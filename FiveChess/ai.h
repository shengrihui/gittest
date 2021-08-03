#pragma once
#define N 1048576	//4**10-1 +1


void read_file();
void upgrad_w(int winner);
void save_file();
void Condition(int condition[4], int board[25][25], int x, int y);
int point_score(int board[25][25], int x, int y);
int board_score(int board[25][25]);
int get_max_min(int leaves[225], int step);
int get_max_min_index(int leaves[225], int player);
void board_count_Copy(int board[25][25], int board_cpy[25][25], int count[25][25], int count_cpy[25][25], int i, int j, int player);
void rand_chess(int board[25][25], int* x, int* y);
void upgrate_count(int count[25][25], int board[25][25], int x, int y);
int* shuffle(int  n);
void _pre_n(int count[25][25], int pre_n[50][2]);
void init_board(int board[25][25], int count[25][25]);
int next_step(int board[25][25], int count[25][25], int player, int forward_step, int* x, int* y);
//void Game(int board[25][25], int count[25][25]);
void pr(int board[25][25]);
//int Zero(int Board[][25]);
int Iswin_2(int x, int y, int Board[25][25], int player);
void Record_step(int board[25][25], int x, int y);
void m_w();
void print_w();