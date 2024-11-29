#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(HWND hwnd, HDC backBuffer, Board* board)
{
	_prevPos.clear();
	num = 0;
	_pos = board->GetStartPos();
	_board = board;
	_hwnd = hwnd;
	_backBuffer = backBuffer;
	CalculatePath();
	_texture.LoadTexture("mario.jpg", _backBuffer);
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
		_prevPos.push_back(make_pair(_pos, num));
		_pos = nextPos;
		num++;
	}



}

void Player::Render()
{

	for (int i = 0; i < _prevPos.size(); ++i)
	{
		string str =to_string(_prevPos[i].second);
		TextOutA(_backBuffer, _prevPos[i].first.x * TILESIZE, _prevPos[i].first.y * TILESIZE, str.c_str(), str.size());
	}

	_texture.RenderImage(_backBuffer, _pos.x* TILESIZE, _pos.y* TILESIZE);

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

	TileType type = _board->GetTileType(pos);

	if (type != TileType::WALL)
		return true;

	return false;
}
