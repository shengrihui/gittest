#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>


#include <graphics.h>
#include <conio.h>

#define _Line_Num 15
#define _Cell_Num (_Line_Num-1)  //���ӵ�����
#define _LImited_Time 10

//�塢���̴�С
#define _Chess_Size 20
#define _Chess_Point_Size _Chess_Size/5
#define _CellBoard_Size 50  //ÿ�����Ӵ�С
#define _Board_Size (_CellBoard_Size*_Cell_Num)  //z�������̵Ĵ�С

//���ڴ�С
#define _Board_padding_1 50  //�������ϡ��¡���߽�ľ���
#define _Board_padding_2 400	//�������ұ߽�ľ���
#define _wChess_height  _Board_Size+2*_Board_padding_1  //�������Ŀ��
#define _wChess_width   _Board_Size+_Board_padding_2

//��ǰ��ҵ���Ϣ��Բ��x,y,r
#define _Nowplayer_Circle_r ( _Chess_Size*2)
#define _Nowplayer_Circle_x (_Board_padding_1+_Board_Size+_Nowplayer_Circle_r+50)
#define _Nowplayer_Circle_y (_Board_padding_1+_Board_Size/2-60)

//��ʱ������x,y,size
#define _Timer_x (_Nowplayer_Circle_x +_Nowplayer_Circle_r+30)
#define _Timer_y  (_Nowplayer_Circle_y-_Nowplayer_Circle_r*0.8)
#define _Timer_Size 80

//��Ϸ��Ϣ��չʾ
#define _Msgbox_x _Board_padding_1+_Board_Size+50
#define _Msgbox_y_1 _Board_padding_1
#define _Msgbox_y_2 _Nowplayer_Circle_y+_Nowplayer_Circle_r+70
#define _Msgbox_Size_1 50	//�����1�������ֵĴ�С
#define _Msgbox_Size_2 30	//��Ϣ
#define _Msgbox_padding_1 _Msgbox_Size_1+10	//���ֺ���Ϣ֮��ļ��
#define _Msgbox_padding_2 5	//����Ϣ֮��ļ��

#define _Player_Color_x _Msgbox_x+180
#define _Player_Color_y_1 _Msgbox_y_1+_Msgbox_Size_1+20
#define _Player_Color_y_2 _Player_Color_y_1+(_Msgbox_y_2-_Msgbox_y_1)
#define _Player_Color_r	_Chess_Size*1.5


void BGM();
void Team();
void Welcome();
void Chessboard_windows();
void Chessboard();
void ChessBoard_Line(int i,  int x1, int y1, int x2, int y2);
void ChessBoard_Point(int i, int x, int y);
void Game_msgbox();
void Timer(int i);
void Refresh();
void Refresh_config(float f);

