#pragma once
#include "ConsoleHelper.h"

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

	void Init(int32 size);
	void Render();

private:
	void GenerateMap();
	TileType GetTileType(const Pos& pos);
	Color	 GetTileColor(const Pos&color);
	Pos		 GetEnterPos() { return Pos(1, 1); }
	Pos		 GetExitPos() { return Pos(_size-1, _size-1); }


private:
	const char* TILE = "бс";
	TileType _board[BOARDMAXSIZE][BOARDMAXSIZE] = {};
	int32	 _size = 0;
};

