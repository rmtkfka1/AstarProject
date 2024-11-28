#include "pch.h"
#include "Board.h"


Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size)
{
	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; ++y)
	{
		for (int32 x = 0; x < 25; ++x)
		{
			Color color = GetTileColor(Pos(x, y));
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}

}

void Board::GenerateMap()
{
}

TileType Board::GetTileType(const Pos& pos)
{
	return TileType::NONE;
}

Color Board::GetTileColor(const Pos& color)
{
	return Color::RED;
}

