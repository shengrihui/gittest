#include "display.h"
#include "main_game.h"
#include "ai.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
int Chess_Size = _Chess_Size;
int Chess_Point_Size = _Chess_Point_Size;
int CellBoard_Size = _CellBoard_Size;	 //每个格子大小
int Board_Size _Board_Size;  //z整个棋盘的大小

//窗口大小
int Board_padding_1= _Board_padding_1;  //棋盘与上、下、左边界的距离
int Board_padding_2= _Board_padding_2 ;	//棋盘与右边界的距离
int wChess_height= _wChess_height  ;  //下棋界面的宽高
int wChess_width= _wChess_width  ;

//当前玩家的信息的圆的x,y,r
int Nowplayer_Circle_r= _Nowplayer_Circle_r ;
int Nowplayer_Circle_x= _Nowplayer_Circle_x ;
int Nowplayer_Circle_y= _Nowplayer_Circle_y ;

//计时器的下x,y,size
int Timer_x= _Timer_x ;
int Timer_y = _Timer_y;
int Timer_Size = _Timer_Size;

//游戏信息的展示
int Msgbox_x=_Msgbox_x ;
int Msgbox_y_1= _Msgbox_y_1 ;
int Msgbox_y_2 = _Msgbox_y_2;
int Msgbox_Size_1 = _Msgbox_Size_1;	//“玩家1”三个字的大小
int Msgbox_Size_2= _Msgbox_Size_2 ;	//信息
int Msgbox_padding_1 = _Msgbox_padding_1;
int Msgbox_padding_2 = Msgbox_padding_2;

int Player_Color_x = _Player_Color_x;
int Player_Color_y_1 =_Player_Color_y_1;
int Player_Color_y_2 = _Player_Color_y_2;
int Player_Color_r= _Player_Color_r	;

//origin是原始大小，int*是真实（修改后）的，sz数组大小，axi缩放的大小
int config_origin[] = { Chess_Size, CellBoard_Size,Chess_Point_Size,
	Board_Size ,Board_padding_1,Board_padding_2,wChess_height,wChess_width ,
	Nowplayer_Circle_x, Nowplayer_Circle_y, Nowplayer_Circle_r,
	Timer_x,Timer_y,Timer_Size ,
	Msgbox_x ,Msgbox_y_1,Msgbox_y_2,Msgbox_Size_1,Msgbox_Size_2 ,Msgbox_padding_1,Msgbox_padding_2,
	Player_Color_x ,Player_Color_y_1,Player_Color_y_2,Player_Color_r};
int* config[] = { &Chess_Size, &CellBoard_Size,&Chess_Point_Size,
	&Board_Size ,&Board_padding_1,&Board_padding_2,&wChess_height,&wChess_width,
	&Nowplayer_Circle_x ,&Nowplayer_Circle_y,&Nowplayer_Circle_r,
	&Timer_x ,&Timer_y,&Timer_Size,
	&Msgbox_x ,&Msgbox_y_1,&Msgbox_y_2,&Msgbox_Size_1,&Msgbox_Size_2,& Msgbox_padding_1,& Msgbox_padding_2 ,
	&Player_Color_x ,&Player_Color_y_1,&Player_Color_y_2,&Player_Color_r };
int config_sz = sizeof(config) / sizeof(config[0]);
float axi = 1.0;

int Board[_Line_Num][_Line_Num] = { 0 };

//玩家信息
struct PLAYER
{
	char name[30];	//名字
	int success;	//胜利局数
	int regret;		//悔棋次数
	int step;		//本剧已经走了的步数
	int overtime;	//超时次数
} players[2] = { "玩家1", 0,0,0,0, "玩家2",0,0,0,0 };

MOUSEMSG  M;


//欢迎界面
void Welcome()                                   // 游戏开始界面
{
	initgraph(800, 700);                       // 设置窗口大小
	HWND hWnda = GetHWnd();                     // 使用 API 函数修改窗口名称
	SetWindowText(hWnda, "五子棋小游戏");


	IMAGE imga;                                // 定义开始界面背景图片（插入imga图像）
	loadimage(&imga, "wuziqia.jpg", 800, 700);  //  从文件中读取图像
	putimage(0, 0, &imga);                       // 放置图像的位置
	setbkmode(TRANSPARENT);                    // 设置背景透明,防止后面设计内容被覆盖

	settextcolor(RGB(240, 102, 0));              // 设置文字颜色，利用RGB进行自定义颜色生成
	settextstyle(130, 0, "黑体");		       // 字设置体大小、宽度、字体
	outtextxy(205, 100, "五子棋");             // 文本位置及其内容

	settextcolor(BLACK);                       // 设置文本颜色、字体、大小、内容
	settextstyle(75, 0, "楷体");
	outtextxy(255, 280, "人机大战");
	outtextxy(255, 390, "玩家对战");
	outtextxy(255, 495, "关于小组");



	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();               // 获取一个鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)    // Windows消息，鼠标是否被捕捉
		{
			if (m.x <= 550 && m.x >= 255 && m.y < 600 && m.y > 495)         // 判断鼠标位置，进入关于小组界面
				Team();
			if (m.x <= 550 && m.x >= 255 && m.y < 500 && m.y > 390)         // 判断鼠标位置，进入玩家对战界面
				Game();
			if (m.x <= 550 && m.x >= 255 && m.y < 400 && m.y > 310)
				machine();

		}
	}
}

void BGM()
{
	mciSendString("open ./pipayu.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	if (0)
	{
		mciSendString("close BGM", 0, 0, 0);
	}

}

//关于小组
void Team()                                     // 关于小组                       
{
	initgraph(800, 700);
	HWND hWndc = GetHWnd();                     // 使用 API 函数修改窗口名称
	SetWindowText(hWndc, "关于小组");

	IMAGE imgb;                                 // 插入imgb图像                      
	loadimage(&imgb, "./wuziqi.jpg", 800, 700);
	putimage(0, 0, &imgb);
	setbkmode(TRANSPARENT);                     // 设置背景透明

	settextcolor(WHITE);				        // 文字颜色
	setbkmode(TRANSPARENT);				        // 窗口透明
	settextstyle(130, 0, "宋体");		        // 字体大小、宽度、字体
	settextcolor(BLACK);
	outtextxy(120, 50, "小组成员");             // 小组成员文本设置
	settextstyle(70, 0, "华文隶书");
	settextcolor(BLUE);
	outtextxy(180, 260, "姚帅翔");
	outtextxy(180, 370, "盛日辉");
	outtextxy(180, 480, "祝云可");
	outtextxy(400, 260, "柯俊凯");
	outtextxy(400, 370, "李智遥");
	outtextxy(400, 480, "马  锐");
	settextcolor(BROWN);
	outtextxy(590, 600, "返  回");


	MOUSEMSG m;                          // 定义鼠标消息
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)    // 从 关于小组 返回 游戏主界面判断
		{
			if (m.x <= 720 && m.x >= 590 && m.y < 665 && m.y > 600)
			{
				Welcome();

			}
			else
				FlushMouseMsgBuffer();   // 清空鼠标消息缓冲区

		}
	}

}

//绘制棋盘界面
void Chessboard_windows()
{
	initgraph(wChess_width, wChess_height);
	setbkcolor(RGB(222,145,2));	//背景色
	cleardevice();//背景设置为白色
	setcolor(BLACK);//画图颜色
	setfillcolor(BLACK);	//填充颜色
}

//画棋盘
void Chessboard()
{
	//绘制棋盘格子
	int x1, x2, y1, y2, i, j;
	for (i = 0; i < _Line_Num; i++)
	{
		//竖线 c
		x1 = x2 = Board_padding_1 + i * CellBoard_Size;
		y1 = Board_padding_1;
		y2 = y1 + Board_Size;
		ChessBoard_Line(i, x1, y1, x2, y2);

		//横线 r
		y1 = y2 = Board_padding_1 + i * CellBoard_Size;
		x1 = Board_padding_1;
		x2 = x1 + Board_Size;
		ChessBoard_Line(i, x1, y1, x2, y2);

		//画棋盘当中的几个点
		ChessBoard_Point(i, x1, y1);
	}

	
	//画现在的棋局信息
	for (i=0;i<_Line_Num;i++)
	{
		for (j = 0; j < _Line_Num; j++)
		{
			switch (Board[i][j])
			{
			case 1:setfillcolor(BLACK); solidcircle(Index2Coor(i), Index2Coor(j), Chess_Size); break;
			case 2:setfillcolor(WHITE); solidcircle(Index2Coor(i), Index2Coor(j), Chess_Size); break;
			}
		}
	}
}

//画直线
void ChessBoard_Line(int i, int x1, int y1, int x2, int y2)
{
	//实现边框加粗
	if (i == 0 || i == _Cell_Num)
	{
		setlinestyle(PS_SOLID, 3);
		line(x1, y1, x2, y2);
	}
	else
	{
		setlinestyle(PS_SOLID, 1);
		line(x1, y1, x2, y2);
	}
}

//画棋盘当中的5个特殊点
void ChessBoard_Point(int i, int x, int y)
{
	//间隔
	int q = (_Cell_Num) / 4;;
	if (i % q == 0)
	{
		switch (i / q)
		{
		case 1:
		case 3:
			solidcircle(x + q * CellBoard_Size, y, Chess_Point_Size);
			solidcircle(x + 3 * q * CellBoard_Size, y, Chess_Point_Size);
			break;
		case 2:
			solidcircle(x + 2 * +q * CellBoard_Size, y, Chess_Point_Size);
			break;
		default:
			break;
		}
	}
}

//游戏时候的一些玩家信息
void Game_msgbox()
{
	char s[50] = {};
	int i;
	int y1 = Msgbox_y_1;	//名字的y
	int y2=y1+Msgbox_padding_1;	//信息的第一个y
	int dy = 0;	//每个信息之间的y差
	for (i = 0; i <= 1; i++) {	//两个玩家
		if (i == 1) {	//y1,y2,切换到玩家二的值
			y1 = Msgbox_y_2;
			y2 = y1 + Msgbox_padding_1;
		}
		settextstyle(Msgbox_Size_1, 0, "华文隶书");
		outtextxy(Msgbox_x, y1, players[i].name);	//名字

		dy = 0;
		settextstyle(Msgbox_Size_2, 0, "微软粗黑");
		sprintf(s, "步数：%d", players[i].step);
		outtextxy(Msgbox_x, y2, _T(s));

		dy +=Msgbox_Size_2+ Msgbox_padding_2;
		sprintf(s, "悔棋：%d", players[i].regret);
		outtextxy(Msgbox_x, y2 + dy, _T(s)); 

		dy += Msgbox_Size_2 + Msgbox_padding_2;
		sprintf(s, "超时次数：%d", players[i].overtime);
		outtextxy(Msgbox_x, y2 + dy, _T(s));

		dy += Msgbox_Size_2 + Msgbox_padding_2;
		sprintf(s, "胜利局数：%d", players[i].success);
		outtextxy(Msgbox_x, y2 + dy, _T(s));
	}
}

void PLayer_color(int b_p)
{
	int x=Player_Color_x, y1 = Player_Color_y_1, y2 = Player_Color_y_2, t;
	if (b_p == 1) { t = y1; y1 = y2; y2 = t; }
	//黑玩家对应y1，
	setfillcolor(BLACK);
	solidcircle(x, y1, Player_Color_r);
	setfillcolor(WHITE);
	solidcircle(x, y2, Player_Color_r);
}

//计时器的显示
void Timer(int i)
{
	char t[3] = { 48 + i / 10,48 + i % 10,'\0' };
	if (i <= 5 && i % 2 == 1)settextcolor(RED);
	settextstyle(Timer_Size, 0, "黑体");
	outtextxy(Timer_x, Timer_y, t);
	settextcolor(BLACK);
}

void Refresh( )
{
	//cleardevice();
	Chessboard_windows();
	Chessboard();  //画棋盘
	//Game_msgbox();
}
//更新参数
void  Refresh_config(float f)
{
	int i;
	if (axi <= 1.5 && axi >= 0.5)
	{
		for (i = 0; i < config_sz; i++)
			*(config[i]) = (int)((config_origin[i]) * f);
	}
}

//登录--玩家名字
void Login()
{
	// 定义字符串缓冲区，并接收用户输入
	char s[30];
	InputBox(s, 30, "请输入玩家1的姓名（默认玩家1）：");
	if (strcmp(s, "") != 0)
		strcpy(players[0].name, s);
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	InputBox(s, 30, "请输入玩家2的姓名（默认玩家1）：");
	if (strcmp(s, "") != 0)
		strcpy(players[1].name, s);
}

//游戏主函数
void Game()
{
	Chessboard_windows();
	Chessboard();
	Login();
	//Game_msgbox();
	InitBoard(Board);	//初始化棋盘喜喜
	int x = 0, y = 0, idx_x = 0, idx_y = 0;  //x,y棋盘坐标，inx_x,y数组下标
	int step = 1;	//记录步数（是谁下的计数器）
	int black_player = 0;//一局当中先下（执黑）玩家号
	int white_player = 1 - black_player;
	int player = 0;	//现在是黑还是白在下，主要用于传参
	while (step)
	{
		PLayer_color(black_player);
		if (step % 2 == 1)	//每局都是黑方先下
		{
			player = black_player;
			setfillcolor(BLACK);
			solidcircle(Nowplayer_Circle_x, Nowplayer_Circle_y, Nowplayer_Circle_r);	//显示现在是哪一方在下
		}
		else
		{
			player = white_player;
			setfillcolor(WHITE);
			solidcircle(Nowplayer_Circle_x, Nowplayer_Circle_y, Nowplayer_Circle_r);
		}
		Move(player, &x, &y, &idx_x, &idx_y);  //玩家1
		step++;
		players[player].step++;	//玩家步数+1
		if (Iswin(idx_x, idx_y) == 1)
		{
			Sleep(1000);
			InitBoard(Board);
			FlushMouseMsgBuffer();
			cleardevice();
			players[player].success++;
			step = 1;
			players[0].step = players[1].step = 0;	//对玩家的步数清零
			player = black_player; black_player = white_player; white_player = player; 	//交换颜色
			if (players[player].success == 2)
			{
				 break;
			}			
		}
	}
}

void Move(int player, int* x, int* y, int* idx_x, int* idx_y)
{
	time_t start = time(NULL), end=time(NULL);
	int t = 0;
	while (1)
	{
		//t = difftime(time(NULL), start);
		t = difftime(time(NULL),start);
		Game_msgbox();
		Timer(_LImited_Time - t);
		if ( t<=_LImited_Time )
		{
			//M = GetMouseMsg();
			
			PeekMouseMsg(&M, true);
			if (M.mkCtrl)
			{
				//放大
				//PeekMouseMsg(&M, true);
				if (M.uMsg == WM_RBUTTONDOWN)
				{
					axi += 0.1;
					//setaspectratio(axi, axi);
					Refresh_config(axi);
					initgraph(wChess_width, wChess_height);
					Refresh();
				}
			}
			else if (M.mkShift)
			{
				//缩小
				//PeekMouseMsg(&M, true);
				if (M.uMsg == WM_RBUTTONDOWN)
				{
					
					axi -= 0.1;
					//setaspectratio(axi, axi);
					Refresh_config(axi);
					FlushMouseMsgBuffer();
					initgraph(wChess_width, wChess_height);
					Refresh();
				}
			}
			else if (M.uMsg == WM_LBUTTONDOWN)
			{
				if (Coor2Index_(M.x) >= 0 && Coor2Index_(M.y) >= 0)	//如果在一定的范围内，具体在函数里实现
				{
					*x = M.x; *y = M.y;
					*idx_x = Coor2Index_(*x);
					*idx_y = Coor2Index_(*y);
					//已经有子的情况
					if (Board[*idx_x][*idx_y] != 0)
						continue;
					Board[*idx_x][*idx_y] = player + 1;
					solidcircle(Coor2Coor(*x), Coor2Coor(*y), Chess_Size);	//在鼠标点击的位置对应的坐标花园
					FlushMouseMsgBuffer();
					break;
				}
			}
		}
		else //超时，电脑随机下一个
		{
			int x, y;
			while (1)
			{
				x = rand() % _Line_Num;
				y = rand() % _Line_Num;
				if (Board[x][y] != 0)
				{
					continue;
				}
				*idx_x = x; *idx_y = y;
				Board[x][y] = player + 1;
				solidcircle(Index2Coor(x), Index2Coor(y), Chess_Size);				break;
				break;
			}
			players[player].overtime++;
			FlushMouseMsgBuffer();
			break;
		}
	}
	FlushMouseMsgBuffer();
	Refresh();
}

//在判断平局的时候用，计0个数
int Zero()
{
	int zero=0,i,j;
	for (i = 0; i < _Line_Num; i++)
	{
		for (j = 0; j < _Line_Num; j++)
		{
			if (Board[i][j] == 0)
				zero++;
		}
	}
	return zero;
}

//判断是否赢了，平局返回-1，赢了返回1，没有返回0
int Iswin(int x, int y)
{
	int c[4] = { 1,1,1,1 };
	//
	int m[4] = { 3,3,3,3 };
	int i, j, dx, dy, x2, y2;
	//平局返回-1
	int zero = Zero();
	
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
				if (x2 < 0 || x2 >= _Line_Num || y2 < 0 || y2 >= _Line_Num || Board[x2][y2] != Board[x][y])
				{
					m[j] = 2;
				}
				else
				{
					c[j]++;
				}
			case 2:	//比3少一个方向
				x2 = x - dx; y2 = y - dy;
				if (x2 < 0 || x2 >= _Line_Num || y2 < 0 || y2 >= _Line_Num || Board[x2][y2] != Board[x][y])
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
				if (x2 < 0 || x2 >= _Line_Num || y2 < 0 || y2 >=_Line_Num || Board[x2][y2] != Board[x][y])
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

//图坐标转换为数组小标 
int Coor2Index_(int x)
{
	int idx;
	for (idx = 0; idx <= _Cell_Num; idx++)
	{
		if (abs((idx * CellBoard_Size + Board_padding_1) - x) <= Chess_Size)
			return idx;
	}
	return -1;
}

//数组下标转为坐标
int Index2Coor(int x)
{
	return x * CellBoard_Size + Board_padding_1;
}

//将鼠标的坐标信息转换为棋盘上的坐标
int Coor2Coor(int x)
{
	return Index2Coor(Coor2Index_(x));
}

//初始化棋盘的记录信息
void InitBoard(int board[][_Line_Num])
{
	int x, y;
	for (x = 0; x < _Line_Num; x++)
	{
		for (y = 0; y < _Line_Num; y++)
			Board[x][y] = 0;
	}
}




void machine()
{
	Chessboard_windows();
	Chessboard();
	int board[25][25] = { 0 }, count[25][25] = { 0 };
	init_board(board, count);
	read_file();
	int step = 1;
	int x = 0, y = 0, idx_x = 0, idx_y = 0;
	while (step)
	{
		if (step % 2 == 1)
		{
			setfillcolor(BLACK);
			while (1)
			{
				M = GetMouseMsg();
				if (M.uMsg == WM_LBUTTONDOWN)
				{
					if (Coor2Index_(M.x) >= 0 && Coor2Index_(M.y) >= 0)	//如果在一定的范围内，具体在函数里实现
					{
						x = M.x; y = M.y;
						idx_x = Coor2Index_(x)+5;
						idx_y = Coor2Index_(y)+5;
						//已经有子的情况
						if (board[idx_x ][idx_y] != 0)
							continue;
						board[idx_x ][idx_y ] = 1;
						solidcircle(Coor2Coor(x), Coor2Coor(y), Chess_Size);	//在鼠标点击的位置对应的坐标花园
						FlushMouseMsgBuffer();
						break;
					}
				}
			}
		}
		else
		{
			setfillcolor(WHITE);
			next_step(board, count, 2, 1, &idx_x, &idx_y);
			board[idx_x][idx_y] = 2;
			upgrate_count(count, board, idx_x, idx_y);
			solidcircle(Index2Coor(idx_x-5), Index2Coor(idx_y-5), Chess_Size);
		}
		upgrate_count(count, board, idx_x, idx_y);
		printf("ste0:%d idx_x:%d idx_y:%d\n", step, idx_x, idx_y);
		step++;
		if (1 == Iswin_2(idx_x, idx_y, board, step % 2+1))
		{
			print_w();
			exit(0);
		}
	}

}



int main()
{
	srand((unsigned int)time(NULL));
	BGM();
	Welcome();
	
	
	_getch();  //等待任意键
	closegraph();
	return 0;
}

