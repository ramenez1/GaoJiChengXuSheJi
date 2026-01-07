#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int pCmdShow)
{
	wchar_t ClassName[] = L"石从灏设计的窗口类"; 
	wchar_t Title[] = L"石从灏创建的窗口"; 

    // 定义窗口类
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW; // 设置风格
    wcex.lpfnWndProc = WndProc; // 指定处理消息的函数
    wcex.hInstance = hInstance; // 指定句柄
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //默认图标
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // 默认光标
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 白色背景
    wcex.lpszClassName = ClassName; // 设置类名

    // 注册
    RegisterClassEx(&wcex); 

    // 创建窗口
    HWND hWnd = CreateWindow(
        ClassName,          // 窗口类名
        Title,              // 窗口标题
        WS_OVERLAPPEDWINDOW,  // 默认窗口风格 
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, // 窗口位置和大小
        NULL, NULL, hInstance, NULL
    );


    ShowWindow(hWnd, pCmdShow);
    UpdateWindow(hWnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        wchar_t Text[] = L"石从灏成功地输出显示文本信息";

        TextOut(hdc, 200, 150, Text, lstrlen(Text));

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY: 
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
