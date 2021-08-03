#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
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

 int weights[N] = { 0 };
int step_record[255][4] = { 0 };	//记录每一步的情况
int Step = 0;		//一共多少步了

//读文件
void read_file()
{
	FILE* fp = fopen("weights.txt", "r");
	int i;
	if (fp == NULL)
	{
		for (i = 0; i < N; i++)
		{
			weights[i] = 0;
		}
		return;
	}
	for (i = 0; i < N; i++) {
		fscanf(fp, "%d", &weights[i]);
	}
	fclose(fp);
}

//一局结束后更新，然后保存
void upgrad_w(int winner)
{
	int i, j;
	for (i = 0; i < Step; i += 2)
	{
		for (j = 0; j < 4; j++)
		{
			if (winner == 1)	//赢了
			{
				weights[step_record[i][j]]++;
				weights[step_record[i + 1][j]]--;
			}
			else if (winner == 2)
			{
				weights[step_record[i][j]]--;
				weights[step_record[i + 1][j]]++;
			}
		}
	}
	save_file();
}

//写文件
void save_file()
{
	FILE* fp = fopen("weights.txt", "w");
	int i;
	for (i = 0; i < N; i++)
		fprintf(fp, "%d ", weights[i]);
	fclose(fp);
}


void Condition(int condition[4], int board[25][25], int x, int y)
{
	int i, ex;  //i循环变量，ex次方数--4进制转10进制
	//算横竖撇捺分别对应的10进制数（weights的下标）
	ex = 9;
	for (i = -5; i <= 5; i++)
	{
		if (i == 0)continue;	//(z,y)自己不算
		condition[0] += board[x + i][y] * pow(4, ex);	//x+,y=
		condition[1] += board[x + i][y + i] * pow(4, ex);	//x+,y+
		condition[2] += board[x][y + i] * pow(4, ex);	//x=,y+
		condition[3] += board[x - i][y + i] * pow(4, ex);	//x-,y+
		ex--;
	}
}

//点Ix,y)的分数
int point_score(int board[25][25], int x, int y)
{
	int i; //i循环变量，ex次方数--4进制转10进制
	int max = 0, temp = 0;	//max取四个里面的最大，temp临时
	int condition[4] = { 0,0,0,0 };	//4中情况，横竖撇捺
	Condition(condition, board, x, y);


	for (i = 0; i < 4; i++)
	{
		//printf("%d \n", weights[condition[i]]);
		//step_record[Step][i] = condition[i];
		//printf("%d", condition[i]);
		temp = weights[condition[i]];
		if (temp > max)
			max = temp;
	}
	return max;
}

//整个盘面的分数
int board_score(int board[25][25])
{
	int i, j, score = 0;
	for (i = 5; i <= 19; i++)
	{
		for (j = 5; j <= 19; j++)
		{
			//pr(board);
			if (board[i][j] == 0)
			{
				score += point_score(board, i, j);
			}
		}
	}
	return score;
}

int get_max_min(int leaves[], int step) //
{
	int ret, i = 0;
	for (i = 0; i < 50; i++)
	{
		if (leaves[i] != -123456)
		{
			ret = leaves[i];
			break;
		}
	}
	for (i = 0; i < 50; i++)
	{
		if (step % 2 == 1)	//自己 求最大值
		{
			if (ret < leaves[i])ret = leaves[i];
		}
		else if (step % 2 == 0)
		{
			if (leaves[i] != -123456)
			{
				if (ret > leaves[i])ret = leaves[i];
			}
		}
	}
	return ret;
}
int get_max_min_index(int leaves[], int player)
{
	int m = get_max_min(leaves, player);
	for (int i = 0; i < 50; i++)
	{
		if (leaves[i] == m)
			return i;
	}
}

//新展开一种棋盘情况
void board_count_Copy(int board[25][25], int board_cpy[25][25],
	int count[25][25], int count_cpy[25][25],
	int i, int j, int player)
{
	int x, y;
	for (x = 0; x < 25; x++)
	{
		for (y = 0; y < 25; y++)
		{
			count_cpy[x][y] = count[x][y];
			if (x == i && y == j)
				board_cpy[x][y] = player;
			else
				board_cpy[x][y] = board[x][y];
		}
	}
}


//随机下
void rand_chess(int board[25][25], int* x, int* y)
{
	int i, j;
	while (1)
	{
		i = rand() % 15 + 5;
		j = rand() % 15 + 5;
		if (board[i][j] == 0)
		{
			*x = i;
			*y = j;
			break;
		}
	}
}


//更新count
void upgrate_count(int count[25][25], int board[25][25], int x, int y)
{
	int i, x0, y0;
	for (i = 5; i > 0; i--)
	{
		for (x0 = x - i; x0 <= x + i; x0++)
		{
			for (y0 = y - i; y0 <= y + i; y0++)
			{
				if (x0 >= 5 && x0 <= 19 && y0 >= 5 && y0 <= 19)
				{
					//在范围内，且盘面上没有棋
					if (board[x0][y0] == 0)
						count[x0][y0]++;
				}
			}
		}
	}
	count[x][y] = 0;
}


int* shuffle(int  n)
{
	int* perm = (int*)malloc(sizeof(int) * n);  //分配n个int的存储空间，返回第一个的地址
	int i;
	//先生成一个有序的数组
	for (i = 0; i < n; i++)
	{
		*(perm + i) = i;
	}

	int t, temp, j;
	for (i = 0; i < 10; i++)  //做10次循环，每次进行乱序
	{
		for (j = 0; j < n; j++)
		{
			t = rand() % n;
			if (t == j)continue;
			temp = perm[j];
			perm[j] = perm[t];
			perm[t] = temp;
		}
	}
	return perm;
}

void _pre_n(int count[25][25], int pre_n[50][2])
{
	int i, j, t;
	int temp_xy[281][225][2] = { 0 };
	//记录坐标  [值][出现次数][xy坐标}
	// [i][j][0/1] i值第j次出现的x/y坐标
	//280= 8 * 5 + 16 * 4 + 24 * 3 + 32 * 2 + 40
	int temp_c[281] = { 0 };	//计数
	for (i = 5; i <= 19; i++)
	{
		for (j = 5; j <= 19; j++)
		{
			t = count[i][j];	//取(i,j)的值
			temp_xy[t][temp_c[t]][0] = i;	//t值temt_c[t[次出现的x坐标
			temp_xy[t][temp_c[t]][1] = j;
			temp_c[t]++;
		}
	}

	int k = 0;	//用于限定多少个数
	int* a = NULL;
	for (i = 280; i >= 0; i--)
	{
		t = temp_c[i];	//t=i值的次数
		if (t == 0)continue;
		a = shuffle(t);	//生成0到t的随机数组

		for (j = 0; j < t; j++)
		{
			pre_n[k][0] = temp_xy[i][a[j]][0];
			pre_n[k][1] = temp_xy[i][a[j]][1];
			if (++k == 50)return;	//最多50个
		}

	}

}

//初始化25*25的盘面
void init_board(int board[25][25], int count[25][25])
{
	int i, j;
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 25; j++) {
			count[i][j] = 0;
			if (i >= 5 && i <= 19 && j >= 5 && j <= 19)
				board[i][j] = 0;
			else
				board[i][j] = 3;
		}
	}
}


int next_step(int board[25][25], int count[25][25],
	int player, int forward_step, int* x, int* y)
{
	int board_cpy[25][25] = { 0 };
	int count_cpy[25][25] = { 0 };
	int i, j, m, n;
	int leaves[50] = { 0 }, l = 0;


	int pre_50[50][2] = { 0 };
	_pre_n(count, pre_50);

	/*pr(count);
	printf("\n");
	pr(board);*/
	for (n = 0; n < 50; n++)
	{
		//取出坐标(i,j)
		i = pre_50[n][0];
		j = pre_50[n][1];

		if (Iswin_2(i, j, board, player) == 1 && forward_step == 1)
		{
			*x = i; *y = j;
			return 0;
		}

		board_count_Copy(board, board_cpy, count, count_cpy, i, j, player);
		if (forward_step == 2)
			leaves[l++] = board_score(board_cpy);
		else
			leaves[l++] = next_step(board_cpy, count_cpy,
				3 - player, forward_step + 1, NULL, NULL);

	}

	if (forward_step > 1) {
		return get_max_min(leaves, forward_step);
	}
	else
	{
		int index = get_max_min_index(leaves, player);
		*x = pre_50[index][0];
		*y = pre_50[index][1];
		//printf("index:%d  %d %d \n",index, *x, *y);
	}
}

//void Game(int board[25][25], int count[25][25])
//{
//	int player = 1;
//	int x, y, m;
//	time_t start, end;
//	init_board(board, count);
//	Step = 0;
//	while (1)
//	{
//		start = time(NULL);
//		if ((player == 2 && (Step % 3) == (rand() % 4)) || Step < 4)
//		{
//			//前4步或者偶尔让玩家二随机下
//			rand_chess(board, &x, &y);
//		}
//		else
//		{
//			next_step(board, count, player, 1, &x, &y);
//		}
//
//		board[x][y] = player;
//		upgrate_count(count, board, x, y);
//		Record_step(board, x, y);
//		player = 3 - player;
//		Step++;
//
//
//		end = time(NULL);
//		//printf("Step:%d x:%d y:%d time:%d\n", Step, x - 5, y - 5, end - start);
//		if (Iswin(x, y, board, player) == 1)
//		{
//			//pr(board);
//			break;
//		}
//	}
//	upgrad_w(player);
//
//}

void Record_step(int board[25][25], int x, int y)
{
	int condition[4] = { 0,0,0,0 };
	Condition(condition, board, x, y);
	int i;
	for (i = 0; i < 4; i++)
	{
		step_record[Step][i] = condition[i];
	}
}

void pr(int board[25][25])
{
	int i, j;
	printf("   ");
	for (i = 5; i < 20; i++)
		printf("%2d ", i);
	printf("\n");
	for (i = 5; i < 20; i++)
	{
		printf("%2d ", i);
		for (j = 5; j < 20; j++)
			printf("%2d ", board[i][j]);
		printf("\n");
	}
	printf("\n");
}
int Zero(int Board[][25])
{
	int zero = 0, i, j;
	for (i = 5; i <= 19; i++)
	{
		for (j = 5; j <= 19; j++)
		{
			if (Board[i][j] == 0)
				zero++;
		}
	}
	return zero;
}
int Iswin_2(int x, int y, int Board[25][25], int player)
{
	int c[4] = { 1,1,1,1 };
	//
	int m[4] = { 3,3,3,3 };
	int i, j, dx, dy, x2, y2;
	//平局返回-1
	int zero = Zero(Board);

	if (zero == 0)return -1;

	//j 四种模式（方向）
	for (j = 0; j < 4; j++)
	{
		//i 以x,y开始往外走四层
		for (i = 1; i <= 4; i++)
		{
			//根据横竖撇捺选择dx，dy
			switch (j)
			{
			case 0:dx = i; dy = i; break;	//捺
			case 1:dx = i; dy = 0; break;	//横   x是横着的
			case 2:dx = i; dy = -i; break;	//撇
			case 3:dx = 0; dy = i; break;	//竖
			}


			switch (m[j])
			{
			case 3:	//两个方向
				x2 = x + dx; y2 = y + dy;
				if (x2 < 5 || x2 >= 20 || y2 < 5 || y2 >= 20 || Board[x2][y2] != player)
				{
					m[j] = 2;
				}
				else
				{
					c[j]++;
				}
			case 2:	//比3少一个方向
				x2 = x - dx; y2 = y - dy;
				if (x2 < 5 || x2 >= 20 || y2 < 5 || y2 >= 20 || Board[x2][y2] != player)
				{
					if (m[j] == 2)m[j] = 0;
					else  m[j] = 1;
				}
				else
				{
					c[j]++;
				}
				break;
			case 1:
				x2 = x + dx;	y2 = y + dy;
				if (x2 < 5 || x2 >= 20 || y2 < 5 || y2 >= 20 || Board[x2][y2] != player)
				{
					m[j] = 0;
				}
				else
				{
					c[j]++;
				}
			case 0:
				break;
			}
		}

		if (c[j] >= 5)
			return 1;
	}
	return 0;
}


//打印非0的weight
void print_w()
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		if (weights[i] != 0)
		{
			printf("%d  %d\n", i, weights[i]);
		}
	}
}

//对不同产生的weights取平均
void m_w()
{
	//FILE* fread1 = fopen("weights_1.txt", "r");
	FILE* fp = fopen("weights.txt", "r");
	//FILE* fread3 = fopen("weights.txt", "r");
	int sum[N] = { 0 };
	int a=0, b=0, c=0;
	int i;
	for (i = 0; i < N; i++)
	{
		//fscanf(fread1, "%d", &a);
		fscanf(fp, "%d", &b);
		//fscanf(fread3, "%d", &c);
		sum[i] = a + b + c;
	}
	//fclose(fread1);
	fclose(fp);
	//fclose(fread3);

	/*FILE* fw = fopen("weights.txt", "w");
	for (i = 0; i < N; i++)
	{
		fprintf(fw, "%d ", (int)(sum[i]/3));
	}

	fclose(fw);*/

}





