#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include <limits.h>
#include "judge.h"
#include "define.h"
#include "judge.c"
#include "alphabeta.c"
#include "gomokuController.c"

int board[15][15];
int value_board[15][15];

int ban_flag = 0;			//禁じ手か否か
int win_flag = 0;			//勝利したか否か
int draw_flag = 0;		//引き分けか否か
int black_flag = 0;		//先手
int white_flag = 0;		//後手
int ban = 0;					//禁じ手かどうか
int start_flag_2=0;		//2手目用

int main(int argc,char *argv[]) {

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
	sprintf(destination,"%s",argv[1]);		//自分のPCのIPアドレス
	char port_char[256];

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

		//先手の1手目
		if(black_flag){
			blackOne(&x,&y);
		}
		//後手の1手目
		else if(white_flag){
			whiteOne(buffer,&x,&y);
		}
		//先手の2手目
		else if(start_flag_2){
			blackTwo(buffer,&x,&y);
		}
		//先手なら3手目から、後手なら2手目からelse通る
		else{
			char* delim = " ************************ ";
			int enemy_x,enemy_y;
			recieveEnemy(buffer,&enemy_x,&enemy_y);		//相手の入力受け取り

			//相手の禁じ手判定
			if(ban && ban_judge(enemy_x,enemy_y,ENEMY_NUM)){
					printf("%sそれはbanだよ%s\n",delim,delim);
					ban_flag = 1;
			}
			//勝利判定
			else if(checkWin(MY_NUM,&x,&y)){
				printf("%s大勝利%s\n",delim,delim);
				win_flag = 1;
			}
			//敵の5連阻止
			else if(checkWin(ENEMY_NUM,&x,&y)){
				printf("%s五連を阻止%s\n",delim,delim);
			}
			//引き分け処理
			else if(checkDraw(&x,&y)){
				printf("%s引き分けなんだよなぁ%s\n",delim,delim);
				draw_flag = 1;
			}
			//通常処理
			else{
				think(&x,&y);
				// randomPut(&x,&y);				//デバッグ用
			}
		}
		int i = 0;
		int j = 0;
		//既に石がある場合は評価値を消去する
		for(i = 0; i < 15; i++){
			for(j = 0; j < 15; j++){
				if(!isStone(j,i,SPACE_NUM)){
					value_board[i][j] = 0;
				}
			}
		}
		// getBoard();
		x++;
		y++;
		if(ban_flag)sprintf(msg, "%s", "forbidden");						//禁じ手勝利
		else if(win_flag)sprintf(msg, "%d,%d,%s", x,y,"win");		//5連勝利
		else if(draw_flag)sprintf(msg,"%d,%d,%s", x,y,"draw");	//引き分け
		else sprintf(msg,"%d,%d",x,y);	//通常
		printf("send : %s\n",msg);
		while(-1 == send(s, msg, strlen(msg), 0)){}
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();

	return 0;

}