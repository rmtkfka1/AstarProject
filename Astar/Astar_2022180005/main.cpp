#include "pch.h"

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX),
                     CS_CLASSDC,
                     WndProc,
                     0L,
                     0L,
                     GetModuleHandle(NULL),
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     L"2022180005 Astar",
                     NULL };

    RegisterClassEx(&wc);

    RECT wr = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindow(wc.lpszClassName, L"2022180005 Astar",
        WS_OVERLAPPEDWINDOW,
        100, // 윈도우 좌측 상단의 x 좌표
        100, // 윈도우 좌측 상단의 y 좌표
        wr.right - wr.left, // 윈도우 가로 방향 해상도
        wr.bottom - wr.top, // 윈도우 세로 방향 해상도
        NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    MSG msg = {};

    unique_ptr<Engine> engine = make_unique<Engine>();

    engine->Init(hwnd,1);

    while (WM_QUIT != msg.message) 
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            engine->Update();
            engine->Render();
        }
    }

    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);


    return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {


    switch (msg)
    {
    case WM_SIZE:

        return 0;
    case WM_SYSCOMMAND:
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_LBUTTONUP:
        break;
    case WM_RBUTTONUP:
        break;
    case WM_KEYDOWN:
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
