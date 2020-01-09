#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"

int maxlevel(int depth, int x, int y,int value);
int minlevel(int depth, int x, int y,int value);
// int maxlevel(int depth, int x, int y, int value, int alpha, int beta);
// int minlevel(int depth, int x, int y, int value, int alpha, int beta);

extern int board[15][15];
extern int dx[8];
extern int dy[8];
extern int my_num;
extern int enemy_num;

//評価
int my_value(int x, int y){
    if(!ban_judge(x, y, my_num))return -10000;
    switch(get_value(x, y, my_num)){
        case 2: return 10;
        case 3: return 100;
        case 4: return 1000;
        case 5: return 100000;
        default: return 1;
    }
}

int enemy_value(int x, int y){
    if(!ban_judge(x, y,enemy_num))return 10000;
    switch(get_value(x, y, enemy_num)){
        case 2: return -10;
        case 3: return -100;
        case 4: return -1000;
        case 5: return -100000;
        default: return -1;
    }
}

/******************minmax******************/
// int maxlevel(int depth, int x, int y,int value){

//     board[y][x] = my_num;        //仮に置く(自分)
//     int max = INT_MIN;

// 	if(depth == 0){            //一番低い子ノード
//         //評価
//         board[y][x] = 0;
//         printf("maxlevel----------depth-> %d,value->%d,x->%d,y->%d\n",depth,value,x+1,y+1);
//         return value;
// 	}
//     //相手が225のうち、どこに置くか
//     int xx = 0,yy = 0;
//     for(xx = SEARCH_START; xx < SEARCH_END; xx++){
//         for(yy = SEARCH_START; yy < SEARCH_END; yy++){
//             if(!board[yy][xx]){
//                 int score = minlevel(depth-1,xx,yy,value + enemy_value(xx,yy));
//                 if(max < score)max = score;
//             }
//         }
//     }

//     board[y][x] = 0;        //手を戻す
//     printf("depth-> %d,max->%d,x->%d,y->%d\n",depth,max,x+1,y+1);
//     return max;
// }

// int minlevel(int depth, int x, int y,int value){

//     board[y][x] = enemy_num;        //仮に置く(相手)
//     int min = INT_MAX;

//     if(depth == 0){            //一番低い子ノード
//         //評価(相手)
//         printf("minlevel----------depth-> %d,value->%d,x->%d,y->%d\n",depth,value,x+1,y+1);
//         board[y][x] = 0;
//         return value;
// 	}
//     int xx = 0,yy = 0;
//     for(xx = SEARCH_START; xx < SEARCH_END; xx++){
//         for(yy = SEARCH_START; yy < SEARCH_END; yy++){
//             if(!board[yy][xx]){
//                 int score = maxlevel(depth-1,xx,yy,value + my_value(xx,yy));
//                 if(min > score)min = score;
//             }
//         }
//     }

//     board[y][x] = 0;        //手を戻す
//     printf("depth-> %d,min->%d,x->%d,y->%d\n",depth,min,x+1,y+1);
//     return min;
// }


/******************alphabeta*******************/
int alpha_flag = 0, beta_flag = 0;      //最初の子ノード探索か判断のための値
int alpha_mark = 0, beta_mark = 0;
int alpha = 100, beta = -100;
int maxlevel(int depth, int x, int y, int value){
    int max = INT_MIN;      //子ノードの最大値
    board[y][x] = my_num;        //仮に置く(自分)
	int score = 0;              //それぞれの評価値

	if(depth == 0){            //一番低い子ノード
        //printf("x->%d,y->%d, max return %d (max)\n",x+1,y+1,value);
        //評価
        board[y][x] = 0;        //手を戻す
        return value;
	}

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){

            if(!board[yy][xx]){
                //printf("A\n");
                score = minlevel(depth-1,xx,yy,value + enemy_value(xx,yy));
                //printf("depth:%d(x:%d, y:%d) <- score:%d(x:%d, y:%d)\n", depth, x+1, y+1, score, xx+1, yy+1);
                if(!beta_flag && (depth!= 3))if(score >= beta){beta_mark = 1;max = score;break;}      //β値を上回ったら終了
                if(score > max){
                    max = score;        //最大値より大きかったら更新
                    //printf("maxchanged\n");
                    if(beta_flag && (depth != 3)){beta = max; /*printf("betachanged\n");*/}      //最初の子ノード探索であればβ値更新
                }
                //printf("x->%d, y->%d, max->%d, beta->%d, depth->%d,\n", xx+1, yy+1, max, beta, depth);
            }
        }
        if(beta_mark)break;
    }
    //printf("depth%d----------max%d-------------------score%d\n", depth, max, score);
    beta_flag = 0;
    board[y][x] = 0;
    if(beta_mark){beta_mark = 0;/*printf("betacut  x:%d, y:%d, max return %d\n", xx+1, yy+1, score);*/return score;}          //β値を上回ったらその時の評価値を返す
    if(max < beta){beta = max;/*printf("betachanged exception\n");*/}
    //printf("max return %d\n", max);
    return max;                             //最大値を返す
}

int minlevel(int depth, int x, int y, int value){
    int min = INT_MAX;      //子ノードの最小値
    board[y][x] = enemy_num;        //仮に置く(相手)
    int score = 0;              //それぞれの評価値

    if(depth == 0){            //一番低い子ノード
        //printf("x->%d,y->%d, min return %d (min)\n",x+1,y+1,value);
        //評価(相手)
        board[y][x] = 0;       //手を戻す
        return value;
	}

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){

            if(!board[yy][xx]){
                score = maxlevel(depth-1,xx,yy,value + my_value(xx,yy));
                //printf("depth:%d(x:%d, y:%d) <- score:%d(x:%d, y:%d)\n", depth, x+1, y+1, score, xx+1, yy+1);
                if(!alpha_flag)if(score <= alpha){alpha_mark = 1;min = score;break;}         //α値を下回ったら終了
                if(score < min){
                    min = score;            //最小値より小さかったら更新
                    //printf("minchanged\n");
                    if(alpha_flag){alpha = min; /*printf("alphachanged\n");*/}     //最初の子ノード探索であればα値更新
                }
                //printf("x->%d, y->%d, min->%d, alpha->%d, depth->%d, \n", xx+1, yy+1, min, alpha, depth);
            }
        }
        if(alpha_mark)break;
    }
    //printf("depth%d=========min%d============score%d\n", depth, min, score);
    alpha_flag = 0;
    beta_flag = 1;
    beta = -100;
    //printf("beta resettttttttttttttttttttttttttttttttt\n");
    board[y][x] = 0;
    if(alpha_mark){alpha_mark = 0;/*printf("alphacut  x:%d, y:%d, min return %d\n", x+1, yy+1, score);*/return score;}         //α値を下回ったらその時の評価値を返す
    //printf("min return %d\n", min);
    return min;                             //最小値を返す
}