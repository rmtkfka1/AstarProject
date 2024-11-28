#include "pch.h"
#include "Engine.h"
#include "Player.h"
#include "Board.h"
#include "KeyManager.h"
Engine::Engine()
{
}

Engine::~Engine()
{
    SelectObject(_backBuffer, _oldBitmap);
    DeleteObject(_bufferBitmap);
    DeleteDC(_backBuffer);
    ReleaseDC(_hwnd, _hdc); 

    delete _player;
    delete _board;

}

void Engine::Init(HWND hwnd)
{
	_hwnd = hwnd;

    _hdc = GetDC(_hwnd);
    _backBuffer = CreateCompatibleDC(_hdc);
    _bufferBitmap = CreateCompatibleBitmap(_hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
    _oldBitmap = (HBITMAP)SelectObject(_backBuffer, _bufferBitmap);

    if (_player)
    {
        delete  _player;
        _player = nullptr;
    }

    if (_board)
    {
        delete _board;
        _board = nullptr;
    }
    
    _player = new Player();
    _board = new Board();

    _board->Init(_hwnd, _backBuffer, 25, _player);
    _player->Init(_hwnd,_backBuffer,_board);

    KeyManager::GetInstance()->Init(_hwnd);

}

void Engine::Update()
{
    uint64 currentTick = ::GetTickCount64();
    const uint64 deltaTime = currentTick - lastTick;
    lastTick = currentTick;

    KeyManager::GetInstance()->Update();


    if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::R))
    {
        Init(_hwnd);
    }


    _player->Update(deltaTime);
}

void Engine::RenderBegin()
{
    HBRUSH backgroundBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    FillRect(_backBuffer, &rect, backgroundBrush);
}


void Engine::RenderEnd()
{
    BitBlt(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, _backBuffer, 0, 0, SRCCOPY);
}

void Engine::Render()
{   

    RenderBegin();
   
    // ----- ���� ������ �ڵ� -----
  
    _board->Render();
    _player->Render();

    TextRender(500,0,"������:2022180005 �����");

    TextRender(500, 20, "WINAPI �� ����Ͽ� ����");
    TextRender(500, 40, "������������ �� ���̽�Ÿ �˰��� ����");
    TextRender(500, 60, "R:����");
    // ----- ���� ������ �ڵ� �� -----


    RenderEnd();

}

void Engine::TextRender(int x, int y ,const CHAR* message)
{
    TextOutA(_backBuffer, x, y, message, strlen(message));
}
