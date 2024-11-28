#include "pch.h"
#include "Board.h"
#include "Player.h"

int main()
{
	::srand(static_cast<uint32>(time(nullptr)));

	Player* player = new Player();
	Board* board = new Board();

	board->Init(25,player);
	player->Init(board);

	uint64 lastTick = 0;

	while (1)
	{
		uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTime = currentTick - lastTick;
		lastTick = currentTick;
		player->Update(deltaTime);
		board->Render();
	}

	delete board;
	delete player;
}