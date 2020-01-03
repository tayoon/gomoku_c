#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"

// int maxlevel(int depth, int x, int y,int value);
// int minlevel(int depth, int x, int y,int value);
int maxlevel(int depth, int x, int y, int value, int alpha, int beta);
int minlevel(int depth, int x, int y, int value, int alpha, int beta);

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


int first_flag = 1;         //最初の子ノード探索か判断のための値
int maxlevel(int depth, int x, int y, int value, int alpha, int beta){
    int max = INT_MIN;      //子ノードの最大値
    board[y][x] = my_num;        //仮に置く(自分)
	int score;              //それぞれの評価値

    //printf("depth...%d-> ", depth);
	if(depth == 0){            //一番低い子ノード
        printf("maxlevel----------depth-> %d,value->%d,x->%d,y->%d\n",depth,value,x+1,y+1);
        //評価
        board[y][x] = 0;        //手を戻す
        return value;
	}
    if(depth == 2)first_flag = 1;
    // printf("x: %d, y: %d\n", x, y);
    // printf("flag: %d\n", first_flag);

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                printf("A\n");
                int score = minlevel(depth-1,xx,yy,value + enemy_value(xx,yy), alpha, beta);
                if(!first_flag)if(score >= beta)break;      //β値を上回ったら終了
                if(score > max){
                    max = score;        //最大値より大きかったら更新
                    if(first_flag)beta = max;       //最初の子ノード探索であればβ値更新
                }
            }
            printf("x->%d, y->%d, beta->%d, depth->%d,\n", xx+1, yy+1, beta, depth);
        }
    }
    first_flag = 0;
    board[y][x] = 0;
    if(score >= beta)return score;          //β値を上回ったらその時の評価値を返す
    return max;                             //最大値を返す
}

int minlevel(int depth, int x, int y, int value, int alpha, int beta){
    int min = INT_MAX;      //子ノードの最小値
    board[y][x] = enemy_num;        //仮に置く(相手)
    int score;              //それぞれの評価値

    //printf("depth...%d-> ", depth);
    if(depth == 0){            //一番低い子ノード
        printf("minlevel----------depth-> %d,value->%d,x->%d,y->%d\n",depth,value,x+1,y+1);
        //評価(相手)
        board[y][x] = 0;       //手を戻す
        return value;
	}
    if(depth == 2)first_flag = 1;
    printf("x: %d, y: %d\n", x, y);
    // printf("flag: %d\n", first_flag);

    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                int score = maxlevel(depth-1,xx,yy,value + my_value(xx,yy), alpha, beta);
                if(!first_flag)if(score <= alpha)break;         //α値を下回ったら終了
                if(score < min){
                    min = score;            //最小値より小さかったら更新
                    if(first_flag)alpha = min;      //最初の子ノード探索であればα値更新
                }
            }
            printf("x->%d, y->%d, alpha->%d, depth->%d, \n", xx+1, yy+1, alpha, depth);
        }
    }

    first_flag = 0;
    board[y][x] = 0;
    if(score <= alpha)return score;         //α値を下回ったらその時の評価値を返す
    return min;                             //最小値を返す
}