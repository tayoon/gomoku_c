#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"

int maxlevel(int depth, int x, int y);
int minlevel(int depth, int x, int y);
// int maxlevel(int depth, int x, int y, int value, int alpha, int beta);
// int minlevel(int depth, int x, int y, int value, int alpha, int beta);

extern int value_board[15][15];
extern int board[15][15];
extern int dx[8];
extern int dy[8];

// //評価
// int my_value(int x, int y){
//     if(!ban_judge(x, y, MY_NUM))return -10000;
//     switch(get_value(x, y, MY_NUM)){
//         case 2: return 10;
//         case 3: return 100;
//         case 4: return 1000;
//         case 5: return 100000;
//         default: return 1;
//     }
// }

// int enemy_value(int x, int y){
//     if(!ban_judge(x, y,ENEMY_NUM))return 10000;
//     switch(get_value(x, y, ENEMY_NUM)){
//         case 2: return -10;
//         case 3: return -100;
//         case 4: return -1000;
//         case 5: return -100000;
//         default: return -1;
//     }
// }

/******************alphabeta*******************/
int alpha_flag = 1, beta_flag = 1;      //最初の子ノード探索か判断のための値
int alpha_mark = 0, beta_mark = 0;
int alpha = 100, beta = -100;

int maxlevel(int depth, int x, int y){
    int max = INT_MIN;      //子ノードの最大値
    // board[y][x] = MY_NUM;        //仮に置く(自分)
    setBoard(x,y,MY_NUM);
	int score = 0;              //それぞれの評価値

	if(depth == 0){            //一番低い子ノード
        //評価
        int value = getValueOfBoard();
        resetBoard(x,y,MY_NUM);        //手を戻す
        return value;
	}

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                if(ban_judge(xx,yy,ENEMY_NUM)){
                    score = minlevel(depth-1,xx,yy);
                    if(!beta_flag && (depth!= 3))if(score >= beta){beta_mark = 1;max = score;break;}      //β値を上回ったら終了
                    if(score > max){
                        max = score;        //その評価値が最大値より大きかったら更新
                        if(beta_flag && (depth != 3)){beta = max; /*printf("betachanged\n");*/}      //最初の子ノード探索であればβ値更新
                    }
                }
            }
        }
        if(beta_mark)break;
    }
    beta_flag = 0;
    resetBoard(x,y,MY_NUM);
    if(beta_mark){beta_mark = 0;return score;}          //β値を上回ったらその時の評価値を返す
    if(max < beta){beta = max;}             //子ノードのmax値がbetaを超えなかった時にbeta値更新
    return max;                             //最大値を返す
}

int minlevel(int depth, int x, int y){
    int min = INT_MAX;      //子ノードの最小値
    // board[y][x] = ENEMY_NUM;    //仮に置く(相手)
    setBoard(x,y,ENEMY_NUM);
    int score = 0;              //それぞれの評価値

    if(depth == 0){            //一番低い子ノード
        //評価(相手)
        // board[y][x] = 0;       //手を戻す
        int value = getValueOfBoard();
        resetBoard(x,y,ENEMY_NUM);
        return value;
	}

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                if(ban_judge(xx,yy,MY_NUM)){
                    score = maxlevel(depth-1,xx,yy);
                    if(!alpha_flag)if(score <= alpha){alpha_mark = 1;min = score;break;}         //α値を下回ったら終了
                    if(score < min){
                        min = score;            //最小値より小さかったら更新
                        if(alpha_flag){alpha = min; /*printf("alphachanged\n");*/}     //最初の子ノード探索であればα値更新
                    }
                }
            }
        }
        if(alpha_mark)break;
    }
    alpha_flag = 0;
    beta_flag = 1;          //beta値リセットするため
    beta = -100;            //beta値の初期値をリセット
    // board[y][x] = 0;
    resetBoard(x,y,ENEMY_NUM);
    if(alpha_mark){alpha_mark = 0;return score;}         //α値を下回ったらその時の評価値を返す
    return min;                             //最小値を返す
}