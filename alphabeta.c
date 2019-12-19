#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"

int maxlevel(int depth, int x, int y,int value);
int minlevel(int depth, int x, int y,int value);
// int maxlevel(int depth, int x, int y, int alpha, int beta);
// int minlevel(int depth, int x, int y, int alpha, int beta);

extern int board[15][15];
extern int dx[8];
extern int dy[8];
extern int my_num;
extern int enemy_num;

//評価
int my_value(int x, int y){
    if(!ban_judge(x, y, my_num))return -100;
    switch(win_judge(x, y, my_num)){
        case 2: return 50;
        case 3: return 80;
        case 4: return 100;
        case 5: return 100000;
        default: return 0;
    }
}

int enemy_value(int x, int y){
    if(!ban_judge(x, y,enemy_num))return 100;
    switch(win_judge(x, y, enemy_num)){
        case 2: return -50;
        case 3: return -80;
        case 4: return -100;
        case 5: return -100000;
        default: return 0;
    }
}


int maxlevel(int depth, int x, int y,int value){

    board[y][x] = my_num;        //仮に置く(自分)
    int max = INT_MIN;
	int score;
	if(depth == 0){            //一番低い子ノード
        //評価
        board[y][x] = 0;
        return my_value(x, y);
	}
    //相手が225のうち、どこに置くか
    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                score = minlevel(depth-1,xx,yy,value + enemy_value(xx,yy));
            }
            if(max < score)max = score;
        }
    }

    board[y][x] = 0;        //手を戻す
    return max;
}

int minlevel(int depth, int x, int y,int value){

    board[y][x] = enemy_num;        //仮に置く(相手)
    int min = INT_MAX;
    int score;

    if(depth == 0){            //一番低い子ノード
        //評価(相手)
        board[y][x] = 0;
        return value;
	}
    int xx = 0,yy = 0;
    for(xx = SEARCH_START; xx < SEARCH_END; xx++){
        for(yy = SEARCH_START; yy < SEARCH_END; yy++){
            if(!board[yy][xx]){
                score = maxlevel(depth-1,xx,yy,value + my_value(xx,yy));
            }
            if(min > score)min = score;
        }
    }

    board[y][x] = 0;        //手を戻す
    return min;
}


// int first_flag = 1;         //最初の子ノード探索か判断のための値

// int maxlevel(int depth, int x, int y, int alpha, int beta){
//     int max = INT_MIN;      //子ノードの最大値
//     board[y][x] = 1;        //仮に置く(自分)
// 	int score;              //それぞれの評価値

//     printf("depth...%d-> ", depth);
// 	if(depth == 0){            //一番低い子ノード
//         //評価
//         board[y][x] = 0;        //手を戻す
//         return value(x, y);
// 	}
//     printf("x: %d, y: %d\n", x, y);
//     printf("flag: %d\n", first_flag);

// 	for(int i = 0; i < 8; i++){             //注目しているマスの周り8マスを調査
//         //printf("x:%d,y:%d  ", x+dx[i], y+dy[i]);
//         if(board[y+dy[i]][x+dx[i]])continue;        //既にあったらパス
//         score = minlevel(depth-1, x+dx[i], y+dy[i], alpha, beta);
//         board[y][x] = 0;        //手を戻す
//         printf("min%d:%d(%d, %d)\n", x+dx[i], y+dy[i], score, i);
//         if(!first_flag)if(score >= beta)break;      //β値を上回ったら終了
//         if(score > max){
//             max = score;        //最大値より大きかったら更新
//             if(first_flag)beta = max;       //最初の子ノード探索であればβ値更新
//         }
//     }
//     printf("\n");
//     first_flag = 0;
//     if(score >= beta)return score;          //β値を上回ったらその時の評価値を返す
//     return max;                             //最大値を返す
// }

// int minlevel(int depth, int x, int y, int alpha, int beta){
//     int min = INT_MIN;      //子ノードの最小値
//     board[y][x] = 2;        //仮に置く(相手)
//     int score;              //それぞれの評価値

//     printf("%d-> ", depth);
//     if(depth == 0){            //一番低い子ノード
//         //評価(相手)
//         board[y][x] = 0;        //手を戻す
//         return enemy_value(x, y);
// 	}
//     printf("x: %d, y: %d\n", x, y);
//     printf("flag: %d\n", first_flag);

//     for(int i = 0; i < 8; i++){
//         if(board[y+dy[i]][x+dx[i]])continue;
//         score = maxlevel(depth-1, x+dx[i], y+dy[i], alpha, beta);
//         board[y][x] = 0;        //手を戻す
//         printf("max%d:%d(%d, %d)\n", x+dx[i], y+dy[i], score, i);
//         if(!first_flag)if(score <= alpha)break;         //α値を下回ったら終了
//         if(score < min){
//             min = score;            //最小値より小さかったら更新
//             if(first_flag)alpha = min;      //最初の子ノード探索であればα値更新
//         }
//     }
//     printf("\n");
//     first_flag = 0;
//     if(score <= alpha)return score;         //α値を下回ったらその時の評価値を返す
//     return min;                             //最小値を返す
// }