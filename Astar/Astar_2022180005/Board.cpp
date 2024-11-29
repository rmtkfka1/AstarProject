#include "pch.h"
#include "Board.h"
#include "Player.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(HWND hwnd, HDC backBuffer, int32 size, Player* player)
{
	_hwnd = hwnd;
	_size = size;
	_player = player;
	_backBuffer = backBuffer;
	

	GenerateMap();

	_wallTexture.LoadTexture("box.png", _backBuffer);
	_emptyTexture.LoadTexture("grass.jpg", _backBuffer);
	_goalTexture.LoadTexture("star.jpg", _backBuffer);

}

void Board::Render()
{
	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			TileType type = GetTileType(Pos(x, y));
			
			switch (type)
			{
			case TileType::NONE:
				break;
			case TileType::EMPTY:
				_emptyTexture.RenderImage(_backBuffer, x * TILESIZE, y * TILESIZE);
				break;
			case TileType::WALL:
				_wallTexture.RenderImage(_backBuffer, x * TILESIZE, y * TILESIZE);
				break;
			case TileType::GOAL:
				_goalTexture.RenderImage(_backBuffer, x * TILESIZE, y * TILESIZE);

			default:
				break;
			}

		}
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
				_board[x + 1][y] = TileType::EMPTY;
				continue;
			}

			//우측도달 하단으로 벽뚫기
			if (x == _size - 2)
			{
				_board[x][y + 1] = TileType::EMPTY;
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
				_board[x + 1][y] = TileType::EMPTY;
			}
		}
	}

};

TileType Board::GetTileType(Pos pos)
{

	if (pos == GetEndPos())
	{
		return TileType::GOAL;
	}

	if (pos.x < 0 || pos.y < 0 || pos.x >= _size || pos.y >= _size)
	{
		return TileType::NONE;
	}


	return _board[pos.x][pos.y];
}


