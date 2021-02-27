/*
*Text-Based Adventure Game School Project
*Made by Elvan Mulyono
*-------------------------------------------
*AT11A026_10
*CL11 課題　No.7
*エルファンムルヨノ
*/

#include "Game.h"		//ゲームヘーダーファイル

/* Console 設定 */
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
DWORD dwMode = NULL;
COORD screen_buffer_size;
WORD screen_buffer_attribute = LIGHTGRAY;
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
#define CONSOLE_INPUT_MODE	( ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT )
#define CONSOLE_OUTPUT_MODE	(ENABLE_PROCESSED_OUTPUT | ENABLE_LVB_GRID_WORLDWIDE | ENABLE_VIRTUAL_TERMINAL_PROCESSING )

/* タイトル画面 */
void intro()
{
	/* 画面の設定 */
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

/* メニュー画面 */
void gameMsg_Menu()
{
	/* 画面の設定 */
	SetScreenMode();
	SetHighVideoColor();

	/* テキスト設定 */
	ConsoleTextColor(WHITE);
	SetFontSize(10, 20);
	printf("\t\t\t\t\t\t\t\tTHE BLUE ISLAND\n\n");
	Sleep(1000);
}

/* 開始画面 */
void gameMsg_Start()
{
	/* テキスト設定 */
	ConsoleTextColor(YELLOW);
	printCommand();
	Sleep(1000);

	/* INTRO */
	ConsoleTextColor(WHITE);
	PrintString("\n\nこのゲームは開発中ですよ！\n\n");
	PrintString("ストーリーとか苦手なのでこのゲームはまだ終わってない！\n\n");
	PrintString("許してください!!!\n\n");
	Sleep(1000);
	printf("-----------------------------------------------------------\n");
	printf("\n名前を入力: ");
	scanf("%[^\n]s", &name);
	rewind(stdin);
}

int main()
{
	/* INTRO */
	intro();
	ClearScreen();

	/* ゲーム開始画面 */
	gameMsg_Menu();
	gameMsg_Start();

	/* 始まり */
	printf("\nあなたは%sです。\n\n", name);
	Sleep(100);
	PrintString("あなたはブルーアイランドにおります。\n\n");
	PrintString("ブルーアイランドへようこそ\n\n");

	executeLook("around");
	Sleep(1000);
	
	/* COMMANDS */
	while (getInput() && execute(input));
	gameMsg_End();
	getchar();
	return EXIT_SUCCESS;
}

/*　終了画面 */
void gameMsg_End()
{
	PrintString("くそげーだけど\n");
	PrintString("Thank you for playing!\n");
}

/**
 * @brief	キーボードの入力を読み込む処理
 *
 * @param	keycode [入力] 出力keyboard keycode
 */
int KeyPress(int keyboard)
{
	return (GetAsyncKeyState(keyboard) & 0x8000 != 0);
}

/**
 * @brief	キーボードの入力を読み込む処理
 *
 */
static bool getInput()
{
printf("\n--> ");
return fgets(input, sizeof(input), stdin) != NULL;
}

/**
 * @brief	全部のcommandを実行する処理
 *
 * @param	input [入力] 出力getInput()のポインタ
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
			PrintString("馬鹿野郎、悪い言葉言うな・・\n");
		}
		else
		{
			printf("%sはわかりません。\n", command);
		}
	}
	return true;
}

/**
 * @brief	lookのcommandを実行する
 *
 * @param	object [入力] 出力objectのポインタ
 */
void executeLook(const char* object)
{
	if (object != NULL && strcmp(object, "around") == 0)
	{
		printf("現在の場所は %s です。。\n", locations[playerLocation].tag);
	}
	else
	{
		printf("COMMANDはわかりません");
	}
}

/**
 * @brief	goのcommandを実行する
 *
 * @param	object [入力] 出力location のポインタ
 */
bool executeGo(const char* object)
{
	if (object != NULL && strcmp(object, "north") == 0 && playerLocation != NORTH) 
	{
		playerLocation = NORTH;
		PrintString("北に\n");
	}
	else if (object != NULL && strcmp(object, "east") == 0 && playerLocation != EAST)
	{
		playerLocation = EAST;
		PrintString("東に\n");
	}
	else if (object != NULL && strcmp(object, "south") == 0 && playerLocation != SOUTH)
	{
		playerLocation = SOUTH;
		PrintString("南に\n");
	}
	else if (object != NULL && strcmp(object, "west") == 0 && playerLocation != WEST)
	{
		playerLocation = WEST;
		PrintString("西に\n");
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
			printf("それは現在の場所ですよ！\n");
			return false;
	}
	else
	{
		PrintString("正しい方向を入力してください！\n");
	}
}

/**
 * @brief	searchのcommandを実行する
 *
 */
void executeSearch()
{
	if (locations[playerLocation].num_items > 0) 
	{
		PrintString("アイテムが見つかりました： \n");
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
		PrintString("命の記憶を取り戻した\n");
		PrintString("YOU WIN!!\n");
		gameMsg_End();
		exit(0);
	}
	else
	{
		PrintString("何もありません。\n");
	}
}

/**
 * @brief	lookのcommandを実行する
 *
 * @param	object [入力] 出力items のポインタ
 */
void executeTake(const char *object)
{
	if (object != NULL && strcmp(object, "key") == 0 && playerLocation == EAST)
	{
		inventory[1]++;
		PrintString("金のカギを取得した！\n");
		objs[1].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "torch") == 0 && playerLocation == WEST)
	{
		inventory[3]++;
		PrintString("灯を手に入れた！\n");
		objs[3].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "wood") == 0 && playerLocation == SOUTH)
	{
		inventory[0]++;
		PrintString("木材を手に入れた！\n");
		objs[0].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else if (object != NULL && strcmp(object, "shell") == 0 && playerLocation == SOUTH)
	{
		inventory[2]++;
		PrintString("殻を手に入れた！\n");
		objs[2].itemQuantity--;
		locations[playerLocation].num_items--;
	}
	else
	{
		PrintString("OBJECT NOT FOUND\n");
	}
}

/**
 * @brief	locationの処理
 *
 * @param	object [入力] 出力area struct description のポインタ
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
			PrintString("あなたは暗闇の中で眠っているクマを見つけました\n");
			PrintString("そして、そのクマは起きました。\n");
			PrintString("あなたは殺されました\n");
			PrintString("GAME OVER\n");
			gameMsg_End();
			exit(0);
		}
		else if (inventory[3] > 0 && inventory[4] > 0)
		{
			PrintString("YOU ENTERED THE DARK CAVE\n");
			PrintString("あなたは暗闇の中で眠っているクマを見つけました\n");
			PrintString("そして、そのクマは起きました。\n");
			PrintString("けど、武器持っているので、クマを殺せる\n\n\n");
			executeSearch();
		}
		else
		{
			PrintString("TORCHを探してください！\n");
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
			PrintString("GOLDEN KEYを探してください！\n");
		}
	}
}


/**
 * @brief	COMMANDを表示する
 *
 */
void printCommand()
{
	printf("COMMAND PALETTE\n");
	printf("-------------------------------------------------|\n");
	printf("look around: 現在の場所を表示する\n");
	printf("search : 周りにアイテムを探す\n");
	printf("go '方向': north(北), east(東), south(南), west(西)\n");
	printf("take 'アイテム名': 拾う\n");
	printf("quit : ゲームを終了する\n");
	printf("inventory : インベントリーを表示する\n");
	printf("check stats : キャラクター情報を表示する\n");
	printf("craft spear : 武器を作成する\n");
	printf("-------------------------------------------------|\n");
}

/**
 * @brief	プレイヤー情報を表示する処理
 *
 * @param	stats [入力] 出力objectのポインタ
 */
void executeStats(const char* object)
{
	if (object != NULL && strcmp(object, "stats") == 0)
	{
			PrintStats();
	}
	else
	{
		PrintString("COMMANDはわかりません。\n");
	}
}

/**
 * @brief	武器を作成する
 *
 * @param	武器名 [入力] 出力objectのポインタ
 */
void executeCraft(const char* object)
{
	if (object != NULL && strcmp(object, "spear") == 0 && inventory[0] > 0 && inventory[2] > 0)
	{
		inventory[4]++;
		PrintString("武器を作成しました！\n");
		inventory[0]--;
		inventory[2]--;
	}
	else if (object != NULL && strcmp(object, "spear") == 0 && inventory[0] <= 0 && inventory[2] <= 0)
	{
		PrintString("必要な素材を取得してください！");
	}
	else
	{
		PrintString("OBJECT NOT FOUND\n");
	}
}


/**
 *  @brief プレイヤー情報を表示する処理
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
 * @brief	プレイヤーインベントリーを表示する関数
 *
 * @param	inventory 出力 items[i] のポインタ
 */
void printInventory(int inventory[numItems])
{
	printf("\n%sのインベントリー: \n", name);
	for (int i = 0; i < numItems; i++)
	{
		if (inventory[i] > 0)
		{
			printf("%s\n", items[i]);
		}
	}
}

/**
 * @brief	文字列の出力
 *
 * @param	buf [入力] 出力文字列配列のポインタ
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
 * @brief	コンソールウィンドウのタイトルバーに表示されるテキストを設定
 *
 * @param	title [入力] ウィンドウタイトルに表示するテキスト
 */
void SetCaption(const char* title)
{
	SetConsoleTitle(title);
}

/**
* @brief	コンソールウィンドウの表示されるモード
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
 * @brief	フォントサイズ設定
 *
 * @param	width, heightのフォントサイズを入力
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
 * @brief	画面消去
 */
void ClearScreen()
{
	system("CLS");
}


/**
* @brief	文字色設定
*
* @param	color [入力] 文字色
* @note
*  文字色はenum COLORSを参照する
*/
void ConsoleTextColor(int color)
{
	screen_buffer_info.wAttributes &= ~0x000f;
	screen_buffer_info.wAttributes |= (color & 0x0f);
	SetConsoleTextAttribute(hOut, screen_buffer_info.wAttributes);
}

/**
 * @brief	文字色高輝度化
 */
void SetHighVideoColor()
{
	SetConsoleTextAttribute(hOut, screen_buffer_info.wAttributes |= FOREGROUND_INTENSITY);
}

/**
* @brief コンソールの座標に表示するもの
*
* @param x, y 入力は座標
*/
void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}