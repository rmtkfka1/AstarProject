#pragma once

class Board;



class Player
{
	enum
	{
		MOVE_TICK = 400
	};

public:
	void Init(Board* board);
	void Update(uint64 deltaTime);

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

	//vector<int> _path;
	uint64 _sumTime = 0;

	queue<Pos> _path;
};

