#include <board.h>

int board[15][15];
int dx[8];
int dy[8];

int LeUp_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][(dir_x-1) + 1] == 2)rev++;if(board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)rev++;	//逆方向
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][(dir_x-1) - go])break;
			else if(board[(dir_y-1) - go][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][(dir_x-1) - 1] && board[(dir_y-1) - 2][(dir_x-1) - 2] == 2)return count + rev;
	else return count;
}

int Up_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][dir_x-1] == 2)rev++;if(board[(dir_y-1) + 2][dir_x-1] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][dir_x-1] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][dir_x-1])break;
			else if(board[(dir_y-1) - go][dir_x-1] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][dir_x-1] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][dir_x-1] && board[(dir_y-1) - 2][dir_x-1] == 2)return count + rev;
	else return count;
}

int RiUp_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) + 1][(dir_x-1) - 1] == 2)rev++;if(board[(dir_y-1) + 2][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) - go][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) - go][(dir_x-1) + go])break;
			else if(board[(dir_y-1) - go][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[(dir_y-1) - go][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) - 1][(dir_x-1) + 1] && board[(dir_y-1) - 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int Left_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[dir_y-1][(dir_x-1) + 1] == 2)rev++;if(board[dir_y-1][(dir_x-1) + 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[dir_y-1][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[dir_y-1][(dir_x-1) - go])break;
			else if(board[dir_y-1][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[dir_y-1][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[dir_y-1][(dir_x-1) - 1] && board[dir_y-1][(dir_x-1) - 2] == 2)return count + rev;
	else return count;
}

int Right_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[dir_y-1][(dir_x-1) - 1] == 2)rev++;if(board[dir_y-1][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[dir_y-1][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[dir_y-1][(dir_x-1) + go])break;
			else if(board[dir_y-1][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[dir_y-1][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[dir_y-1][(dir_x-1) + 1] && board[dir_y-1][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int LeDo_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) - 1][(dir_x-1) + 1] == 2)rev++;if(board[(dir_y-1) - 2][(dir_x-1) + 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][(dir_x-1) - go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][(dir_x-1) - go])break;
			else if(board[(dir_y-1) + go][(dir_x-1) - go] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][(dir_x-1) - go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][(dir_x-1) + 1] && board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int Down_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) - 1][dir_x-1] == 2)rev++;if(board[(dir_y-1) - 2][dir_x-1] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][dir_x-1] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][dir_x-1])break;
			else if(board[(dir_y-1) + go][dir_x-1] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][dir_x-1] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][dir_x-1] && board[(dir_y-1) + 2][dir_x-1] == 2)return count + rev;
	else return count;
}

int RiDo_judge(int dir_y, int dir_x, int count, int a_cnt){
	int rev = 0;
	if(board[(dir_y-1) - 1][(dir_x-1) - 1] == 2)rev++;if(board[(dir_y-1) - 2][(dir_x-1) - 2] == 2)rev++;
	int go = 1;
	while(1){
		if(!board[(dir_y-1) + go][(dir_x-1) + go] && !a_cnt){
			go++;
			if(!board[(dir_y-1) + go][(dir_x-1) + go])break;
			else if(board[(dir_y-1) + go][(dir_x-1) + go] == 2)a_cnt++;
		}else if(board[(dir_y-1) + go][(dir_x-1) + go] == 2){
			count++;
			go++;
		}else break;
	}
	if(!board[(dir_y-1) + 1][(dir_x-1) + 1] && board[(dir_y-1) + 2][(dir_x-1) + 2] == 2)return count + rev;
	else return count;
}

int ban_judge(int dir_y, int dir_x){		//board[dir_y-1][dir_x-1]のジャッジ
	int ban3_cnt = 0, ban4_cnt = 0, ban6_cnt = 0, five_cnt = 0;
	int a, b, c, d, e, f, g, h;

	if((a = Left_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((b = Right_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((c = Up_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((d = Down_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((e = RiUp_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((f = LeDo_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((g = LeUp_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;
	if((h = RiDo_judge(dir_y, dir_x, 0, 0)) >= 2)ban3_cnt++;

	if(a >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(b >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(c >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(d >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(e >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(f >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(g >= 3){ban3_cnt = 0;ban4_cnt++;}
	if(h >= 3){ban3_cnt = 0;ban4_cnt++;}

	//if(a >= 4 || b >= 4 || c >= 4 || d >= 4 || e >= 4 || f >= 4 || g >= 4 || h >= 4){ban4_cnt = 0;five_cnt++;}
	if(a >= 5 || b >= 5 || c >= 5 || d >= 5 || e >= 5 || f >= 5 || g >= 5 || h >= 5){
		if(five_cnt != ban6_cnt)five_cnt++;
		else if(five_cnt == ban6_cnt)ban6_cnt++;
	}
	
	printf("3: %d, 4: %d, 5: %d, 6: %d\n", ban3_cnt, ban4_cnt, five_cnt, ban6_cnt);
	printf("leup: %d, up: %d, riup: %d, left: %d, right: %d, ledo: %d, down: %d, rido: %d\n",
			a, b, c, d, e, f, g, h);
	if(ban3_cnt >= 2 || ban4_cnt >= 2 || ban6_cnt)return 0;
	else return 1;
}