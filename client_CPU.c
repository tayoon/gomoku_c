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
extern int alpha_flag, beta_flag;
extern int alpha, beta;

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
	int start_flag, white_flag, ban;
	if(!strcmp("black",str)){
		sprintf(port_char,"12345");
		start_flag = 1;
		white_flag = 0;
		ban = 0;
	}
	else{
		sprintf(port_char,"12346");
		start_flag=0;
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

	int x = 0;
	int y = 0;
	int start_flag_2=0;

	while(1){
		//何か文字列を受け取るまで待機
		while(-1 == recv(s, buffer, 1024, 0)){}
		printf("recieve : %s\n",buffer);
		//endの文字列を受け取ると終了
		if(!strcmp("end",buffer))break;
		int ban_flag = 0;
		int win_flag = 0;
		//先手の1手目
		if(start_flag){
			x = 8, y = 8;
			setBoard(x-1,y-1,MY_NUM);
			start_flag = 0;
			start_flag_2 = 1;
		}
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
			if(checkWin(MY_NUM)){win_flag = 1;}
			else{
				// int xx = 0, yy = 0;
				// int best_x = 0, best_y = 0;
				// //225のうち、自分がどこに置くか
				// int best = INT_MIN;
				// for(xx = SEARCH_START; xx < SEARCH_END; xx++){
				// 	for(yy = SEARCH_START; yy < SEARCH_END; yy++){
				// 		alpha_flag = 1, beta_flag = 1;
				// 		if(!board[yy][xx]){
				// 			if(ban_judge(xx,yy,MY_NUM)){
				// 				int score = maxlevel(DEPTH_NUM,xx,yy);
				// 				if(score > best){
				// 					best = score;
				// 					best_x = xx, best_y = yy;
				// 					//printf("x: %d, y: %d, point: %d\n", best_x+1, best_y+1, best);
				// 				}
				// 			}//printf("x: %d, y: %d, point: %d ###################################\n", xx+1, yy+1, best);
				// 		}
				// 		//printf("x: %d, y: %d end!!!!!!!!!!!!!!!!!!!!!\n", xx+1, yy+1);
				// 	}
				// }
				// //ここで最適x,y
				// x = best_x, y = best_y;
				int i = 0;
				int j = 0;
				int max = 0;
				int maxX,maxY;
				// for(i = 0; i < 15; i++){
				// 	for(j = 0; j < 15; j++){
				// 		if(board[i][j]){printf("#,  ");continue;}
				// 		if(!ban && !ban_judge(i,j,MY_NUM)){printf("b, ");continue;}
				// 		int score = value_board[i][j];
				// 		if(max <= score){
				// 			max = score;
				// 			maxX = j;
				// 			maxY = i;
				// 		}
				// 		printf("%d, ", score);
				// 	}
				// 	printf("\n");
				// }
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[i][j]){/*printf("#,  ");*/continue;}
						if(!ban && !ban_judge(i,j,MY_NUM)){/*printf("b, ");*/continue;}
						int score = get_value(j, i, MY_NUM) + get_value(j, i, ENEMY_NUM);
						if(max <= score){
							max = score;
							maxX = j;
							maxY = i;
						}
						//printf("%d, ", score);
					}
					//printf("\n");
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
				// getValueBoard();
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
		else if(win_flag)sprintf(msg, "%s", "win");
		else sprintf(msg,"%d,%d",x,y);
		printf("send : %s\n",msg);
		while(-1 == send(s, msg, strlen(msg), 0)){}
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();

	return 0;

}