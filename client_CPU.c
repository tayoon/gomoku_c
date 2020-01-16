#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include "judge.h"
#include "judge.c"
#include "alphabeta.c"
#include "define.h"

int board[15][15];
int value_board[15][15];

int main(void) {

	//接続するサーバの情報の構造体を用意
	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	char str[256];
	printf("black or white\n");
	while(1){
		scanf("%s",str);
		if(!strcmp("black",str) || !strcmp("white",str))break;
		printf("文字が違います。black or white\n");
	}

	//サーバの情報を入力
	char destination[256];
	//scanf("%s",destination);
	sprintf(destination,"127.0.0.1");		//自分のPCのIPアドレス
	char port_char[256];

	int black_flag, white_flag;//先手・後手
	int ban = 0;	//禁じ手かどうか
	int start_flag_2=0;	//2手目用

	//先手か後手の文字列を判断
	if(!strcmp("black",str)){
		sprintf(port_char,"12345");
		black_flag = 1;
		white_flag = 0;
		ban = 0;
	}
	else{
		sprintf(port_char,"12346");
		black_flag=0;
		white_flag = 1;
		ban = 1;
	}

	int port = atoi(port_char);
	dest.sin_port = htons(port);  //ポート番号
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(destination);

	//ソケット通信の準備・生成
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//サーバへの接続
	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {
		printf("%sに接続できませんでした\n", destination);
		return -1;
	}

	char buffer[1024];
	printf("%sに接続しました\n", destination);
	recv(s,buffer,1024,0);		//文字を受ける
	printf("recieve : %s\n",buffer);
	char name[256] = "TAYOON";
	send(s,name,strlen(name),0);		//名前送信
	printf("%s\n",name);
	char msg[256];

	//送信用のx,y
	int x = 0;
	int y = 0;


	//以下五目並べの処理
	while(1){
		//何か文字列を受け取るまで待機
		while(-1 == recv(s, buffer, 1024, 0)){}
		printf("recieve : %s\n",buffer);
		//endの文字列を受け取ると終了
		if(!strcmp("end",buffer))break;
		int ban_flag = 0;			//禁じ手か否か
		int win_flag = 0;			//勝利したか否か
		int draw_flag = 0;		//引き分けか否か

		//先手の1手目
		if(black_flag){
			x = 8, y = 8;
			setBoard(x-1,y-1,MY_NUM);
			black_flag = 0;
			start_flag_2 = 1;
		}
		//後手の1手目
		else if(white_flag){
			char *ptr;
			ptr = strtok(buffer,",");
			int enemy_x = atoi(ptr);
			ptr = strtok(NULL,",");
			int enemy_y = atoi(ptr);
			setBoard(enemy_x-1,enemy_y-1,ENEMY_NUM);

			while(1){
				srand((unsigned)time(NULL));
				x = rand() % 3 + 7;
				y = rand() % 3 + 7;
				if(!board[y-1][x-1])break;
			}
			setBoard(x-1,y-1,MY_NUM);
			white_flag = 0;
		}
		//先手の2手目
		else if(start_flag_2){
			char *ptr;
			ptr = strtok(buffer,",");
			int enemy_x = atoi(ptr);
			ptr = strtok(NULL,",");
			int enemy_y = atoi(ptr);
			setBoard(enemy_x-1,enemy_y-1,ENEMY_NUM);

			if(!(enemy_x-x)){
				x = enemy_x - 1;
				y = enemy_y;
			}
			else if(!(enemy_y-y)){
				x = enemy_x;
				y = enemy_y - 1;
			}
			else{
				if(!((enemy_x-x)-(enemy_y-y))){x = 9; y = 7;}
				else{x = 7; y = 7;}
			}
			setBoard(x-1,y-1,MY_NUM);
			start_flag_2 = 0;
		}
		//先手なら3手目から、後手なら2手目からelse通る
		else{
			char *ptr;
			ptr = strtok(buffer,",");
			int enemy_x = atoi(ptr);
			ptr = strtok(NULL,",");
			int enemy_y = atoi(ptr);
			setBoard(enemy_x-1,enemy_y-1,ENEMY_NUM);

			/************以下にロジックを書く*********/
			//相手の禁じ手判定
			if(ban && !ban_judge(enemy_x-1,enemy_y-1,ENEMY_NUM)){
					ban_flag = 1;
			}
			//勝利判定
			if(checkWin(MY_NUM)){
				int i = 0,j = 0,k = 0;
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[i][j]!=0)continue;
      			for(k = 0; k < 4; k++){
        		int numOfNode = search(j,i,k,0,1,MY_NUM) + search(j,i,(7-k),0,1,MY_NUM);
        		if(numOfNode==4){x = j; y = i;}
      			}
					}
				}
				win_flag = 1;
				x++;y++;
			}
			//敵の5連阻止
			else if(checkWin(ENEMY_NUM)){
				int i = 0,j = 0,k = 0;
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[i][j]!=0)continue;
      			for(k = 0; k < 4; k++){
        		int numOfNode = search(j,i,k,0,1,ENEMY_NUM) + search(j,i,(7-k),0,1,ENEMY_NUM);
        		if(numOfNode==4){x = j; y = i;}
      			}
					}
				}
				x++;y++;
			}
			else if(checkDraw()){
				draw_flag = 1;
			}
			else{
				int i = 0;
				int j = 0;
				int max = 0;
				int maxX,maxY;
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[i][j]){printf("#,  ");continue;}
						if(!ban && !ban_judge(j, i, MY_NUM)){printf("b, ");continue;}
						int score = get_value(j, i, MY_NUM) + get_value(j, i, ENEMY_NUM);
						if(max <= score){
							max = score;
							maxX = j;
							maxY = i;
						}
						printf("%d, ", score);
					}
					printf("\n");
				}
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(i==maxY && j==maxX)printf(" ● ");
						else if(board[i][j]==1)printf(" ○ ");
						else if(board[i][j]==2)printf(" × ");
						else printf(" ― ");
					}
					printf("\n");
				}
				x = maxX;
				y = maxY;
				printf("x -> %d,y -> %d\n",x,y);
				printf("maxX->%d,maxY->%d\n",maxX,maxY);
				setBoard(x,y,MY_NUM);
				x++;
				y++;
				/*************ロジックここまで***********/
			}
		}
		int i = 0;
		int j = 0;
		for(i = 0; i < 15; i++){
			for(j = 0; j < 15; j++){
				if(board[i][j]){
					value_board[i][j] = 0;
				}
			}
		}
		getBoard();
		//printf("%d\n",start_flag_2);
		if(ban_flag)sprintf(msg, "%s", "forbidden");
		else if(win_flag)sprintf(msg, "%d,%d,%s", x,y,"win");
		else if(draw_flag)sprintf(msg,"%s","draw");
		else sprintf(msg,"%d,%d",x,y);
		printf("send : %s\n",msg);
		while(-1 == send(s, msg, strlen(msg), 0)){}
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();

	return 0;

}