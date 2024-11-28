#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetStartPos();
	_board = board;

	CalculatePath();
}

void Player::Update(uint64 deltaTime)
{
	if (_path.empty())
		return;

	_sumTime += deltaTime;

	if (_sumTime >= MOVE_TICK)
	{
		_sumTime = 0;

		Pos nextPos = _path.front();
		_path.pop();
		_pos = nextPos;
	}

}

void Player::CalculatePath()
{
	
	Pos start = _board->GetStartPos();
	Pos dest = _board->GetEndPos();

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
	};

	while (start != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로, 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		if (CanGo(start + front[newDir]))
		{
			_dir = newDir;
			start += front[_dir];
			_path.push(start);
		}

		else if (CanGo(start + front[_dir]))
		{
			start += front[_dir];
			_path.push(start);
		}

		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}



}




bool Player::CanGo(Pos pos)
{
	if (_board == nullptr)
		assert(false);

	TileType type=_board->GetTileType(pos);

	if (type == TileType::EMPTY)
		return true;

	return false;
}
