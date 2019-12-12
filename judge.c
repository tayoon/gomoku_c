#include <stdio.h>
#include <stdlib.h>
#include "judge.h"

extern int board[15][15];
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

char direction[8][256] = {
  {"Left Up"},
  {"Up"},
  {"Right Up"},
  {"Left"},
  {"Right"},
  {"Left Down"},
  {"Down"},
  {"Right Down"}
};

//二つ空白を見つけると終了
int judge(int dir_y, int dir_x, int i,int numOfNode,int cnt_flag){

  int x = dir_x + dx[i];
  int y = dir_y + dy[i];

	if(board[y][x] == 2)return judge(y,x,i,numOfNode + 1,cnt_flag);
	if(board[y][x] == 0)return judge(y,x,i,numOfNode,cnt_flag + 1);
	if(cnt_flag==2)return numOfNode;
}

//一つでも空白を見つけると終了
int judge_adj(int dir_y, int dir_x, int i,int numOfNode){

  int x = dir_x + dx[i];
  int y = dir_y + dy[i];

	if(board[y][x] == 2)return judge_adj(y,x,i,numOfNode + 1);
	if(board[y][x] == 0)return numOfNode;
}

int ban_judge(int dir_y, int dir_x){		//board[dir_y-1][dir_x-1]のジャッジ
	int ban3_cnt = 0, ban4_cnt = 0, ban6_cnt = 0, five_cnt = 0;
  int jud_num[8] = {0,0,0,0,0,0,0,0};
  int show_num[8] = {0,0,0,0,0,0,0,0};    //表示用
  int jud_5[4] = {0,0,0,0};
  int i,j;

  int y = dir_y - 1;
  int x = dir_x - 1;

  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    show_num[i] = judge(y,x,i,0,0);
    jud_num[i] = show_num[i] + judge_adj(y,x,(7-i),0);
  }

  //連続したノードを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = judge_adj(y,x,i,0) + judge_adj(y,x,(7-i),0);
  }

  //連続しているかに関わらず33,44を判断
  for(i = 0; i < 8; i++){
    switch(jud_num[i]){
      case 2:ban3_cnt++;break;
      case 3:ban4_cnt++;break;
      default: break;
    }
  }

  //連続している5連,長連を判断
  //また連続している33,44は重複しているので引く
  for(i = 0; i < 4; i++){
    switch(jud_5[i]){
      case 2:ban3_cnt--; break;
      case 3:ban4_cnt--; break;
      case 4:five_cnt++; break;
      case 5:ban6_cnt++; break;
      default: break;
    }
  }
  //見かけ上のノード数
	for(i = 0; i < 8; i++){printf("%s -> %d\n",direction[i],show_num[i]);}
	printf("3: %d, 4: %d, 5: %d, 6: %d\n", ban3_cnt, ban4_cnt, five_cnt, ban6_cnt);
  if(ban3_cnt==2){printf("三三です.\n");return 0;}
  if(ban4_cnt==2){printf("四四です.\n");return 0;}
  if(ban6_cnt==2){printf("長連です.\n");return 0;}
	//  if(ban3_cnt == 2 || ban4_cnt == 2 || (ban6_cnt && !five_cnt))return 0;
  return 1;
}
