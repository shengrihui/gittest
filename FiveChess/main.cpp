#include "display.h"
#include "main_game.h"
#include "ai.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
int Chess_Size = _Chess_Size;
int Chess_Point_Size = _Chess_Point_Size;
int CellBoard_Size = _CellBoard_Size;	 //ÿ�����Ӵ�С
int Board_Size _Board_Size;  //z�������̵Ĵ�С

//���ڴ�С
int Board_padding_1= _Board_padding_1;  //�������ϡ��¡���߽�ľ���
int Board_padding_2= _Board_padding_2 ;	//�������ұ߽�ľ���
int wChess_height= _wChess_height  ;  //�������Ŀ��
int wChess_width= _wChess_width  ;

//��ǰ��ҵ���Ϣ��Բ��x,y,r
int Nowplayer_Circle_r= _Nowplayer_Circle_r ;
int Nowplayer_Circle_x= _Nowplayer_Circle_x ;
int Nowplayer_Circle_y= _Nowplayer_Circle_y ;

//��ʱ������x,y,size
int Timer_x= _Timer_x ;
int Timer_y = _Timer_y;
int Timer_Size = _Timer_Size;

//��Ϸ��Ϣ��չʾ
int Msgbox_x=_Msgbox_x ;
int Msgbox_y_1= _Msgbox_y_1 ;
int Msgbox_y_2 = _Msgbox_y_2;
int Msgbox_Size_1 = _Msgbox_Size_1;	//�����1�������ֵĴ�С
int Msgbox_Size_2= _Msgbox_Size_2 ;	//��Ϣ
int Msgbox_padding_1 = _Msgbox_padding_1;
int Msgbox_padding_2 = Msgbox_padding_2;

int Player_Color_x = _Player_Color_x;
int Player_Color_y_1 =_Player_Color_y_1;
int Player_Color_y_2 = _Player_Color_y_2;
int Player_Color_r= _Player_Color_r	;

//origin��ԭʼ��С��int*����ʵ���޸ĺ󣩵ģ�sz�����С��axi���ŵĴ�С
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

//�����Ϣ
struct PLAYER
{
	char name[30];	//����
	int success;	//ʤ������
	int regret;		//�������
	int step;		//�����Ѿ����˵Ĳ���
	int overtime;	//��ʱ����
} players[2] = { "���1", 0,0,0,0, "���2",0,0,0,0 };

MOUSEMSG  M;


//��ӭ����
void Welcome()                                   // ��Ϸ��ʼ����
{
	initgraph(800, 700);                       // ���ô��ڴ�С
	HWND hWnda = GetHWnd();                     // ʹ�� API �����޸Ĵ�������
	SetWindowText(hWnda, "������С��Ϸ");


	IMAGE imga;                                // ���忪ʼ���汳��ͼƬ������imgaͼ��
	loadimage(&imga, "wuziqia.jpg", 800, 700);  //  ���ļ��ж�ȡͼ��
	putimage(0, 0, &imga);                       // ����ͼ���λ��
	setbkmode(TRANSPARENT);                    // ���ñ���͸��,��ֹ����������ݱ�����

	settextcolor(RGB(240, 102, 0));              // ����������ɫ������RGB�����Զ�����ɫ����
	settextstyle(130, 0, "����");		       // ���������С����ȡ�����
	outtextxy(205, 100, "������");             // �ı�λ�ü�������

	settextcolor(BLACK);                       // �����ı���ɫ�����塢��С������
	settextstyle(75, 0, "����");
	outtextxy(255, 280, "�˻���ս");
	outtextxy(255, 390, "��Ҷ�ս");
	outtextxy(255, 495, "����С��");



	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();               // ��ȡһ�������Ϣ
		if (m.uMsg == WM_LBUTTONDOWN)    // Windows��Ϣ������Ƿ񱻲�׽
		{
			if (m.x <= 550 && m.x >= 255 && m.y < 600 && m.y > 495)         // �ж����λ�ã��������С�����
				Team();
			if (m.x <= 550 && m.x >= 255 && m.y < 500 && m.y > 390)         // �ж����λ�ã�������Ҷ�ս����
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

//����С��
void Team()                                     // ����С��                       
{
	initgraph(800, 700);
	HWND hWndc = GetHWnd();                     // ʹ�� API �����޸Ĵ�������
	SetWindowText(hWndc, "����С��");

	IMAGE imgb;                                 // ����imgbͼ��                      
	loadimage(&imgb, "./wuziqi.jpg", 800, 700);
	putimage(0, 0, &imgb);
	setbkmode(TRANSPARENT);                     // ���ñ���͸��

	settextcolor(WHITE);				        // ������ɫ
	setbkmode(TRANSPARENT);				        // ����͸��
	settextstyle(130, 0, "����");		        // �����С����ȡ�����
	settextcolor(BLACK);
	outtextxy(120, 50, "С���Ա");             // С���Ա�ı�����
	settextstyle(70, 0, "��������");
	settextcolor(BLUE);
	outtextxy(180, 260, "Ҧ˧��");
	outtextxy(180, 370, "ʢ�ջ�");
	outtextxy(180, 480, "ף�ƿ�");
	outtextxy(400, 260, "�¿���");
	outtextxy(400, 370, "����ң");
	outtextxy(400, 480, "��  ��");
	settextcolor(BROWN);
	outtextxy(590, 600, "��  ��");


	MOUSEMSG m;                          // ���������Ϣ
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)    // �� ����С�� ���� ��Ϸ�������ж�
		{
			if (m.x <= 720 && m.x >= 590 && m.y < 665 && m.y > 600)
			{
				Welcome();

			}
			else
				FlushMouseMsgBuffer();   // ��������Ϣ������

		}
	}

}

//�������̽���
void Chessboard_windows()
{
	initgraph(wChess_width, wChess_height);
	setbkcolor(RGB(222,145,2));	//����ɫ
	cleardevice();//��������Ϊ��ɫ
	setcolor(BLACK);//��ͼ��ɫ
	setfillcolor(BLACK);	//�����ɫ
}

//������
void Chessboard()
{
	//�������̸���
	int x1, x2, y1, y2, i, j;
	for (i = 0; i < _Line_Num; i++)
	{
		//���� c
		x1 = x2 = Board_padding_1 + i * CellBoard_Size;
		y1 = Board_padding_1;
		y2 = y1 + Board_Size;
		ChessBoard_Line(i, x1, y1, x2, y2);

		//���� r
		y1 = y2 = Board_padding_1 + i * CellBoard_Size;
		x1 = Board_padding_1;
		x2 = x1 + Board_Size;
		ChessBoard_Line(i, x1, y1, x2, y2);

		//�����̵��еļ�����
		ChessBoard_Point(i, x1, y1);
	}

	
	//�����ڵ������Ϣ
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

//��ֱ��
void ChessBoard_Line(int i, int x1, int y1, int x2, int y2)
{
	//ʵ�ֱ߿�Ӵ�
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

//�����̵��е�5�������
void ChessBoard_Point(int i, int x, int y)
{
	//���
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

//��Ϸʱ���һЩ�����Ϣ
void Game_msgbox()
{
	char s[50] = {};
	int i;
	int y1 = Msgbox_y_1;	//���ֵ�y
	int y2=y1+Msgbox_padding_1;	//��Ϣ�ĵ�һ��y
	int dy = 0;	//ÿ����Ϣ֮���y��
	for (i = 0; i <= 1; i++) {	//�������
		if (i == 1) {	//y1,y2,�л�����Ҷ���ֵ
			y1 = Msgbox_y_2;
			y2 = y1 + Msgbox_padding_1;
		}
		settextstyle(Msgbox_Size_1, 0, "��������");
		outtextxy(Msgbox_x, y1, players[i].name);	//����

		dy = 0;
		settextstyle(Msgbox_Size_2, 0, "΢��ֺ�");
		sprintf(s, "������%d", players[i].step);
		outtextxy(Msgbox_x, y2, _T(s));

		dy +=Msgbox_Size_2+ Msgbox_padding_2;
		sprintf(s, "���壺%d", players[i].regret);
		outtextxy(Msgbox_x, y2 + dy, _T(s)); 

		dy += Msgbox_Size_2 + Msgbox_padding_2;
		sprintf(s, "��ʱ������%d", players[i].overtime);
		outtextxy(Msgbox_x, y2 + dy, _T(s));

		dy += Msgbox_Size_2 + Msgbox_padding_2;
		sprintf(s, "ʤ��������%d", players[i].success);
		outtextxy(Msgbox_x, y2 + dy, _T(s));
	}
}

void PLayer_color(int b_p)
{
	int x=Player_Color_x, y1 = Player_Color_y_1, y2 = Player_Color_y_2, t;
	if (b_p == 1) { t = y1; y1 = y2; y2 = t; }
	//����Ҷ�Ӧy1��
	setfillcolor(BLACK);
	solidcircle(x, y1, Player_Color_r);
	setfillcolor(WHITE);
	solidcircle(x, y2, Player_Color_r);
}

//��ʱ������ʾ
void Timer(int i)
{
	char t[3] = { 48 + i / 10,48 + i % 10,'\0' };
	if (i <= 5 && i % 2 == 1)settextcolor(RED);
	settextstyle(Timer_Size, 0, "����");
	outtextxy(Timer_x, Timer_y, t);
	settextcolor(BLACK);
}

void Refresh( )
{
	//cleardevice();
	Chessboard_windows();
	Chessboard();  //������
	//Game_msgbox();
}
//���²���
void  Refresh_config(float f)
{
	int i;
	if (axi <= 1.5 && axi >= 0.5)
	{
		for (i = 0; i < config_sz; i++)
			*(config[i]) = (int)((config_origin[i]) * f);
	}
}

//��¼--�������
void Login()
{
	// �����ַ������������������û�����
	char s[30];
	InputBox(s, 30, "���������1��������Ĭ�����1����");
	if (strcmp(s, "") != 0)
		strcpy(players[0].name, s);
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	InputBox(s, 30, "���������2��������Ĭ�����1����");
	if (strcmp(s, "") != 0)
		strcpy(players[1].name, s);
}

//��Ϸ������
void Game()
{
	Chessboard_windows();
	Chessboard();
	Login();
	//Game_msgbox();
	InitBoard(Board);	//��ʼ������ϲϲ
	int x = 0, y = 0, idx_x = 0, idx_y = 0;  //x,y�������꣬inx_x,y�����±�
	int step = 1;	//��¼��������˭�µļ�������
	int black_player = 0;//һ�ֵ������£�ִ�ڣ���Һ�
	int white_player = 1 - black_player;
	int player = 0;	//�����Ǻڻ��ǰ����£���Ҫ���ڴ���
	while (step)
	{
		PLayer_color(black_player);
		if (step % 2 == 1)	//ÿ�ֶ��Ǻڷ�����
		{
			player = black_player;
			setfillcolor(BLACK);
			solidcircle(Nowplayer_Circle_x, Nowplayer_Circle_y, Nowplayer_Circle_r);	//��ʾ��������һ������
		}
		else
		{
			player = white_player;
			setfillcolor(WHITE);
			solidcircle(Nowplayer_Circle_x, Nowplayer_Circle_y, Nowplayer_Circle_r);
		}
		Move(player, &x, &y, &idx_x, &idx_y);  //���1
		step++;
		players[player].step++;	//��Ҳ���+1
		if (Iswin(idx_x, idx_y) == 1)
		{
			Sleep(1000);
			InitBoard(Board);
			FlushMouseMsgBuffer();
			cleardevice();
			players[player].success++;
			step = 1;
			players[0].step = players[1].step = 0;	//����ҵĲ�������
			player = black_player; black_player = white_player; white_player = player; 	//������ɫ
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
				//�Ŵ�
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
				//��С
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
				if (Coor2Index_(M.x) >= 0 && Coor2Index_(M.y) >= 0)	//�����һ���ķ�Χ�ڣ������ں�����ʵ��
				{
					*x = M.x; *y = M.y;
					*idx_x = Coor2Index_(*x);
					*idx_y = Coor2Index_(*y);
					//�Ѿ����ӵ����
					if (Board[*idx_x][*idx_y] != 0)
						continue;
					Board[*idx_x][*idx_y] = player + 1;
					solidcircle(Coor2Coor(*x), Coor2Coor(*y), Chess_Size);	//���������λ�ö�Ӧ�����껨԰
					FlushMouseMsgBuffer();
					break;
				}
			}
		}
		else //��ʱ�����������һ��
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

//���ж�ƽ�ֵ�ʱ���ã���0����
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

//�ж��Ƿ�Ӯ�ˣ�ƽ�ַ���-1��Ӯ�˷���1��û�з���0
int Iswin(int x, int y)
{
	int c[4] = { 1,1,1,1 };
	//
	int m[4] = { 3,3,3,3 };
	int i, j, dx, dy, x2, y2;
	//ƽ�ַ���-1
	int zero = Zero();
	
	if (zero == 0)return -1;

	//j ����ģʽ������
	for (j = 0; j < 4; j++)
	{
		//i ��x,y��ʼ�������Ĳ�
		for (i = 1; i <= 4; i++)
		{
			//���ݺ���Ʋ��ѡ��dx��dy
			switch (j)
			{
			case 0:dx = i; dy = i; break;	//��
			case 1:dx = i; dy = 0; break;	//��   x�Ǻ��ŵ�
			case 2:dx = i; dy = -i; break;	//Ʋ
			case 3:dx = 0; dy = i; break;	//��
			}


			switch (m[j])
			{
			case 3:	//��������
				x2 = x + dx; y2 = y + dy;
				if (x2 < 0 || x2 >= _Line_Num || y2 < 0 || y2 >= _Line_Num || Board[x2][y2] != Board[x][y])
				{
					m[j] = 2;
				}
				else
				{
					c[j]++;
				}
			case 2:	//��3��һ������
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

//ͼ����ת��Ϊ����С�� 
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

//�����±�תΪ����
int Index2Coor(int x)
{
	return x * CellBoard_Size + Board_padding_1;
}

//������������Ϣת��Ϊ�����ϵ�����
int Coor2Coor(int x)
{
	return Index2Coor(Coor2Index_(x));
}

//��ʼ�����̵ļ�¼��Ϣ
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
					if (Coor2Index_(M.x) >= 0 && Coor2Index_(M.y) >= 0)	//�����һ���ķ�Χ�ڣ������ں�����ʵ��
					{
						x = M.x; y = M.y;
						idx_x = Coor2Index_(x)+5;
						idx_y = Coor2Index_(y)+5;
						//�Ѿ����ӵ����
						if (board[idx_x ][idx_y] != 0)
							continue;
						board[idx_x ][idx_y ] = 1;
						solidcircle(Coor2Coor(x), Coor2Coor(y), Chess_Size);	//���������λ�ö�Ӧ�����껨԰
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
	
	
	_getch();  //�ȴ������
	closegraph();
	return 0;
}

