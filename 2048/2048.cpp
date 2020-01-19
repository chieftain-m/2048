#include"pch.h"
#include"2048.h"
#include<iostream>
#include"easyx.h"
#include<conio.h>
using namespace std;
int MaxScore = 0;
int score = 0;					//总成绩
void init(int map[][MAP_COL], int* score) {
	int x, y;	//随机位置参数
	*score = 0;	//对成绩进行初始化
	memset(map, 0, sizeof(int)*MAP_ROW*MAP_COL);	//初始化地图
	//对地图进行初始化
	for (int i = 0; i < 2;)
	{
		x = rand() % 4;
		y = rand() % 4;
		if (map[x][y] == 0)
		{
			if (rand() % 7 == 0)
				map[x][y] = 4;
			else
				map[x][y] = 2;
			i++;
		}
	}
}
void DrawMap(int map[][MAP_COL], int score)
{
	wchar_t arr[20];				//临时参数
	setbkcolor(RGB(0, 0, 0));	//背景颜色
	setlinecolor(RGB(255, 0, 0));	//线条颜色
	setlinestyle(PS_SOLID, 3);		//线条风格
	settextcolor(RGB(255, 0, 183));	//字体颜色
	settextstyle(30, 0, L"宋体");	//字体风格 和 字体大小
	cleardevice();					//清屏
	BeginBatchDraw();				//开始绘制地图
	for (int i = 0; i <= 4; ++i)
	{
		line(PIXEL * i, 0 + 50, PIXEL * i, PIXEL * 4 + 50);//竖线
		line(0, PIXEL * i + 50, PIXEL * 4, PIXEL * i + 50);//横线
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			wsprintf(arr, L"%d", map[i][j]);					//将数字写入字符串
			outtextxy(j * PIXEL + 32, i * PIXEL + 50 + 30, arr);//指定位置输出字符串
		}
	}
	//分数
	settextcolor(RGB(0, 255, 0));	//字体颜色 红色
	wsprintf(arr, L"score: %d", score);
	outtextxy(0, 15, arr);			//指定位置输出字符串
	//最高分
	outtextxy(MAP_ROW * PIXEL + 10, 5, L"最高分:");			//指定位置输出字符串
	wsprintf(arr, L"%d", MaxScore);
	outtextxy(MAP_ROW * PIXEL + 120, 5, arr);				//指定位置输出字符串
	outtextxy(MAP_ROW * PIXEL + 10, 80, L"↑↓←→");			//指定位置输出字符串
	outtextxy(MAP_ROW * PIXEL + 10, 120, L"W S A D");			//指定位置输出字符串
	outtextxy(MAP_ROW * PIXEL + 10, 160, L"控制游戏");		//指定位置输出字符串
	EndBatchDraw();		//结束绘制地图
}
void Play(int map[][MAP_COL], int* score)
{
	int len;
	switch (getch())
	{
		case 72://上
		case'W':
		case'w':
		for (int j = 0; j < 4; j++) {
			len = 4;
			for (int i = 0; i < len - 1; i++) {//第一步将为0的块移到下面
				if (map[i][j] == 0) {
					for (int k = i; k < 3; k++) {
						map[k][j] = map[k + 1][j];
						map[k + 1][j] = 0;
					}
					len--;
					i--;
				}
			}
			for (int i = 0; i < len - 1; i++) {//第二步合并相同的块
				if (map[i][j] == 0) return;
				if (map[i][j] == map[i + 1][j]) {
					map[i][j] *= 2;
					//合并之后后面的数字往前移一位
					for (int k = i + 1; k < 3; k++) {
						map[k][j] = map[k + 1][j];
						map[k + 1][j] = 0;
					}
					*score += map[i][j];
				}
			}
		}
		break;
		case 80://下
		case'S':
		case's':
		for (int j = 0; j < 4; j++) {
			len = 0;
			for (int i = 3; i > len; i--){//第一步将为0的块移到上面
				if (map[i][j] == 0) {
					for (int k = i; k > 0; k--) {
						map[k][j] = map[k - 1][j];
						map[k - 1][j] = 0;
					}
					len++;
					i++;
				}
			}
			for (int i = 3; i > len; i--) {//第二步合并相同的块
				if (map[i][j] == 0) return;
				if (map[i][j] == map[i - 1][j]) {
					map[i][j] *= 2;
					for (int k = i - 1; k > 0; k--) {
						map[k][j] = map[k - 1][j];
						map[k - 1][j] = 0;
					}
					*score += map[i][j];
				}
			}
		}
		break;
		case 75://左
		case'A':
		case'a':
			for (int i = 0; i < 4; i++) {
				len = 4;
				for (int j = 0; j < len - 1; j++) {//第一步将为0的块移到右面
					if (map[i][j] == 0) {
						for (int k = j; k < 3; k++) {
							map[i][k] = map[i][k + 1];
							map[i][k + 1] = 0;
						}
						len--;//出现一个0 len减1
						j--;//将右边一个的值赋给了当前块，需要重新判断新的块是否是0
					}
				}
				for (int j = 0; j < 3; j++) {//第二步合并相同的块
					if (map[i][j] == 0) return;
					if (map[i][j] == map[i][j + 1]) {
						map[i][j] *= 2;
						for (int k = j + 1; k < 3; k++) {
							map[i][k] = map[i][k + 1];
							map[i][k + 1] = 0;
						}
						*score += map[i][j];
					}
				}
			}
			break;
			case 77://左
			case'D':
			case'd':
			for (int i = 0; i < 4; i++) {
				len = 0;
				for (int j = 3; j > len; j--) {//第一步将为0的块移到右面
					if (map[i][j] == 0) {
						for (int k = j; k > 0; k--) {
							map[i][k] = map[i][k - 1];
							map[i][k - 1] = 0;
						}
						len++;//出现一个0 len加1
						j++;//将左边一个的值赋给了当前块，需要重新判断新的块是否是0
					}
				}
				for (int j = 3; j > 0; j--) {//第二步合并相同的块
					if (map[i][j] == map[i][j - 1]) {
						map[i][j] *= 2;
						for (int k = j - 1; k > 0; k--) {
							map[i][k] = map[i][k - 1];
							map[i][k - 1] = 0;
						}
						*score += map[i][j];
					}
				}
			}
			break;
			default:
			break;
	}
}
int Judge(int map[][MAP_COL])
{
	int num = 0;	//记录0的个数
	int flag = 0;	//如果可以合并,flag为1
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] >= 2048) return 0;//赢
			if (map[i][j] == 0) num++;		//记录0的个数
			if (j + 1 < 4 && map[i][j] == map[i][j + 1]) flag = 1;//右边是不是一样
			if (i + 1 < 4 && map[i][j] == map[i + 1][j]) flag = 1;//下方是不是一样
		}
	}
	if (num == 0 && flag == 0)  return -1;	//满了并且不能合并  输
	if (num == 0) return 1;					//满了 但是可以合并
	return 2;
	return 0;
}
void Add(int map[][MAP_COL])
{
	int x, y;
	do
	{
		x = rand() % 4;
		y = rand() % 4;
	} while (map[x][y] != 0);	//找到数字为零的位置
	if (rand() % 7 == 0)		
		map[x][y] = 4;
	else
		map[x][y] = 2;
}
void WriteData(int map[][MAP_COL], int score)
{
	FILE*fp = fopen("D:\\2048.txt", "wt");
	if (fp == NULL) return;
	fwrite(map, sizeof(int)*MAP_ROW*MAP_COL, 1, fp);
	fwrite(&score, sizeof(int), 1, fp);
	fwrite(&MaxScore, sizeof(int), 1, fp);
	fclose(fp);
}
void ReadData(int map[][MAP_COL], int score)
{
	FILE*fp = fopen("D:\\2048.txt", "rt");
	if (fp == NULL) return;
	fread(map, sizeof(int)*MAP_ROW*MAP_COL, 1, fp);
	fread(&score, sizeof(int), 1, fp);
	fread(&MaxScore, sizeof(int), 1, fp);
	fclose(fp);
}

int main() {
	int map[MAP_ROW][MAP_COL];	//地图大小
	initgraph(MAP_ROW * PIXEL + 200, MAP_COL * PIXEL + 100);	//加载窗口
	init(map, &score);			//初始化地图数据
	while (1)
	{
		DrawMap(map, score);	//绘制地图
		Play(map, &score);
		int res=Judge(map);
		switch (res) {
		case -1:
			MessageBox(GetHWnd(), L"你输了", L"很遗憾", MB_OK);
			if (score > MaxScore)
				MaxScore = score;
			init(map, &score);		//输了，先初始化数据
			if (MessageBox(GetHWnd(), L"是否重新开始", L"提示", MB_YESNO | MB_DEFBUTTON1) == IDNO)
			{
				WriteData(map, score);	//保存游戏
				return 0;
			}
			break;
		case 0:
			MessageBox(GetHWnd(), L"你赢了", L"恭喜", MB_OK);
			if (score > MaxScore)
				MaxScore = score;
			WriteData(map, score);
			return 0;
			break;
		case 1://没有空位置
			break;
		case 2://还有空位置
			Add(map);
			break;
		default:
			break;
		}
	}
	getchar();
	closegraph();
	return 0;
}