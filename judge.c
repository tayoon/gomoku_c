#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "judge.h"

extern int board[15][15];
extern int value_board[15][15];
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
int search(int x, int y, int i,int numOfNode,int spaceFlag, int playerNum){      //int playerNum = 1or2

  x += dx[i];
  y += dy[i];

  if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
	if(board[y][x] == (2/playerNum) || spaceFlag==2)return numOfNode;
	if(board[y][x] == 1*playerNum)return search(x,y,i,numOfNode + 1,spaceFlag,playerNum);
	if(board[y][x] == 0)return search(x,y,i,numOfNode,spaceFlag + 1,playerNum);
  return 0;
}

int addValuesBySearch(int *x,int *y,int i,int numOfNode,int spaceFlag, int playerNum,int *backFlag){

  (*x) += dx[i];
  (*y) += dy[i];

  if(((*x) < 0 || (*y) < 0) || ((*x) > 14 || (*y) > 14))return numOfNode;
	if(board[*y][*x] == (2/playerNum) || spaceFlag==2)return numOfNode;
  if((board[*y][*x] == 1*playerNum) && (spaceFlag==1)){*backFlag=1;return addValuesBySearch(x,y,i,numOfNode + 1,spaceFlag,playerNum,backFlag);}
	if(board[*y][*x] == 1*playerNum)return addValuesBySearch(x,y,i,numOfNode + 1,spaceFlag,playerNum,backFlag);
	if(board[*y][*x] == 0)return addValuesBySearch(x,y,i,numOfNode,spaceFlag + 1,playerNum,backFlag);
  return 0;
}

//全体の評価値
int getValueOfBoard(){
    int sum = 0;
    int i = 0,j = 0;
    for(i = 0; i < 15; i++){
        for(j = 0; j < 15; j++){
            sum += value_board[i][j];
        }
    }
    return sum;
}

void getValueBoard(){
  int x = 0,y = 0;
  for(y = 0; y < 15; y++){
    for(x = 0; x < 15; x++){
      printf(" %d ",value_board[y][x]);
    }
    printf("\n");
  }
}

void setValueBoard(int x,int y, int num){
  int i = 0,j = 0;
  //置いた駒の周囲を＋1する
  //ボード外なら
  for(i = y-1; i <= y+1; i++){
    if(i < 0 || i > 14)continue;

    for(j = x-1; j <= x+1; j++){
      if(j < 0 || j > 14)continue;

      if(num==1)value_board[i][j]++;
      if(num==2)value_board[i][j]--;
    }
  }

  for(i = 0; i < 4; i++){

    int fx = x,fy = y;
    int bx = x,by = y;
    int backFlag = 0;
    int backFlag2 = 0;

    int numOfNode = addValuesBySearch(&fx,&fy,i,1,0,num,&backFlag) + addValuesBySearch(&bx,&by,(7-i),1,0,num,&backFlag2)-1;
    if(numOfNode >= 2){
      if(backFlag==0)fx-=dx[i];fy-=dy[i];
      if(backFlag2==0)bx-=dx[7-i];by-=dy[7-i];
      fx-=dx[i];
      fy-=dy[i];
      bx-=dx[7-i];
      by-=dy[7-i];
      value_board[fy][fx] += (numOfNode)*(numOfNode)*(numOfNode);
      value_board[by][bx] += (numOfNode)*(numOfNode)*(numOfNode);
    }
  }

  // getValueBoard();
}

int checkWin(int num){
  int x = 0,y = 0;
  int i = 0;
  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(board[y][x]!=0)continue;
      for(i = 0; i < 4; i++){
        int numOfNode = search(x,y,i,0,1,num) + search(x,y,(7-i),0,1,num);
        if(numOfNode==4)return 1;       //大勝利！！！！！！！！！！
      }
    }
  }
  return 0;
}

void getBoard(){
  int i,j;
  for(i = 0; i < 15;i++){
		for(j = 0; j < 15; j++){
			printf("%d ",board[i][j]);
		}
		printf("\n");
  }
}

void resetValueBoard(int x,int y, int num){
  int i = 0,j = 0;
  for(i = y-1; i <= y+1; i++){
    if(i < 0 || i > 14)continue;
    for(j = x-1; j <= x+1; j++){
      if(j < 0 || j > 14)continue;
      if(num==1)value_board[i][j]--;
      if(num==2)value_board[i][j]++;
    }
  }

  for(i = 0; i < 4; i++){

    int fx = x,fy = y;
    int bx = x,by = y;
    int backFlag = 0;
    int backFlag2 = 0;

    int numOfNode = addValuesBySearch(&fx,&fy,i,1,0,num,&backFlag) + addValuesBySearch(&bx,&by,(7-i),1,0,num,&backFlag2)-1;
    if(numOfNode >= 2){
      if(backFlag==0)fx-=dx[i];fy-=dy[i];
      if(backFlag2==0)bx-=dx[7-i];by-=dy[7-i];
      fx-=dx[i];
      fy-=dy[i];
      bx-=dx[7-i];
      by-=dy[7-i];
      // printf("\nfx->%d,fy->%d,backFlag->%d\n",fx,fy,backFlag);
      // printf("bx->%d,by->%d,backFlag2->%d\n\n",bx,by,backFlag2);
      value_board[fy][fx] -= (numOfNode)*(numOfNode)*(numOfNode);
      value_board[by][bx] -= (numOfNode)*(numOfNode)*(numOfNode);
    }
  }

  // getValueBoard();
}


void setBoard(int x,int y,int num){
  board[y][x] = num;
  setValueBoard(x,y,num);
}


void resetBoard(int x,int y,int num){
  board[y][x] = 0;
  resetValueBoard(x,y,num);
}
//置こうとしているマスの周り確認（優位性）<- ban_judgeを利用
int get_value(int dir_x, int dir_y, int player_num){		//board[dir_y-1][dir_x-1]のジャッジ
	int second = 0;
	int three = 0;
  int four = 0;
  int five = 0;

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
    jud_num[i] = search(x,y,i,0,0,player_num) + search(x,y,(7-i),0,1,player_num);
  }

  //連続したコマを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = search(x,y,i,0,1,player_num) + search(x,y,(7-i),0,1,player_num);
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

  int x = dir_x;
  int y = dir_y;

  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    show_num[i] = search(x,y,i,0,0,player_num);
    jud_num[i] = show_num[i] + search(x,y,(7-i),0,1,player_num);
  }

  //連続したノードを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = search(x,y,i,0,1,player_num) + search(x,y,(7-i),0,1,player_num);
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