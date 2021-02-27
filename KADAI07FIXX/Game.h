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
*�䌴�搶��coniex.h��coniex.cpp����Q�l���܂���*/

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
		BLACK,			/* #000000	��				*/
		BLUE,			/* #0000AA	��				*/
		GREEN,			/* #00AA00	��				*/
		CYAN,			/* #00AAAA	�V�A��			*/
		RED,			/* #AA0000	��				*/
		MAGENTA,		/* #AA00AA	�}�[���^			*/
		BROWN,			/* #AA5500	��				*/
		LIGHTGRAY,		/* #AAAAAA	���邢�D�F		*/
		DARKGRAY,		/* #555555	�Â��D�F			*/
		LIGHTBLUE,		/* #5555FF	���邢��			*/
		LIGHTGREEN,		/* #55FF55	���邢��			*/
		LIGHTCYAN,		/* #55FFFF	���邢�V�A��		*/
		LIGHTRED,		/* #FF5555	���邢��			*/
		LIGHTMAGENTA,	/* #FF55FF	���邢�}�[���^	*/
		YELLOW,			/* #FFFF55	��				*/
		WHITE			/* #FFFFFF	��				*/
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
	const char *tag;					//�ꏊ��
	const char *description;			//�ꏊ�L���v�V����
	int num_items;
}area;

area locations[4] = 
{
	{"Main Island", "�u���[�A�C�����h", 0},
	{"Dark Cave", "�Â��ĕ|�����A�A�����m��Ȃ��Ƃ��̋C�������E�E���������Ȃ���", 1},
	{"Side Beach", "�C�݁A�����Ȃ��݂������ǒT���ΈӊO�Ɩ��ɗ���������Ȃ�", 2},
	{"Tree House", "�������ꂽ����̉ƁA���ɂ͉�������݂���", 1}
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

/* �ϐ��錾 */
char name[100];						//�L�����N�^�[��
static char input[100];				//�L�[�{�[�h�̓���
static int playerLocation = 0;		//���݂̏ꏊ�ԍ�
char* screen_buffer_full;
const int numItems = 5;				//�A�C�e����

/* �C���x���g���[���\���ϐ��錾 */
const char items[5][100] =
{
	"Wood",
	"Golden Key",
	"Shell",
	"Torch",
	"Spear"
};
/* �C���x���g���[�̃A�C�e���� */
static int inventory[numItems] = { 0,0,0,0,0 };

/* �Q�[���p�[�c */
void gameMsg_Menu();
void gameMsg_Start();
void gameMsg_End();
void intro();

/* �E�B���h�E�@*/
void SetCaption(const char* title);				//�R���\�[���E�B�h�E�^�C�g��
void SetScreenMode();							//�R���\�[���E�B�h��ʐݒ�
void GotoXY(int x, int y);

/* �`�� */
void ConsoleTextColor(int color);				//�e�L�X�g�F�ݒ�
void SetHighVideoColor();						//�����F���P�x��
inline void SetFontSize(int width, int height);	//�t�H���g�T�C�Y�ݒ�
void PrintString(const char* buf);				//��������v�����g
void ClearScreen();								//��ʃN���A

/* �C���^���N�V���� */
int KeyPress(int keyboard);						//Stdin����
static bool getInput();							//COMMAND����
static bool execute(char *input);				//COMMAND���s����
bool executeGo(const char* object);				
void executeLook(const char* object);
void executeSearch();
void executeTake(const char* object);
void executeLocation(const char* object);
void executeStats(const char* object);
void executeCraft(const char* object);

/* UI */
void PrintStats();								//�L�������
void printCommand();							//COMMAND���X�g
void printInventory(int inventory[numItems]);	//�C���x���g���[���

#ifdef __cplusplus
}
#endif

#endif /* GAME_H */