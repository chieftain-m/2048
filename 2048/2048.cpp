#include"pch.h"
#include"2048.h"
#include<iostream>
#include"easyx.h"
#include<conio.h>
using namespace std;

void Init(int map[][MAP_COL], int score) {
	int x, y;
	score = 0;
	memset(map, 0, sizeof(map[MAP_ROW][MAP_COL]));
	for (int i = 0; i < 2;) {
		x = rand() % 4; 
		y = rand() % 4;
		if (map[x][y] == 0) {
			if (rand() % 7 == 0) {
				map[x][y] = 4;
			}
			else {
				map[x][y] = 2;
			}
			i++;
		}
	}
}
void ReadData(int map[][MAP_COL], int score)
{
	FILE*fp = fopen("D:\\2048.txt", "rt");
	if (fp == NULL) return;
	fread(map, sizeof(int)*MAP_ROW*MAP_COL, 1, fp);
	fread((void*)score, sizeof(int), 1, fp);
	fread((void*)MaxScore, sizeof(int), 1, fp);
	fclose(fp);
}
int main() {
	int map[MAP_ROW][MAP_COL];
	int score = 0;
	initgraph(MAP_ROW * PIXEL + 100, MAP_COL * PIXEL + 100);
	Init(map, score);			//初始化地图数据
	ReadData(map, score);		//读取数据
}