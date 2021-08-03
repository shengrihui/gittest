#pragma once
//处理字符
#include  < cstdio >
#include  < cstdlib >
#include  < clocale >
#include  < cwchar >
#include "display.h"
void Game();	//游戏主函数
void Move(int player, int* x, int* y, int* idx_x, int* idx_y);	//每次的落子，x,y屏幕坐标，inx_x,y数组下标
int Iswin(int x, int y);	//判断是否赢
void Login();	//输入玩家名字

//function.cpp
void _strcpy(wchar_t* s1, wchar_t* s2);
int Coor2Index_(int x);	//落子的屏幕坐标转为它附近的点的数组下标，x是横
int Index2Coor(int x);	//数组下标转为对应的屏幕坐标
int Coor2Coor(int x);	//鼠标落子的屏幕坐标转为对应的格点屏幕坐标
void InitBoard(int board[][_Line_Num]);
void machine();