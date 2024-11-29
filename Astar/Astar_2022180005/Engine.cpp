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

void Engine::Init(HWND hwnd,int value)
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
    _player->Init(_hwnd,_backBuffer,_board,value);

    KeyManager::GetInstance()->Init(_hwnd);

}

void Engine::Update()
{
    uint64 currentTick = ::GetTickCount64();
    const uint64 deltaTime = currentTick - lastTick;
    lastTick = currentTick;

    KeyManager::GetInstance()->Update();


    if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::ONE))
    {
        Init(_hwnd,1);
    }

    if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::TWO))
    {
        Init(_hwnd, 2);
    }

    if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::THREE))
    {
        Init(_hwnd, 3);
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
   
    // ----- 실제 렌더링 코드 -----
  
    _board->Render();
    _player->Render();

    TextRender(550,0,"만든이:2022180005 김상혁");

    TextRender(550, 20,     "WINAPI 를 사용하여 구현");
    TextRender(550, 40,     "동적지형생성 및 여러가지 길찾기 알고리즘 적용");
    TextRender(550, 60,     "-------------------------------------키입력 안내-------------------------------------");
    TextRender(550, 80,     "1: 우수법(RightHand) 방법으로 길찾기");
    TextRender(550, 100,    "2: BFS(너비우선) 방법으로 길찾기");
    TextRender(550, 120,    "3: DFS(깊이우선) 방법으로 길찾기");
    // ----- 실제 렌더링 코드 끝 -----


    RenderEnd();

}

void Engine::TextRender(int x, int y ,const CHAR* message)
{
    TextOutA(_backBuffer, x, y, message, strlen(message));
}
