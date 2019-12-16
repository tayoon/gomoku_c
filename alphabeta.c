#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//int maxlevel(int depth, int x, int y);
//int minlevel(int depth, int x, int y);
int maxlevel(int depth, int x, int y, int alpha, int beta);
int minlevel(int depth, int x, int y, int alpha, int beta);

extern int board[17][17];
extern int dx[8];
extern int dy[8];

//評価
int value(int x, int y){
    if(!ban_judge(x, y))return -100;
    if(win_judge(x, y) == 3)return 50;
    if(win_judge(x, y) == 4)return 80;
    if(win_judge(x, y) == 5)return 100;
    return 0;
}

int enemy_value(int x, int y){
    if(!ban_judge(x, y))return +100;
    if(win_judge(x, y) == 3)return -50;
    if(win_judge(x, y) == 4)return -80;
    if(win_judge(x, y) == 5)return -100;
    return 0;
}

/*
int maxlevel(int depth, int x, int y){
    board[y][x] = 1;        //仮に置く(自分)
    int max = INT_MIN;
	int score;

	if(depth == 0){            //一番低い子ノード
        //評価
        return value(x, y);
	}

	for(int i = 0; i < 8; i++){             //注目しているマスの周り8マスを調査
        if(board[y+dy[i]][x+dx[i]])continue;        //既にあったらパス
        score = minlevel(depth-1, x+dx[i], y+dy[i]);
        if(score >= max){
            max = score;
        }
    }
    board[y][x] = 0;        //手を戻す
    return max;
}

int minlevel(int depth, int x, int y){
    board[y][x] = 2;        //仮に置く(相手)
    int min = INT_MAX;
    int score;

    if(depth == 0){            //一番低い子ノード
        //評価(相手)
        return enemy_value(x, y);
	}

    for(int i = 0; i < 8; i++){
        if(board[y+dy[i]][x+dx[i]])continue;
        score = maxlevel(depth-1, x+dx[i], y+dy[i]);
        if(score <= min){
            min = score;
        }
    }
    board[y][x] = 0;        //手を戻す
    return min;
}
*/

int maxlevel(int depth, int x, int y, int alpha, int beta){
    board[y][x] = 1;        //仮に置く(自分)
	int score;

	if(depth == 0){            //一番低い子ノード
        //評価
        board[y][x] = 0;        //手を戻す
        return value(x, y);
	}

	for(int i = 0; i < 8; i++){             //注目しているマスの周り8マスを調査
        if(board[y+dy[i]][x+dx[i]])continue;        //既にあったらパス
        score = minlevel(depth-1, x+dx[i], y+dy[i], alpha, beta);
        if(score >= alpha){
            alpha = score;
            if(alpha <= beta)break;
        }
    }
    board[y][x] = 0;        //手を戻す
    if(alpha <= beta)return beta;
    return alpha;
}

//alpha
int minlevel(int depth, int x, int y, int alpha, int beta){
    board[y][x] = 2;        //仮に置く(相手)
    int score;

    if(depth == 0){            //一番低い子ノード
        //評価(相手)
        board[y][x] = 0;        //手を戻す
        return enemy_value(x, y);
	}

    for(int i = 0; i < 8; i++){
        if(board[y+dy[i]][x+dx[i]])continue;
        score = maxlevel(depth-1, x+dx[i], y+dy[i], alpha, beta);
        if(score <= beta){
            beta = score;
            if(beta <= alpha)break;
        }
        
    }
    board[y][x] = 0;        //手を戻す
    if(beta <= alpha)return alpha;
    return beta;
}