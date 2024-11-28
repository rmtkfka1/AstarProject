#pragma once
#include "ConsoleHelper.h"

class Player;

enum class TileType
{
	NONE=0,
	EMPTY,
	WALL
};

const int BOARDMAXSIZE = 100;

class Board
{

public:
	Board();
	~Board();

	void Init(int32 size , Player* player);
	void Render();

	TileType GetTileType(const Pos& pos);
	Color	 GetTileColor(const Pos& pos);
	Pos		 GetStartPos() { return Pos(1, 1); }
	Pos		 GetEndPos() { return Pos(_size - 2, _size - 2); }

private:
	void GenerateMap();

private:
	const char*		TILE = "бс";
	TileType		_board[BOARDMAXSIZE][BOARDMAXSIZE] = {};
	int32			_size = 0;
	Player*			_player;
};

