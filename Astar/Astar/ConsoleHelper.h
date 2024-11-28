#pragma once

enum class Color
{
	BLAKC = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHILE = RED | GREEN | BLUE
};


class ConsoleHelper
{

public:

	static void SetCursorPosition(int x, int y);
	static void SetCursorColor(Color color);
	static void ShowConsoleCursor(bool flag);

};

