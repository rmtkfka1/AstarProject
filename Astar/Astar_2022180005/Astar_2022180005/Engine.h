#pragma once
class Board;
class Player;

class Engine
{

public:

	Engine();
	~Engine();

	void Init(HWND hwnd);
	void Update();
	void RenderBegin();
	void RenderEnd();
	void Render();
	void TextRender(int x, int y, const CHAR* message);

private:
	Board* _board =nullptr;
	Player* _player=nullptr;
	UINT lastTick = 0;
private:
	HWND _hwnd;
	HDC     _hdc;
	HDC		_backBuffer;
	HBITMAP _bufferBitmap;
	HBITMAP _oldBitmap;
};

