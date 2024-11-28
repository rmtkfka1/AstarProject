#pragma once

class Player;

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
	GOAL,
};

const int BOARDMAXSIZE = 100;

class Board
{
public:
	Board();
	~Board();

	void Init(HWND hwnd ,HDC backBuffer, int32 size, Player* player);
	void Render();

	TileType GetTileType(Pos pos);
	Pos		 GetStartPos() { return Pos(1, 1); }
	Pos		 GetEndPos() { return Pos(_size - 2, _size - 2); }

private:
	void GenerateMap();

private:
	HWND _hwnd;
	HDC	 _backBuffer;


private:
	TileType		_board[BOARDMAXSIZE][BOARDMAXSIZE] = {};
	int32			_size = 0;
	Player* _player;

private:
	Texture _wallTexture;
	Texture _emptyTexture;
	Texture _goalTexture;

};

