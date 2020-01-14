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

double valueSearch(int x, int y, int i,double numOfNode,int spaceFlag, int playerNum){      //int playerNum = 1or2
  // int original_x = x;
  // int original_y = y;
  x += dx[i];
  y += dy[i];

  // if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode*10;
	// if(board[y][x] == (2/playerNum))return numOfNode*10;
  if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
	if(board[y][x] == (2/playerNum)){numOfNode -= 1.5;/*printf("ABAB\n");*/return numOfNode;}
  if(spaceFlag == 2)return numOfNode;
	if(board[y][x] == 1*playerNum)return valueSearch(x,y,i,numOfNode + 1,spaceFlag,playerNum);
	if(board[y][x] == 0)return valueSearch(x,y,i,numOfNode,spaceFlag + 1,playerNum);
  return 0;
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


void setBoard(int x,int y,int num){
  board[y][x] = num;
}


int get_value(int x, int y, int player_num){		//board[y-1][x-1]のジャッジ
  value_board[y][x] = 0;
  int jud_num[8] = {0,0,0,0,0,0,0,0};
  int jud_5[4] = {0,0,0,0};
  int block[4];

  int i = 0;

  //連続したコマを見つける用w
  for(i = 0; i < 4; i++){
    jud_5[i] = valueSearch(x,y,i,0,1,player_num)*10 + valueSearch(x,y,(7-i),0,1,player_num)*10;
  }
  //printf("\n");

  //反対側のコマも判断する
  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    jud_num[i] = valueSearch(x,y,i,0,0,player_num)*10 + valueSearch(x,y,(7-i),0,1,player_num)*10;
  }
  //printf("\n");

  //連続しているかに関わらず33,44を判断
  for(i = 0; i < 8; i++){
    switch(jud_num[i]){
      case 10:value_board[y][x] += 2;break;
      case 20:value_board[y][x] += 18;break;
      case 30:value_board[y][x] += 146*2;break;
      case 15:value_board[y][x] += 100;break;
      case 5:value_board[y][x] += 1;break;
      default:value_board[y][x] += 0;break;
    }
    //printf("%d -> ", value_board[y][x]);
  }
  //printf("\n");

  //連続している5連,長連を判断
  //また連続している33,44は重複しているので引く
  for(i = 0; i < 4; i++){

    switch(jud_5[i]){
      case 10:value_board[y][x] -= 2;break;
      case 20:value_board[y][x] -= 18;break;
      case 30:value_board[y][x] -= 146;break;
      case 40:value_board[y][x] += 10000;break;
      case 25:value_board[y][x] += 10000;break;
      case 15:value_board[y][x] -= 100;break;
      case 5:value_board[y][x] -= 1;break;
      default:value_board[y][x] += 0;break;
    }
  }
  //printf("\n\n");
  //printf("x:%d, y:%d, player:%d, value:%d\n", x+1, y+1, player_num, value_board[y][x]);
  return value_board[y][x];
}
//置こうとしているマスの周り確認（優位性）<- ban_judgeを利用
// int get_value(int dir_x, int dir_y, int player_num){		//board[dir_y-1][dir_x-1]のジャッジ
// 	int second = 0;
// 	int three = 0;
//   int four = 0;
//   int five = 0;

//   int jud_num[8] = {0,0,0,0,0,0,0,0};
//   // int show_num[8] = {0,0,0,0,0,0,0,0};    //表示用
//   int jud_5[4] = {0,0,0,0};

//   int i = 0;
//   int x = dir_x - 1;
//   int y = dir_y - 1;

//   //反対側のコマも判断する
//   //連続しているかは関係なく33,44を見つける用
//   for (i = 0; i < 8; i++){
//     // show_num[i] = search(x,y,i,0,0, player_num);
//     jud_num[i] = search(x,y,i,0,0,player_num) + search(x,y,(7-i),0,1,player_num);
//   }

//   //連続したコマを見つける用
//   for(i = 0; i < 4; i++){
//     jud_5[i] = search(x,y,i,0,1,player_num) + search(x,y,(7-i),0,1,player_num);
//   }

//   //連続しているかに関わらず33,44を判断
//   for(i = 0; i < 8; i++){
//     switch(jud_num[i]){
//       case 1:second++; break;
//       case 2:three++; break;
//       case 3:four++; break;
//       default: break;
//     }
//   }

//   //連続している5連,長連を判断
//   //また連続している33,44は重複しているので引く
//   for(i = 0; i < 4; i++){
//     switch(jud_5[i]){
//       case 1:second--; break;
//       case 2:three--; break;
//       case 3:four--; break;
//       case 4:five++; break;
//       default: break;
//     }
//   }

//   if(second == 1)return 2;
//   if(three == 1)return 3;
//   if(four == 1)return 4;
//   if(five == 1)return 5;
//   return 0;
// }




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
  if(ban3_cnt>=2){return 0;}
  if(ban4_cnt>=2){return 0;}
  if(ban6_cnt>=2){return 0;}
  return 1;
}