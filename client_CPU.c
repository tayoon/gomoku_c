#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

int board[15][15];

int LeUp_judge(int a, int b, int count){
	if(!board[(a-1) - 1][(b-1) - 1])return 0;
	if(board[(a-1) - 1][(b-1) - 1] == 2){
		count++;
		count += LeUp_judge(a-1, b-1, count);
	}
	return count;
}
int Up_judge(int a, int b, int count){
	if(board[(a-1) - 1][b-1] == 2){
		count++;
		count += Up_judge(a, b-1, count);
	}
	return count;
}
int RiUp_judge(int a, int b, int count){
	if(board[(a-1) - 1][(b-1) + 1] == 2){
		count++;
		count += RiUp_judge(a+1, b-1, count);
	}
	return count;
}
int Left_judge(int a, int b, int count){
	if(board[a-1][(b-1) - 1] == 2){
		count++;
		count += Left_judge(a-1, b, count);
	}
	return count;
}
int Right_judge(int a, int b, int count){
	if(board[a-1][(b-1) + 1] == 2){
		count++;
		count += Right_judge(a-1, b+1, count);
	}
	return count;
}
int LeDo_judge(int a, int b, int count){
	if(board[(a-1) + 1][(b-1) - 1] == 2){
		count++;
		count += LeDo_judge(a-1, b+1, count);
	}
	return count;
}
int Down_judge(int a, int b, int count){
	if(board[(a-1) + 1][b-1] == 2){
		count++;
		count += Down_judge(a-1, b-1, count);
	}
	return count;
}
int RiDo_judge(int a, int b, int count){
	if(board[(a-1) + 1][(b-1) + 1] == 2){
		count++;
		count += RiDo_judge(a-1, b-1, count);
	}
	return count;
}

int ban_judge(int a, int b){		//board[a-1][b-1]のジャッジ
	int ban3_cnt = 0, ban4_cnt = 0, ban5_cnt = 0;
	int width, deepth, slash, backslash;
	/*for(int i = -1; i < 2; i++){			//8方向調べる
		for(int j = -1; j < 2; j++){
			if(i == 0 && j == 0)continue;
			if(board[(a-1) + i][(b-1) + j] == 2){
				if(board[(a-1+i) + i][(b-1+j) + j] == 2){
					ban3_cnt++;
					if(board[(a-1+i+i) + i][(b-1+j+j) + j] == 2)ban4_cnt++;
				}
			}
			printf("i: %d, j: %d, 3: %d, 4: %d\n", i, j, ban3_cnt, ban4_cnt);
		}
	}*/
	if((width = Left_judge(a, b, 0) + Right_judge(a, b, 0)) >= 2)ban3_cnt++;
	if((deepth = Up_judge(a, b, 0) + Down_judge(a, b, 0)) >= 2)ban3_cnt++;
	if((slash = RiUp_judge(a, b, 0) + LeDo_judge(a, b, 0)) >= 2)ban3_cnt++;
	if((backslash = LeUp_judge(a, b, 0) + RiDo_judge(a, b, 0)) >= 2)ban3_cnt++;
	if(width >= 3)ban4_cnt++;
	if(deepth >= 3)ban4_cnt++;
	if(slash >= 3)ban4_cnt++;
	if(backslash >= 3)ban4_cnt++;
	if(width >= 4 || deepth >= 4 || slash >= 4 || backslash >= 4)ban5_cnt++;
	
	printf("3: %d, 4: %d, 5: %d\n", ban3_cnt, ban4_cnt, ban5_cnt);
	printf("leup: %d, up: %d, riup: %d, left: %d, right: %d, ledo: %d, down: %d, rido: %d\n",
			LeUp_judge(a, b, 0), Up_judge(a, b, 0), RiUp_judge(a, b, 0), Left_judge(a, b, 0), Right_judge(a, b, 0), LeDo_judge(a, b, 0), Down_judge(a, b, 0), RiDo_judge(a, b, 0));
	if(ban3_cnt >= 2 || ban4_cnt >= 2 || ban5_cnt)return 0;
	else return 1;
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
	sprintf(destination,"192.168.11.2");		//自分のPCのIPアドレス
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
	char name[256] = "RYOTA";
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
			while(1){
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
			/************以下にロジックを書く********/

			if(!ban_judge(enemy_y, enemy_x))break;

			while(1){
				/*
				int i, j;
				int x_start = 0, y_start = 0, x_end = 0, y_end = 0;
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[i][j])break;
					}
					if(board[i][j]){printf("y: %d, x: %d\n", i, j);y_start = i + 1;break;}
				}
				for(i = 0; i < 15; i++){
					for(j = 0; j < 15; j++){
						if(board[j][i])break;
					}
					if(board[j][i]){printf("x: %d, y: %d\n", i, j);x_start = i + 1;break;}
				}
				for(i = 14; i >= 0; i--){
					for(j = 14; j >= 0; j--){
						if(board[i][j])break;
					}
					if(board[i][j]){printf("y: %d, x: %d\n", i, j);y_end = i + 1;break;}
				}
				for(i = 14; i >= 0; i--){
					for(j = 14; j >= 0; j--){
						printf("x: %d, y: %d, board: %d\n", i, j, board[j][i]);
						if(board[j][i])break;
					}
					if(board[j][i]){printf("x: %d, y: %d\n", i, j);x_end = i + 1;break;}
				}
				printf("start: x = %d, y = %d\n", x_start, y_start);
				printf("end: x = %d, y = %d\n", x_end, y_end);
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