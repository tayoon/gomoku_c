#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "judge.h"

extern int board[15][15];
extern int value_board[15][15];

extern int ban_flag;		//禁じ手か否か
extern int win_flag;		//勝利したか否か
extern int draw_flag;		//引き分けか否か
extern int black_flag;  //先手
extern int white_flag;  //後手
extern int ban;	        //相手に禁じ手があるかどうか
extern int start_flag_2;	//先手の2手目用

//相手の数字を受け取る
//受け取った際に予め1引いておく
void recieveEnemy(char *buffer,int *enemy_x,int *enemy_y){
  char *ptr;
  ptr = strtok(buffer,",");
  *enemy_x = (atoi(ptr)-1);
  ptr = strtok(NULL,",");
  *enemy_y = (atoi(ptr)-1);
  setBoard(*enemy_x,*enemy_y,ENEMY_NUM);
}

//先手の一手目
void blackOne(int *x,int *y)
{
  *x = 7, *y = 7;
  setBoard(*x,*y,MY_NUM);
  black_flag = 0;
  start_flag_2 = 1;
}

//先手の二手目
void blackTwo(char *buffer,int *x,int *y){
  int enemy_x,enemy_y;

  recieveEnemy(buffer,&enemy_x,&enemy_y);

  //縦に並べられたら
	if(!(enemy_x-7)){
		*x = enemy_x - 1;
		*y = enemy_y + 1;
	}
  //横に並べられたら
	else if(!(enemy_y-7)){
		*x = enemy_x + 1;
		*y = enemy_y - 1;
  }
  //斜めに並べられたら
  else{
    if(!((enemy_x-7)-(enemy_y-7))){*x = 8; *y = 6;}
    else{*x = 6; *y = 6;}
  }
  setBoard(*x,*y,MY_NUM);
  start_flag_2 = 0;
}

//後手の一手目
void whiteOne(char *buffer,int *x,int *y){

  int enemy_x,enemy_y;

  recieveEnemy(buffer,&enemy_x,&enemy_y);

  while(1){
    srand((unsigned)time(NULL));
    *x = rand() % 3 + 6;
    *y = rand() % 3 + 6;
    if(isStone(*x,*y,SPACE_NUM))break;
  }
  setBoard(*x,*y,MY_NUM);
  white_flag = 0;
}

void think(int *x,int *y){

  char* delim = " ************************ ";

  int i = 0;
  int j = 0;
  int max = INT_MIN;
  int maxX,maxY;

  //全探索
  for(i = 0; i < 15; i++){
    for(j = 0; j < 15; j++){
      if(!isStone(j,i,SPACE_NUM)){printf("#,  ");continue;}					//碁石を既に置いていると
      if(ban){
        if(ban_judge(j, i, ENEMY_NUM)){printf("c, ");continue;}			//敵の禁じ手の場所を表示
      }else if(!ban){
        if(ban_judge(j, i, MY_NUM)){printf("b, ");continue;}				//自分の禁じ手の場所を表示
      }
      if(checkNonValue(j, i)){printf("n, ");continue;}							//ここに置いても意味がないということ
      int score = get_value(j, i, MY_NUM) + get_value(j, i, ENEMY_NUM);
      if(max <= score){
        max = score;
        maxX = j;
        maxY = i;
      }
      // printf("%d, ", score);
      printf("V, ");
    }
    printf("\n");
  }
  //現在の盤面の状態と次に置くべき場所を表示
  for(i = 0; i < 15; i++){
    for(j = 0; j < 15; j++){
      if(i==maxY && j==maxX)printf(" ● ");
      else if(isStone(j,i,MY_NUM))printf(" ○ ");
      else if(isStone(j,i,ENEMY_NUM))printf(" × ");
      else printf(" ― ");
    }
    printf("\n");
  }
  *x = maxX;
  *y = maxY;
  printf("x -> %d,y -> %d\n",*x,*y);
  setBoard(*x,*y,MY_NUM);
  if(checkDraw2()){
    printf("%s引き分けなんだねぇ%s\n",delim,delim);
    draw_flag = 1;
  }
}

//禁じ手デバッグ用
void randomPut(int *x,int*y){
  while(1){
    srand((unsigned)time(NULL));
    *x = rand() % 15;
    *y = rand() % 15;
    if(isStone(*x,*y,SPACE_NUM))break;
  }
  setBoard(*x,*y,MY_NUM);
}