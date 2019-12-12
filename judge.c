#include <stdio.h>
#include <stdlib.h>
#include "judge.h"

extern int board[15][15];
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

int judge(int dir_y, int dir_x, int i){
  int count = 0;
  int a_cnt = 0;
  int rev = 0;

  int x = dir_x-1;
  int y = dir_y-1;

	if(board[y - dy[i]][x - dx[i]] == 2){
    rev++;
    if(board[y - dy[i]*2][x - dx[i]*2] == 2)rev++;	//逆方向
  }
  int go = 1;

  while(1){
		if(!board[y + dy[i]*go][x + dx[i]*go] && !a_cnt){
      go++;
			if(!board[y + dy[i]*go][x + dx[i]*go])break;
			else if(board[y + dy[i]*go][x + dx[i]*go] == 2)a_cnt++;
		}else if(board[y + dy[i]*go][x + dx[i]*go] == 2){
			count++;
			go++;
		}else break;
	}

	if(!board[y + dy[i]][x + dx[i]] && board[y + dy[i]*2][x + dx[i]*2] == 2)return count + rev;
	else return count;
}


int ban_judge(int dir_y, int dir_x){		//board[dir_y-1][dir_x-1]のジャッジ
	int ban3_cnt = 0, ban4_cnt = 0, ban6_cnt = 0, five_cnt = 0;
	int a, b, c, d, e, f, g, h;
  int num[8];
  int i = 0;
  for (i = 0; i < 8; i++){
    num[i] = judge(dir_y,dir_x,i);
  }

  for(i = 0; i < 8; i++){
    switch(num[i]){
      case 2:ban3_cnt++;break;
      case 3:ban4_cnt++;break;
      case 4:five_cnt++;break;
      case 5:ban6_cnt++;break;
      default: break;
    }
  }
/*
  for(i = 0; i < 4; i++){
    switch(num[i]+num[7-i]){
      case 2:ban3_cnt++;break;
      case 3:ban4_cnt++;break;
      case 4:five_cnt++;break;
      case 5:ban6_cnt++;break;
      default: break;
    }
  }
*/
	//if(a >= 4 || b >= 4 || c >= 4 || d >= 4 || e >= 4 || f >= 4 || g >= 4 || h >= 4){ban4_cnt = 0;five_cnt++;}
	// if(a >= 5 || b >= 5 || c >= 5 || d >= 5 || e >= 5 || f >= 5 || g >= 5 || h >= 5){
	// 	if(five_cnt != ban6_cnt)five_cnt++;
	// 	else if(five_cnt == ban6_cnt)ban6_cnt++;
	// }

	printf("3: %d, 4: %d, 5: %d, 6: %d\n", ban3_cnt, ban4_cnt, five_cnt, ban6_cnt);
	for(i = 0; i < 8; i++){
    printf("%d,%d -> %d\n",dx[i],dy[i],num[i]);
  }
	if(ban3_cnt >= 2 || ban4_cnt >= 2 || (ban6_cnt && !five_cnt))return 0;
	else return 1;
}
