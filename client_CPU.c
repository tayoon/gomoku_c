#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

int board[15][15];

int LeUp_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][(dir_x-1) + 1] == 2)rev++;if(board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)rev++;	//逆方向
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][(dir_x-1) - go])break;
			else if(board[(dir_y-1) - go][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][(dir_x-1) - 1] && board[(dir_y-1) - 2][(dir_x-1) - 2] == 2)return count + rev;
	else return count;
}

int Up_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][dir_x-1] == 2)rev++;if(board[(dir_y-1) + 2][dir_x-1] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][dir_x-1] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][dir_x-1])break;
			else if(board[(dir_y-1) - go][dir_x-1] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][dir_x-1] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][dir_x-1] && board[(dir_y-1) - 2][dir_x-1] == 2)return count + rev;
	else return count;
}

int RiUp_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][(dir_x-1) - 1] == 2)rev++;if(board[(dir_y-1) + 2][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][(dir_x-1) + go])break;
			else if(board[(dir_y-1) - go][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][(dir_x-1) + 1] && board[(dir_y-1) - 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int Left_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[dir_y-1][(dir_x-1) + 1] == 2)rev++;if(board[dir_y-1][(dir_x-1) + 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[dir_y-1][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[dir_y-1][(dir_x-1) - go])break;
			else if(board[dir_y-1][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[dir_y-1][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[dir_y-1][(dir_x-1) - 1] && board[dir_y-1][(dir_x-1) - 2] == 2)return count + rev;
	else return count;
}

int Right_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[dir_y-1][(dir_x-1) - 1] == 2)rev++;if(board[dir_y-1][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[dir_y-1][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[dir_y-1][(dir_x-1) + go])break;
			else if(board[dir_y-1][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[dir_y-1][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[dir_y-1][(dir_x-1) + 1] && board[dir_y-1][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int LeDo_judge(int dir_y, int dir_x, int count, int a_cnt){
	//if(!board[(dir_y-1) + 1][(dir_x-1) - 1] && !board[(dir_y-1) - 1][(dir_x-1) + 1])return 0;
	int rev = 0;
	if(board[(dir_y-1) - 1][(dir_x-1) + 1] == 2)rev++;if(board[(dir_y-1) - 2][(dir_x-1) + 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][(dir_x-1) - go])break;
			else if(board[(dir_y-1) + go][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][(dir_x-1) + 1] && board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int Down_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) - 1][dir_x-1] == 2)rev++;if(board[(dir_y-1) - 2][dir_x-1] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][dir_x-1] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][dir_x-1])break;
			else if(board[(dir_y-1) + go][dir_x-1] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][dir_x-1] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][dir_x-1] && board[(dir_y-1) + 2][dir_x-1] == 2)return count + rev;
	else return count;
}

int RiDo_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) - 1][(dir_x-1) - 1] == 2)rev++;if(board[(dir_y-1) - 2][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][(dir_x-1) + go])break;
			else if(board[(dir_y-1) + go][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][(dir_x-1) + 1] && board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int ban_judge(int dir_y, int dir_x){		//board[dir_y-1][dir_x-1]のジャッジ
	int ban3_cnt = 0, ban4_cnt = 0, ban6_cnt = 0, five_cnt = 0;
	int a, b, c, d, e, f, g, h;

	if((a = Left_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((b = Right_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((c = Up_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((d = Down_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((e = RiUp_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((f = LeDo_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((g = LeUp_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((h = RiDo_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;

	if(a >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(b >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(c >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(d >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(e >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(f >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(g >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(h >= 3){ban3_cnt = 0;ban4_cnt++;}

	/*if(a >= 4 || b >= 4 || c >= 4 || d >= 4 || e >= 4 || f >= 4 || g >= 4 || h >= 4){ban4_cnt = 0;five_cnt++;}
	if(a >= 5 || b >= 5 || c >= 5 || d >= 5 || e >= 5 || f >= 5 || g >= 5 || h >= 5){
		if(five_cnt >= 2 && ban6_cnt == five_cnt - 1){
			five_cnt = 1, ban6_cnt = 0;
		}else if(five_cnt >= 2 && ban6_cnt == five_cnt){
			five_cnt = 0;
		}
	}*/
	
	printf("3: %d, 4: %d, 5: %d, 6: %d\n", ban3_cnt, ban4_cnt, five_cnt, ban6_cnt);
	printf("leup: %d, up: %d, riup: %d, left: %d, right: %d, ledo: %d, down: %d, rido: %d\n",
			a, b, c, d, e, f, g, h);
	if(ban3_cnt >= 2 || ban4_cnt >= 2 || ban6_cnt)return 0;
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
	sprintf(destination,"172.24.14.220");		//自分のPCのIPアドレス
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

			if(!ban_judge(enemy_y, enemy_x)){printf("end!!");break;}
			//if(ban_judge(enemy_y, enemy_x) == 1){printf("win!!");break;}

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