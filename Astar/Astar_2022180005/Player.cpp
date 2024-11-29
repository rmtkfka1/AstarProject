#include "pch.h"
#include "Player.h"
#include "Board.h"
#include "KeyManager.h"
void Player::Init(HWND hwnd, HDC backBuffer, Board* board, int value)
{
	_prevPos.clear();
	num = 0;
	_pos = board->GetStartPos();
	_board = board;
	_hwnd = hwnd;
	_backBuffer = backBuffer;
	_texture.LoadTexture("mario.jpg", _backBuffer);

	if (value == 1)
	{
		CalculatePath_RightHand();
	}
	else if (value == 2)
	{
		CalculatePath_BFS();
	}
	else if (value == 3)
	{
		CalculatePath_DFS();
	}
	else if (value == 4)
	{
		CalculatePath_Astar();
	}
	

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

	if (KeyManager::GetInstance()->GetButton(KEY_TYPE::UP))
	{
		if (MOVE_TICK > 10.0f)
		{
			MOVE_TICK--;
		}
	}

	if (KeyManager::GetInstance()->GetButton(KEY_TYPE::DOWN))
	{
		if (MOVE_TICK < 1000.0f)
		{
			MOVE_TICK++;
		}
	}

}

void Player::Render()
{

	for (int i = 0; i < _prevPos.size(); ++i)
	{
		int number = _prevPos[i].second;
		string str = to_string(number);
		TextOutA(_backBuffer, _prevPos[i].first.x * TILESIZE, _prevPos[i].first.y * TILESIZE, str.c_str(), str.size());
	}

	_texture.RenderImage(_backBuffer, _pos.x* TILESIZE, _pos.y* TILESIZE);

}

void Player::CalculatePath_RightHand()
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
			cout << start.x << " " << start.y << endl;
		}

		else if (CanGo(start + front[_dir]))
		{
			start += front[_dir];
			_path.push(start);
			cout << start.x << " " << start.y << endl;
		}

		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}



}

void Player::CalculatePath_BFS()
{

	Pos pos = _board->GetStartPos();
	Pos dest = _board->GetEndPos();

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	queue<Pos> q;
	q.push(pos);
	discovered[pos.x][pos.y] = true;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		cout << pos.x << " " << pos.y << "\n";
		_path.push(pos);

		if (pos == dest)
			break;
		
		for (int32 dir = 0; dir < DIR_COUNT; ++dir)
		{
			Pos nextPos = pos + front[dir];

			if (CanGo(nextPos) == false)
				continue;

			if (discovered[nextPos.x][nextPos.y] == true)
				continue;

			q.push(nextPos);
			discovered[nextPos.x][nextPos.y] = true;
			
		}

	}	
}

void Player::CalculatePath_DFS()
{

	const int32 size = _board->GetSize();
	vector<vector<bool>> visited(size, vector<bool>(size, false));
	visited[_pos.x][_pos.y] = true;
	Dfs(_pos,visited);
	
}


bool Player::Dfs(Pos pos, vector<vector<bool>>& visited)
{

	Pos dest = _board->GetEndPos();

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
	};

	_path.push(pos);
	cout << pos.x << " " << pos.y << endl;

	if (pos == dest)
	{
		return true;
	}



	for (int32 dir = 0; dir < DIR_COUNT; ++dir)
	{
		Pos nextPos = pos + front[dir];

		if (visited[nextPos.x][nextPos.y])
			continue;

		if(CanGo(nextPos))
		{
			visited[nextPos.x][nextPos.y] = true;

			bool find = Dfs(nextPos, visited);
			
			if (find)
				return true;
		}
	}

	return false;
}

void Player::CalculatePath_Astar()
{

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
