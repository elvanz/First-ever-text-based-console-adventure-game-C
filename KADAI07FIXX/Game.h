#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef GAME_H
#define GAME_H

/* extern "C" makes a function-name in C++ have C linkage 
(compiler does not mangle the name) so that client C code 
can link to (use) your function using a C compatible header 
file that contains just the declaration of your function. */

/**
*
*
*
*井原先生のconiex.hとconiex.cppから参考取りました*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <process.h>
#include <Windows.h>
#include <mmsystem.h>		//PlaySound header file

#pragma comment (lib , "winmm.lib")

	enum COLORS {
		BLACK,			/* #000000	黒				*/
		BLUE,			/* #0000AA	青				*/
		GREEN,			/* #00AA00	緑				*/
		CYAN,			/* #00AAAA	シアン			*/
		RED,			/* #AA0000	赤				*/
		MAGENTA,		/* #AA00AA	マゼンタ			*/
		BROWN,			/* #AA5500	茶				*/
		LIGHTGRAY,		/* #AAAAAA	明るい灰色		*/
		DARKGRAY,		/* #555555	暗い灰色			*/
		LIGHTBLUE,		/* #5555FF	明るい青			*/
		LIGHTGREEN,		/* #55FF55	明るい緑			*/
		LIGHTCYAN,		/* #55FFFF	明るいシアン		*/
		LIGHTRED,		/* #FF5555	明るい赤			*/
		LIGHTMAGENTA,	/* #FF55FF	明るいマゼンタ	*/
		YELLOW,			/* #FFFF55	黄				*/
		WHITE			/* #FFFFFF	白				*/
	};


/* Struct */
typedef struct CHARACTER
{
	int HP;
	int maxHP;
	int attack;
}chara;

typedef struct AREA
{
	const char *tag;					//場所名
	const char *description;			//場所キャプション
	int num_items;
}area;

area locations[4] = 
{
	{"Main Island", "ブルーアイランド", 0},
	{"Dark Cave", "暗くて怖い洞窟、何か知らないときの気持ちが・・いつも悪くなった", 1},
	{"Side Beach", "海岸、何もないみたいけど探せば意外と役に立つかもしれない", 2},
	{"Tree House", "放棄された樹上の家、中には何かあるみたい", 1}
};

typedef struct OBJECTS
{
	const char		*description;
	const char		*tag;
	int				*itemQuantity;
	struct AREA		*locations;
}objects;

objects objs[] = 
{
	{"Wood", "wood", 0, &locations[2]},
	{"Golden Key", "key", 0, &locations[1]},
	{"Shell", "shell", 0, &locations[2]},
	{"Torch", "torch", 0, &locations[3]},
};

/* ENUMS */
enum directions
{
	NORTH,							//0
	EAST,							//1
	SOUTH,							//2
	WEST							//3
};

/* 変数宣言 */
char name[100];						//キャラクター名
static char input[100];				//キーボードの入力
static int playerLocation = 0;		//現在の場所番号
char* screen_buffer_full;
const int numItems = 5;				//アイテム数

/* インベントリー情報表示変数宣言 */
const char items[5][100] =
{
	"Wood",
	"Golden Key",
	"Shell",
	"Torch",
	"Spear"
};
/* インベントリーのアイテム数 */
static int inventory[numItems] = { 0,0,0,0,0 };

/* ゲームパーツ */
void gameMsg_Menu();
void gameMsg_Start();
void gameMsg_End();
void intro();

/* ウィンドウ　*/
void SetCaption(const char* title);				//コンソールウィドウタイトル
void SetScreenMode();							//コンソールウィド画面設定
void GotoXY(int x, int y);

/* 描面 */
void ConsoleTextColor(int color);				//テキスト色設定
void SetHighVideoColor();						//文字色高輝度化
inline void SetFontSize(int width, int height);	//フォントサイズ設定
void PrintString(const char* buf);				//文字列をプリント
void ClearScreen();								//画面クリア

/* インタラクション */
int KeyPress(int keyboard);						//Stdin処理
static bool getInput();							//COMMAND入力
static bool execute(char *input);				//COMMAND実行する
bool executeGo(const char* object);				
void executeLook(const char* object);
void executeSearch();
void executeTake(const char* object);
void executeLocation(const char* object);
void executeStats(const char* object);
void executeCraft(const char* object);

/* UI */
void PrintStats();								//キャラ情報
void printCommand();							//COMMANDリスト
void printInventory(int inventory[numItems]);	//インベントリー情報

#ifdef __cplusplus
}
#endif

#endif /* GAME_H */