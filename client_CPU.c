#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include "judge.h"
#include "judge.c"

int board[15][15];

int maxlevel(int deepth, int alpha, int beta){
	int score;

	if(deepth == 0){
		//return 現在の局面の評価値
	}

	
}

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
	char name[256] = "BOSS";
	send(s,name,strlen(name),0);		//名前送信
	printf("%s\n",name);
	char msg[256];

	int x = 0;
	int y = 0;

	while(1){
		//何か文字列を受け取るまで待機
		while(-1 == recv(s, buffer, 1024, 0)){}
		printf("recieve : %s\n",buffer);
		//endの文字列を受け取ると終了
		if(!strcmp("end",buffer))break;
		//先手の1手目
		if(start_flag){
			x = 8, y = 8;
			board[y-1][x-1] = 1;
			start_flag = 0;
		}
		else if(white_flag){
			char *ptr;
			ptr = strtok(buffer,",");
			int enemy_x = atoi(ptr);
			ptr = strtok(NULL,",");
			int enemy_y = atoi(ptr);
			board[enemy_y-1][enemy_x-1] = 2;
			while(1){
				srand((unsigned)time(NULL));
				x = rand() % 3 + 7;
				y = rand() % 3 + 7;
				if(!board[y-1][x-1])break;
			}
			board[y-1][x-1] = 1;
			white_flag = 0;
		}
		//先手なら2手目から、後手なら1手目からelse通る
		else{
			char *ptr;
			ptr = strtok(buffer,",");
			int enemy_x = atoi(ptr);
			ptr = strtok(NULL,",");
			int enemy_y = atoi(ptr);
			board[enemy_y-1][enemy_x-1] = 2;
			/************以下にロジックを書く**
			 * ******/
			if(ban)if(!ban_judge(enemy_y, enemy_x)){printf("end!!");break;}

<<<<<<< HEAD
			/*while(1){
				int i, j;
=======
			while(1){
				int yy = 0, xx = 0;
>>>>>>> 45493fc63f093cf3900825d29fd260158379ebcc
				int x_start = 0, y_start = 0, x_end = 0, y_end = 0;
				for(yy = 0; yy < 15; yy++){
					for(xx = 0; xx < 15; xx++){
						if(board[yy][xx])break;
					}
					if(board[yy][xx])break;
				}

				printf("y: %d, x: %d\n", yy, xx);y_start = yy + 1;
				for(xx = 0; xx < 15; xx++){
					for(yy = 0; yy < 15; yy++){
						if(board[yy][xx])break;
					}
					if(board[yy][xx])break;
				}
				printf("y: %d, x: %d\n", yy, xx);x_start = xx + 1;

				for(yy = 14; yy >= 0; yy--){
					for(xx = 14; xx >= 0; xx--){
						if(board[yy][xx])break;
					}
					if(board[yy][xx])break;
				}
				printf("y: %d, x: %d\n", yy, xx);y_end = yy + 1;
				int i,j;
				for(i = 14; i >= 0; i--){
					for(j = 14; j >= 0; j--){
						// printf("x: %d, y: %d, board: %d\n", i, j, board[j][i]);
						if(board[j][i])break;
					}
					if(board[j][i])break;
				}
				printf("y: %d, x: %d\n", j, i);x_end = i + 1;

				printf("start: x = %d, y = %d\n", x_start - 1, y_start - 1);
				printf("end: x = %d, y = %d\n", x_end + 1, y_end + 1);
			*/

				srand((unsigned)time(NULL));
				x = rand()%15 + 1;
				y = rand()%15 + 1;
				if(!board[y-1][x-1])break;
			}
			board[y-1][x-1] = 1;
			/*************ロジックここまで***********/
		}
		sprintf(msg,"%d,%d",x,y);
		printf("send : %s\n",msg);
		while(-1 == send(s, msg, strlen(msg), 0)){}
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();

	return 0;

}