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
//一方向
int search(int dir_x, int dir_y, int i,int numOfNode,int cnt_flag, int player_num){      //int player_num = 1or2

  int x = dir_x + dx[i];
  int y = dir_y + dy[i];

	if(board[y][x] == (2/player_num) || cnt_flag==2 || (x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
	if(board[y][x] == 1*player_num)return search(x,y,i,numOfNode + 1,cnt_flag,player_num);
	if(board[y][x] == 0)return search(x,y,i,numOfNode,cnt_flag + 1,player_num);
}

//一つでも空白を見つけると終了
//隣り合ったコマの数を計算
//一方向
int search_adj(int dir_x, int dir_y, int i,int numOfNode, int player_num){

  int x = dir_x + dx[i];
  int y = dir_y + dy[i];

	if(board[y][x] == (2/player_num) || board[y][x] == 0 || (x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
	if(board[y][x] == 1*player_num)return search_adj(x,y,i,numOfNode + 1,player_num);
}

//置こうとしているマスの周り確認（優位性）<- ban_judgeを利用
int get_value(int dir_x, int dir_y, int player_num){		//board[dir_y-1][dir_x-1]のジャッジ
	int second = 0;
	int three = 0;
  int four = 0;
  int five = 0;
  int six = 0;

  int jud_num[8] = {0,0,0,0,0,0,0,0};
  // int show_num[8] = {0,0,0,0,0,0,0,0};    //表示用
  int jud_5[4] = {0,0,0,0};

  int i = 0;
  int x = dir_x - 1;
  int y = dir_y - 1;

  //反対側のコマも判断する
  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    // show_num[i] = search(x,y,i,0,0, player_num);
    jud_num[i] = search(x,y,i,0,0,player_num) + search_adj(x,y,(7-i),0, player_num);
  }

  //連続したコマを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = search_adj(x,y,i,0, player_num) + search_adj(x,y,(7-i),0, player_num);
  }

  //連続しているかに関わらず33,44を判断
  for(i = 0; i < 8; i++){
    switch(jud_num[i]){
      case 1:second++; break;
      case 2:three++; break;
      case 3:four++; break;
      default: break;
    }
  }

  //連続している5連,長連を判断
  //また連続している33,44は重複しているので引く
  for(i = 0; i < 4; i++){
    switch(jud_5[i]){
      case 1:second--; break;
      case 2:three--; break;
      case 3:four--; break;
      case 4:five++; break;
      case 5:six++; break;
      default: break;
    }
  }

  if(second == 1)return 2;
  if(three == 1)return 3;
  if(four == 1)return 4;
  if(five == 1)return 5;
  return 0;
}


int ban_judge(int dir_x, int dir_y,int player_num){		//board[dir_y-1][dir_x-1]のジャッジ
	int ban3_cnt = 0;
  int ban4_cnt = 0;
  int five_cnt = 0;
  int ban6_cnt = 0;
  int jud_num[8] = {0,0,0,0,0,0,0,0};
  int show_num[8] = {0,0,0,0,0,0,0,0};    //表示用
  int jud_5[4] = {0,0,0,0};
  int i = 0,j = 0;

  int x = dir_x - 1;
  int y = dir_y - 1;

  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    show_num[i] = search(x,y,i,0,0,player_num);
    jud_num[i] = show_num[i] + search_adj(x,y,(7-i),0,player_num);
  }

  //連続したノードを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = search_adj(x,y,i,0,player_num) + search_adj(x,y,(7-i),0,player_num);
  }

  //連続しているかに関わらず33,44を判断
  for(i = 0; i < 8; i++){
    switch(jud_num[i]){
      case 2:ban3_cnt++; break;
      case 3:ban4_cnt++; break;
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
  // if(ban3_cnt==2){printf("三三です.\n");return 0;}
  // if(ban4_cnt==2){printf("四四です.\n");return 0;}
  // if(ban6_cnt==2){printf("長連です.\n");return 0;}
  if(ban3_cnt==2){return 0;}
  if(ban4_cnt==2){return 0;}
  if(ban6_cnt==2){return 0;}
  return 1;
}