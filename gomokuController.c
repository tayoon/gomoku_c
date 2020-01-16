#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "judge.h"

extern int board[15][15];
extern int value_board[15][15];

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
void blackOne(int *x,int *y,int *black_flag,int *start_flag_2)
{
  *x = 7, *y = 7;
  setBoard(*x,*y,MY_NUM);
  *black_flag = 0;
  *start_flag_2 = 1;
}

//先手の二手目
void blackTwo(char *buffer,int *x,int *y,int *start_flag_2){
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
  *start_flag_2 = 0;
}

//後手の一手目
void whiteOne(char *buffer,int *x,int *y,int *white_flag){

  int enemy_x,enemy_y;

  recieveEnemy(buffer,&enemy_x,&enemy_y);

  while(1){
    srand((unsigned)time(NULL));
    *x = rand() % 3 + 6;
    *y = rand() % 3 + 6;
    // if(!board[*y-1][*x-1])break;
    if(isStone(*x,*y,SPACE_NUM))break;
  }
  setBoard(*x,*y,MY_NUM);
  *white_flag = 0;
}
