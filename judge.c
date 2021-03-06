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

//指定した目の状態であれば1を返す
int isStone(int x,int y,int num){
  if(board[y][x]==num)return 1;
  else return 0;
}

//通常の探索のためのメソッド
int search(int x, int y, int i,int numOfNode,int spaceFlag, int playerNum){      //int playerNum = 1or2

  x += dx[i];
  y += dy[i];

  int myNum = (1*playerNum);
  int enemyNum = (2/playerNum);

  if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
	if(isStone(x,y,enemyNum) || spaceFlag==2)return numOfNode;
	if(isStone(x,y,myNum))return search(x,y,i,numOfNode + 1,spaceFlag,playerNum);
	if(isStone(x,y,SPACE_NUM))return search(x,y,i,numOfNode,spaceFlag + 1,playerNum);
  return 0;
}

//引き分け探索用メソッド
int limitSearch(int x, int y, int i,int numOfSpace, int playerNum,int isLimit){      //int playerNum = 1or2

  x += dx[i];
  y += dy[i];

  int myNum = (1*playerNum);
  int enemyNum = (2/playerNum);

  if(isLimit==5)return numOfSpace;
  if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfSpace;
	if(isStone(x,y,enemyNum))return numOfSpace;
	if(isStone(x,y,myNum))return limitSearch(x,y,i,numOfSpace + 1,playerNum,isLimit + 1);
	if(isStone(x,y,SPACE_NUM))return limitSearch(x,y,i,numOfSpace + 1,playerNum,isLimit + 1);
  return 0;
}

//禁じ手判定の際、敵がいれば禁じ手ではないようにする
int isEnemyCheck(int x, int y, int i,int numOfNode,int spaceFlag, int playerNum,int noForbiddenFlag){      //int playerNum = 1or2

  x += dx[i];
  y += dy[i];

  int myNum = (1*playerNum);
  int enemyNum = (2/playerNum);

  if((x < 0 || y < 0) || (x > 14 || y > 14))return noForbiddenFlag;
	if(spaceFlag==2)return noForbiddenFlag;
  if(isStone(x,y,enemyNum)){noForbiddenFlag++;return noForbiddenFlag;}
	if(isStone(x,y,myNum))return isEnemyCheck(x,y,i,numOfNode + 1,spaceFlag,playerNum,noForbiddenFlag);
	if(isStone(x,y,SPACE_NUM))return isEnemyCheck(x,y,i,numOfNode,spaceFlag + 1,playerNum,noForbiddenFlag);
  return 0;
}

//評価値用の探索メソッド
double valueSearch(int x, int y, int i,double numOfNode,int spaceFlag, int playerNum){      //int playerNum = 1or2

  x += dx[i];
  y += dy[i];

  int myNum = (1*playerNum);
  int enemyNum = (2/playerNum);

  if((x < 0 || y < 0) || (x > 14 || y > 14))return numOfNode;
  if(spaceFlag == 2)return numOfNode;
	if(isStone(x,y,enemyNum)){numOfNode -= 1.5;return numOfNode;}
	if(isStone(x,y,myNum))return valueSearch(x,y,i,numOfNode + 1,spaceFlag,playerNum);
	if(isStone(x,y,SPACE_NUM))return valueSearch(x,y,i,numOfNode,spaceFlag + 1,playerNum);
  return 0;
}

//5連判定
int checkWin(int num,int *x,int *y){
  int i = 0;
  int xx = 0;
  int yy = 0;
  for(xx = 0; xx < 15; xx++){
    for(yy = 0; yy < 15; yy++){
      if(!isStone(xx,yy,SPACE_NUM))continue;
      for(i = 0; i < 4; i++){
        int numOfNode = search(xx,yy,i,0,1,num) + search(xx,yy,(7-i),0,1,num);
        if(numOfNode==4){
          setBoard(xx,yy,MY_NUM);   //探索は相手も自分も行えるが、入れるのは自分だけ
          *x = xx;
          *y = yy;
          return 1;
        }       //大勝利！！！！！！！！！！
      }
    }
  }
  return 0;
}

//引き分け処理　座標を返さないバージョン
int checkDraw2(){
  int x = 0,y = 0;
  int i = 0;

  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(!isStone(x,y,SPACE_NUM))continue;
      for(i = 0; i < 4; i++){
        int mySpace = limitSearch(x,y,i,0,MY_NUM,0) + limitSearch(x,y,(7-i),0,MY_NUM,0);
        if(mySpace >= 4)return 0;       //引き分けじゃない
      }
    }
  }
  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(!isStone(x,y,SPACE_NUM))continue;
      for(i = 0; i < 4; i++){
        int enemySpace = limitSearch(x,y,i,0,ENEMY_NUM,0) + limitSearch(x,y,(7-i),0,ENEMY_NUM,0);
        if(enemySpace >= 4)return 0;         //引き分けじゃない
      }
    }
  }

  return 1;   //引き分けだね

}

//引き分け処理 適当な座標を返すバージョン
int checkDraw(int *tx,int *ty){

  int x = 0,y = 0;
  int i = 0;

  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(!isStone(x,y,SPACE_NUM))continue;
      for(i = 0; i < 4; i++){
        int mySpace = limitSearch(x,y,i,0,MY_NUM,0) + limitSearch(x,y,(7-i),0,MY_NUM,0);
        if(mySpace >= 4)return 0;       //引き分けじゃない
      }
    }
  }
  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(!isStone(x,y,SPACE_NUM))continue;
      for(i = 0; i < 4; i++){
        int enemySpace = limitSearch(x,y,i,0,ENEMY_NUM,0) + limitSearch(x,y,(7-i),0,ENEMY_NUM,0);
        if(enemySpace >= 4)return 0;         //引き分けじゃない
      }
    }
  }

  for(x = 0; x < 15; x++){
    for(y = 0; y < 15; y++){
      if(isStone(x,y,SPACE_NUM) && ban_judge(x,y,MY_NUM)){
        *tx = x;
        *ty = y;
        return 1;   //引き分けだよ　一応置く手も返すよ
      }
    }
  }

  return 1;   //引き分けだね

}

//置く価値があるかどうか
//そこに置いても両者共に5連が作れない場合、1を返す
int checkNonValue(int x,int y){
  int i = 0;
  for(i = 0; i < 4; i++){
    int mySpace = limitSearch(x,y,i,0,MY_NUM,0) + limitSearch(x,y,(7-i),0,MY_NUM,0);
    if(mySpace >= 4)return 0;       //まだそこに置く価値がある
  }
  for(i = 0; i < 4; i++){
    int enemySpace = limitSearch(x,y,i,0,ENEMY_NUM,0) + limitSearch(x,y,(7-i),0,ENEMY_NUM,0);
    if(enemySpace >= 4)return 0;    //阻止用に敵も探索しときましょうね
  }
  return 1;
}

//現在の盤面を表示
void getBoard(){
  int i,j;
  for(i = 0; i < 15;i++){
		for(j = 0; j < 15; j++){
			printf("%d ",board[i][j]);
		}
		printf("\n");
  }
}

//ボードに評価値を入れる
void setBoard(int x,int y,int num){
  board[y][x] = num;
}

//評価値を返す
int get_value(int x, int y, int player_num){		//board[y-1][x-1]のジャッジ

  value_board[y][x] = 0;
  int jud_num[8] = {0,0,0,0,0,0,0,0};
  int jud_5[4] = {0,0,0,0};
  int block[4];

  int i = 0;

  //反対側のコマも判断する
  for (i = 0; i < 8; i++){
    jud_num[i] = valueSearch(x,y,i,0,0,player_num)*10 + valueSearch(x,y,(7-i),0,1,player_num)*10;
    switch(jud_num[i]){
      case 10:value_board[y][x] += 5;break;     //二連
      case 20:value_board[y][x] += 20;break;    //三連
      case 30:value_board[y][x] += 82*2;break;  //四連
      // case 25:value_board[y][x] += 10000;break; //敵のいる五連
      case 15:value_board[y][x] += 18;break;    //敵のいる四連
      case 5: value_board[y][x] += 4;break;     //敵のいる三連
      default:value_board[y][x] += 0;break;
    }
  }

  //コマをなるべく連続させるため、余分に付加する
  for(i = 0; i < 4; i++){
    jud_5[i] = valueSearch(x,y,i,0,1,player_num)*10 + valueSearch(x,y,(7-i),0,1,player_num)*10;
    switch(jud_5[i]){
      case 10:value_board[y][x] += 5;break;     //二連
      case 20:value_board[y][x] += 20;break;    //三連
      case 30:value_board[y][x] += 82;break;    //四連
      // case 40:value_board[y][x] += 10000;break; //五連
      // case 25:value_board[y][x] += 10000;break; //敵のいる五連
      case 15:value_board[y][x] += 18;break;    //敵のいる四連
      case 5: value_board[y][x] += 4;break;     //敵のいる三連
      default:value_board[y][x] += 0;break;
    }
  }


  return value_board[y][x];
}

//禁じ手判定
int ban_judge(int dir_x, int dir_y,int player_num){		//board[dir_y-1][dir_x-1]のジャッジ

  int isNoForbidden = 0;
	int ban3_cnt = 0;
  int ban4_cnt = 0;
  int ban6_cnt = 0;
  int jud_num[8] = {0,0,0,0,0,0,0,0};
  int jud_5[4] = {0,0,0,0};
  int i = 0,j = 0;

  int x = dir_x;
  int y = dir_y;

  //連続しているかは関係なく33,44を見つける用
  for (i = 0; i < 8; i++){
    jud_num[i] = search(x,y,i,1,0,player_num) + search(x,y,(7-i),1,1,player_num) - 1;
  }

  //連続したノードを見つける用
  for(i = 0; i < 4; i++){
    jud_5[i] = search(x,y,i,1,1,player_num) + search(x,y,(7-i),1,1,player_num) - 1;
  }

  //連続しているかに関わらず33,44を判断
  for(i = 0; i < 8; i++){
    switch(jud_num[i]){
      case 3:
        // printf("jud_num,case3,%s\n",direction[i]);
        ban3_cnt++;
        isNoForbidden += isEnemyCheck(x,y,i,0,1,player_num,0);
        // printf("isNoForbidden->%d\n",isNoForbidden);
        break;
      case 4:
        // printf("jud_num,case4,%s\n",direction[i]);
        ban4_cnt++; break;
      default: break;
    }
  }

  //連続している5連,長連を判断
  //また連続している三,四は重複しているので引く
  for(i = 0; i < 4; i++){
    switch(jud_5[i]){
      case 3:ban3_cnt--;
        // printf("jud_5,case3,%s\n",direction[i]);
        break;
      case 4:ban4_cnt--;
        // printf("jud_5,case4,%s\n",direction[i]);
        break;
      case 6:ban6_cnt++; break;
        // printf("jud_5,case6,%s\n",direction[i]);
        break;
      default: break;
    }
  }

  // printf("ban3_cnt->%d,ban4_cnt->%d,ban6_cnt->%d\n",ban3_cnt,ban4_cnt,ban6_cnt);

  //三三
  if(ban3_cnt>=2){
      if(isNoForbidden==0){
        // printf("三三です\n");
      return 1;
    }
  }
  //四四
  if(ban4_cnt>=2){
    // printf("四四です\n");
    return 1;
  }
  //長連
  if(ban6_cnt>=1){
    // printf("長連です\n");
    return 1;
  }
  return 0;
}