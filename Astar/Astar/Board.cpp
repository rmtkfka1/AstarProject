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
	_size = size;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
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

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_board[x][y] = TileType::WALL;
			else
				_board[x][y] = TileType::EMPTY;
		}
	}

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			if (y == _size - 2 && x == _size - 2)
			{
				continue;
			}


			//하단도달 우측으로 벽뚫기
			if (y == _size - 2)
			{
				_board[x+1][y] = TileType::EMPTY;
				continue;
			}

			//우측도달 하단으로 벽뚫기
			if (x == _size - 2)
			{
				_board[x][y+1] = TileType::EMPTY;
				continue;
			}

			const int randomNum = ::rand() % 2;

			if (randomNum == 0)
			{
				//아래로 벽뚫기
				_board[x][y + 1] = TileType::EMPTY;
			}
			else
			{
				//우측으로 벽뚫기
				_board[x+1][y] = TileType::EMPTY;
			}
		}
	}
	





}

TileType Board::GetTileType(const Pos& pos)
{

	if (pos.x < 0 || pos.y < 0 || pos.x >= _size || pos.y >= _size)
	{
		return TileType::NONE;
	}

	return _board[pos.x][pos.y];
}

Color Board::GetTileColor(const Pos& pos)
{
	if (GetExitPos() == pos)
	{
		return Color::BLUE;
	}

	TileType type = GetTileType(pos);

	switch (type)
	{
	case TileType::NONE:
		return Color::YELLOW;
		break;
	case TileType::EMPTY:
		return Color::GREEN;
		break;
	case TileType::WALL:
		return Color::RED;
		break;
	default:
		break;
	}

}

