#pragma once

class Board;


class Player
{
	enum
	{
		MOVE_TICK = 100
	};

public:
	void Init(HWND hwnd, HDC backBuffer,Board* board);
	void Update(uint64 deltaTime);
	void Render();

public:
	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

private:
	void CalculatePath();
	bool CanGo(Pos pos);


private:
	Pos _pos;
	int32 _dir = DIR_UP;
	Board* _board;

	uint64 _sumTime = 0;
	queue<Pos> _path;
	vector<pair<Pos,int>>_prevPos;
private:
	int num = 0;
	HWND _hwnd;
	HDC _backBuffer;
	Texture _texture;
};

