#pragma once
//�����ַ�
#include  < cstdio >
#include  < cstdlib >
#include  < clocale >
#include  < cwchar >
#include "display.h"
void Game();	//��Ϸ������
void Move(int player, int* x, int* y, int* idx_x, int* idx_y);	//ÿ�ε����ӣ�x,y��Ļ���꣬inx_x,y�����±�
int Iswin(int x, int y);	//�ж��Ƿ�Ӯ
void Login();	//�����������

//function.cpp
void _strcpy(wchar_t* s1, wchar_t* s2);
int Coor2Index_(int x);	//���ӵ���Ļ����תΪ�������ĵ�������±꣬x�Ǻ�
int Index2Coor(int x);	//�����±�תΪ��Ӧ����Ļ����
int Coor2Coor(int x);	//������ӵ���Ļ����תΪ��Ӧ�ĸ����Ļ����
void InitBoard(int board[][_Line_Num]);
void machine();