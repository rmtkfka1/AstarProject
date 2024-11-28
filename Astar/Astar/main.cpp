#include "pch.h"
#include "Board.h"
#include "Player.h"

int main()
{
	::srand(static_cast<uint32>(time(nullptr)));

	shared_ptr<Player> player = make_shared<Player>();
	shared_ptr<Board> board = make_shared<Board>();

	while (1)
	{
		board->Render();
	}



}