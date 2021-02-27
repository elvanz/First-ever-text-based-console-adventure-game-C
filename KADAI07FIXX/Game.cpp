/*
*Text-Based Adventure Game School Project
*Made by Elvan Mulyono
*-------------------------------------------
*AT11A026_10
*CL11 �ۑ�@No.7
*�G���t�@���������m
*/

#include "Game.h"		//�Q�[���w�[�_�[�t�@�C��

/* Console �ݒ� */
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
DWORD dwMode = NULL;
COORD screen_buffer_size;
WORD screen_buffer_attribute = LIGHTGRAY;
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
#define CONSOLE_INPUT_MODE	( ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT )
#define CONSOLE_OUTPUT_MODE	(ENABLE_PROCESSED_OUTPUT | ENABLE_LVB_GRID_WORLDWIDE | ENABLE_VIRTUAL_TERMINAL_PROCESSING )

/* �^�C�g����� */
void intro()
{
	/* ��ʂ̐ݒ� */
	SetCaption("WORK IN PROGRESS");
	GotoXY(44, 1);
	printf("                  {}\n");
	GotoXY(44, 2);
	printf("  ,   A           {}\n");
	GotoXY(44, 3);
	printf(" / \\, | ,        .--.\n");
	GotoXY(44, 4);
	printf("|  =|= >        /.--.\\\n");
	GotoXY(44, 5);
	printf(" \\ /` | `       |====|\n");
	GotoXY(44, 6);
	printf("  `   |         |`::`|\n");
	GotoXY(44, 7);
	printf("      |     .-;`\\..../`;_.-^-._\n");
	GotoXY(44, 8);
	printf("     /\\\\/  /  |...::..|`   :   `|\n");
	GotoXY(44, 9);
	printf("     |:'\\ |   /'''::''|   .:.   |\n");
	GotoXY(44, 10);
	printf("      \\ /\\;-,/\\   ::  |..HELLO..|\n");
	GotoXY(44, 11);
	printf("      |\\ <` >  >._::_.| ':HAL:' |\n");
	GotoXY(44, 12);
	printf("      | `""`_/   ^^/>/>  |   ':'   |\n");
	GotoXY(44, 13);
	printf("      |       |       \\    :   /\n");
	GotoXY(44, 14);
	printf("      |       |        \\   :   /\n");
	GotoXY(44, 15);
	printf("      |       |___/\\___|`-.:.-`\n");
	GotoXY(44, 16);
	printf("      |        \\_ || _/    `\n");
	GotoXY(44, 17);
	printf("      |        <_ >< _>\n");
	GotoXY(44, 18);
	printf("      |        |  ||  |\n");
	GotoXY(44, 19);
	printf("      |        |  ||  |\n");
	GotoXY(44, 20);
	printf("      |       _\\.:||:./_\n");
	GotoXY(44, 21);
	printf("      | ily  /____/\\____\\\n");
	GotoXY(25, 22);
	printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:\n");
	system("pause");
}

/* ���j���[��� */
void gameMsg_Menu()
{
	/* ��ʂ̐ݒ� */
	SetScreenMode();
	SetHighVideoColor();

	/* �e�L�X�g�ݒ� */
	ConsoleTextColor(WHITE);
	SetFontSize(10, 20);
	printf("\t\t\t\t\t\t\t\tTHE BLUE ISLAND\n\n");
	Sleep(1000);
}

/* �J�n��� */
void gameMsg_Start()
{
	/* �e�L�X�g�ݒ� */
	ConsoleTextColor(YELLOW);
	printCommand();
	Sleep(1000);

	/* INTRO */
	ConsoleTextColor(WHITE);
	PrintString("\n\n���̃Q�[���͊J�����ł���I\n\n");
	PrintString("�X�g�[���[�Ƃ����Ȃ̂ł��̃Q�[���͂܂��I����ĂȂ��I\n\n");
	PrintString("�����Ă�������!!!\n\n");
	Sleep(1000);
	printf("-----------------------------------------------------------\n");
	printf("\n���O�����: ");
	scanf("%[^\n]s", &name);
	rewind(stdin);
}

int main()
{
	/* INTRO */
	intro();
	ClearScreen();

	/* �Q�[���J�n��� */
	gameMsg_Menu();
	gameMsg_Start();

	/* �n�܂� */
	printf("\n���Ȃ���%s�ł��B\n\n", name);
	Sleep(100);
	PrintString("���Ȃ��̓u���[�A�C�����h�ɂ���܂��B\n\n");
	PrintString("�u���[�A�C�����h�ւ悤����\n\n");

	executeLook("around");
	Sleep(1000);
	
	/* COMMANDS */
	while (getInput() && execute(input));
	gameMsg_End();
	getchar();
	return EXIT_SUCCESS;
}

/*�@�I����� */
void gameMsg_End()
{
	PrintString("�������[������\n");
	PrintString("Thank you for playing!\n");
}

/**
 * @brief	�L�[�{�[�h�̓��͂�ǂݍ��ޏ���
 *
 * @param	keycode [����] �o��keyboard keycode
 */
int KeyPress(int keyboard)
{
	return (GetAsyncKeyState(keyboard) & 0x8000 != 0);
}

/**
 * @brief	�L�[�{�[�h�̓��͂�ǂݍ��ޏ���
 *
 */
static bool getInput()
{
printf("\n--> ");
return fgets(input, sizeof(input), stdin) != NULL;
}

/**
 * @brief	�S����command�����s���鏈��
 *
 * @param	input [����] �o��getInput()�̃|�C���^
 */
static bool execute(char *input)
{
	char *command = strtok(input, " \n");
	char *object = strtok(NULL, " \n");
	if (command != NULL)
	{
		if (strcmp(command, "quit") == 0)
		{
			return false;
		}
		else if (strcmp(command, "look") == 0)
		{
			executeLook(object);
		}
		else if (strcmp(command, "go") == 0)
		{
			executeGo(object);
			executeLocation(object);
		}
		else if (strcmp(command, "search") == 0)
		{
			executeSearch();
		}
		else if (strcmp(command, "take") == 0)
		{
			executeTake(object);
		}
		else if (strcmp(command, "inventory") == 0)
		{
			printInventory(inventory);
		}
		else if (strcmp(command, "check") == 0)
		{
			executeStats(object);
		}
		else if (strcmp(command, "craft") == 0)
		{
			executeCraft(object);
		}
		else if (strcmp(command, "fuck") == 0)
		{
			PrintString("�n����Y�A�������t�����ȁE�E\n");
		}
		else
		{
			printf("%s�͂킩��܂���B\n", command);
		}
	}
	return true;
}

/**
 * @brief	look��command�����s����
 *
 * @param	object [����] �o��object�̃|�C���^
 */
void executeLook(const char* object)
{
	if (object != NULL && strcmp(object, "around") == 0)
	{
		printf("���݂̏ꏊ�� %s �ł��B�B\n", locations[playerLocation].tag);
	}
	else
	{
		printf("COMMAND�͂킩��܂���");
	}
}

/**
 * @brief	go��command�����s����
 *
 * @param	object [����] �o��location �̃|�C���^
 */
bool executeGo(const char* object)
{
	if (object != NULL && strcmp(object, "north") == 0 && playerLocation != NORTH) 
	{
		playerLocation = NORTH;
		PrintString("�k��\n");
	}
	else if (object != NULL && strcmp(object, "east") == 0 && playerLocation != EAST)
	{
		playerLocation = EAST;
		PrintString("����\n");
	}
	else if (object != NULL && strcmp(object, "south") == 0 && playerLocation != SOUTH)
	{
		playerLocation = SOUTH;
		PrintString("���\n");
	}
	else if (object != NULL && strcmp(object, "west") == 0 && playerLocation != WEST)
	{
		playerLocation = WEST;
		PrintString("����\n");
	}
	else if (object != NULL && strcmp(object, "back") == 0 && playerLocation > 0)
	{
		playerLocation = 0;
		executeLook("around");
	}
	else if (object != NULL && strcmp(object, "north") == 0 && playerLocation == NORTH ||
		    object != NULL && strcmp(object, "east") == 0 && playerLocation == EAST ||
		    object != NULL && strcmp(object, "south") == 0 && playerLocation == SOUTH ||
		    object != NULL && strcmp(object, "west") == 0 && playerLocation == WEST)
	{
			printf("����͌��݂̏ꏊ�ł���I\n");
			return false;
	}
	else
	{
		PrintString("��������������͂��Ă��������I\n");
	}
}

/**
 * @brief	search��command�����s����
 *
 */
void executeSearch()
{
	if (locations[playerLocation].num_items > 0) 
	{
		PrintString("�A�C�e����������܂����F \n");
		if (playerLocation == WEST)
		{
			objs[3].itemQuantity++;
			if(objs[3].itemQuantity > 0)
			printf("%s\n", objs[3]);
		}
		else if (playerLocation == EAST && inventory[3] == 1)
		{
			objs[1].itemQuantity++;
			if(objs[1].itemQuantity > 0)
			printf("%s\n", objs[1]);
		}
		else if (playerLocation == SOUTH)
		{
			objs[0].itemQuantity++;
			objs[2].itemQuantity++;
			if(objs[0].itemQuantity > 0||objs[2].itemQuantity > 0)
			printf("%s\n%s\n", items[0],items[2]);
		}
	}
	else if (playerLocation == WEST && inventory[1] == 1)
	{
		PrintString("���̋L�������߂���\n");
		PrintString("YOU WIN!!\n");
		gameMsg_End();
		exit(0);
	}
	else
	{
		PrintString("��������܂���B\n");
	}
}

/**
 * @brief	look��command�����s����
 *
 * @param	object [����] �o��items �̃|�C���^
 */
void executeTake(const char *object)
{
	if (object != NULL && strcmp(object, "key") == 0 && playerLocation == EAST)
	{
		inventory[1]++;
		PrintString("���̃J�M���擾�����I\n");
		objs[1].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "torch") == 0 && playerLocation == WEST)
	{
		inventory[3]++;
		PrintString("������ɓ��ꂽ�I\n");
		objs[3].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "wood") == 0 && playerLocation == SOUTH)
	{
		inventory[0]++;
		PrintString("�؍ނ���ɓ��ꂽ�I\n");
		objs[0].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "shell") == 0 && playerLocation == SOUTH)
	{
		inventory[2]++;
		PrintString("�k����ɓ��ꂽ�I\n");
		objs[2].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else
	{
		PrintString("OBJECT NOT FOUND\n");
	}
}

/**
 * @brief	location�̏���
 *
 * @param	object [����] �o��area struct description �̃|�C���^
 */
void executeLocation(const char* object)
{
	if (playerLocation == EAST)
	{
		printf("%s\n", locations[playerLocation].description);
		PrintString("ENTER?\n");
		getInput();
		if (inventory[3] > 0 && inventory[4] <= 0)
		{
			PrintString("YOU ENTERED THE DARK CAVE\n");
			PrintString("���Ȃ��͈Èł̒��Ŗ����Ă���N�}�������܂���\n");
			PrintString("�����āA���̃N�}�͋N���܂����B\n");
			PrintString("���Ȃ��͎E����܂���\n");
			PrintString("GAME OVER\n");
			gameMsg_End();
			exit(0);
		}
		else if (inventory[3] > 0 && inventory[4] > 0)
		{
			PrintString("YOU ENTERED THE DARK CAVE\n");
			PrintString("���Ȃ��͈Èł̒��Ŗ����Ă���N�}�������܂���\n");
			PrintString("�����āA���̃N�}�͋N���܂����B\n");
			PrintString("���ǁA���펝���Ă���̂ŁA�N�}���E����\n\n\n");
			executeSearch();
		}
		else
		{
			PrintString("TORCH��T���Ă��������I\n");
		}
	}
	else if (playerLocation == SOUTH)
	{
		printf("%s\n", locations[playerLocation].description);
	}
	else if (playerLocation == NORTH)
	{
		printf("%s\n", locations[playerLocation].description);
	}
	else if (playerLocation == WEST)
	{
		printf("%s\n", locations[playerLocation].description);
		PrintString("CLIMB?\n");
		getInput();
		if (inventory[1] > 0)
		{
			PrintString("YOU ENTERED THE TREE HOUSE\n");
		}
		else
		{
			PrintString("GOLDEN KEY��T���Ă��������I\n");
		}
	}
}


/**
 * @brief	COMMAND��\������
 *
 */
void printCommand()
{
	printf("COMMAND PALETTE\n");
	printf("-------------------------------------------------|\n");
	printf("look around: ���݂̏ꏊ��\������\n");
	printf("search : ����ɃA�C�e����T��\n");
	printf("go '����': north(�k), east(��), south(��), west(��)\n");
	printf("take '�A�C�e����': �E��\n");
	printf("quit : �Q�[�����I������\n");
	printf("inventory : �C���x���g���[��\������\n");
	printf("check stats : �L�����N�^�[����\������\n");
	printf("craft spear : ������쐬����\n");
	printf("-------------------------------------------------|\n");
}

/**
 * @brief	�v���C���[����\�����鏈��
 *
 * @param	stats [����] �o��object�̃|�C���^
 */
void executeStats(const char* object)
{
	if (object != NULL && strcmp(object, "stats") == 0)
	{
			PrintStats();
	}
	else
	{
		PrintString("COMMAND�͂킩��܂���B\n");
	}
}

/**
 * @brief	������쐬����
 *
 * @param	���햼 [����] �o��object�̃|�C���^
 */
void executeCraft(const char* object)
{
	if (object != NULL && strcmp(object, "spear") == 0 && inventory[0] > 0 && inventory[2] > 0)
	{
		inventory[4]++;
		PrintString("������쐬���܂����I\n");
		inventory[0]--;
		inventory[2]--;
	}
	else if (object != NULL && strcmp(object, "spear") == 0 && inventory[0] <= 0 && inventory[2] <= 0)
	{
		PrintString("�K�v�ȑf�ނ��擾���Ă��������I");
	}
	else
	{
		PrintString("OBJECT NOT FOUND\n");
	}
}


/**
 *  @brief �v���C���[����\�����鏈��
 *
 **/
void PrintStats()
{
	chara character;
	character.HP = 100;
	character.maxHP = 100;
	character.attack = 0;
	if (inventory[4] == 1)
	character.attack += 50;

	printf("HP : %d/%d\n", character.HP, character.maxHP);
	printf("Attack : %d\n", character.attack);
}

/**
 * @brief	�v���C���[�C���x���g���[��\������֐�
 *
 * @param	inventory �o�� items[i] �̃|�C���^
 */
void printInventory(int inventory[numItems])
{
	printf("\n%s�̃C���x���g���[: \n", name);
	for (int i = 0; i < numItems; i++)
	{
		if (inventory[i] > 0)
		{
			printf("%s\n", items[i]);
		}
	}
}

/**
 * @brief	������̏o��
 *
 * @param	buf [����] �o�͕�����z��̃|�C���^
 */
void PrintString(const char* buf)
{
	int N = strlen(buf);
	PlaySound(TEXT("type1.wav"), NULL, SND_ASYNC);
	for (int i = 0; i < N; i++)
	{
		printf("%c", buf[i]);
		Sleep(70);
	}
	PlaySound(NULL, 0, 0);
}

/**
 * @brief	�R���\�[���E�B���h�E�̃^�C�g���o�[�ɕ\�������e�L�X�g��ݒ�
 *
 * @param	title [����] �E�B���h�E�^�C�g���ɕ\������e�L�X�g
 */
void SetCaption(const char* title)
{
	SetConsoleTitle(title);
}

/**
* @brief	�R���\�[���E�B���h�E�̕\������郂�[�h
*/
void SetScreenMode()
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	GetConsoleMode(hOut, &dwMode);
	SetConsoleMode(hOut, dwMode);
	GetConsoleMode(hIn, &dwMode);
	SetConsoleMode(hIn, dwMode);
}

/**
 * @brief	�t�H���g�T�C�Y�ݒ�
 *
 * @param	width, height�̃t�H���g�T�C�Y�����
 */
inline void SetFontSize(int width, int height)
{
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hOut, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = width;
	lpConsoleCurrentFontEx->dwFontSize.Y = height;
	SetCurrentConsoleFontEx(hOut, 0, lpConsoleCurrentFontEx);
}

/**
 * @brief	��ʏ���
 */
void ClearScreen()
{
	system("CLS");
}


/**
* @brief	�����F�ݒ�
*
* @param	color [����] �����F
* @note
*  �����F��enum COLORS���Q�Ƃ���
*/
void ConsoleTextColor(int color)
{
	screen_buffer_info.wAttributes &= ~0x000f;
	screen_buffer_info.wAttributes |= (color & 0x0f);
	SetConsoleTextAttribute(hOut, screen_buffer_info.wAttributes);
}

/**
 * @brief	�����F���P�x��
 */
void SetHighVideoColor()
{
	SetConsoleTextAttribute(hOut, screen_buffer_info.wAttributes |= FOREGROUND_INTENSITY);
}

/**
* @brief �R���\�[���̍��W�ɕ\���������
*
* @param x, y ���͍͂��W
*/
void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}