#pragma once
const int MAP_ROW = 4;
const int MAP_COL = 4;
const int PIXEL = 100;
void init(int map[][MAP_COL], int* score);		//≥ı ºªØ”Œœ∑
void DrawMap(int map[][MAP_COL], int score);
void Play(int map[][MAP_COL], int* score);
int Judge(int map[][MAP_COL]);
void Add(int map[][MAP_COL]);
void WriteData(int map[][MAP_COL], int score);
void ReadData(int map[][MAP_COL], int* score);