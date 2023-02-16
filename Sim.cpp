// Sim.cpp : 定义应用程序的入口点。
//
#pragma warning(disable:4302)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6386)
#pragma warning(disable:6387)

#include "framework.h"
#include "Sim.h"

#define MAX_LOADSTRING 100
#define WNDX 800
#define WNDY 600

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
const int sysX = GetSystemMetrics(SM_CXSCREEN);
const int sysY = GetSystemMetrics(SM_CYSCREEN);
/*
const int mapSize_X;
const int mapSize_y;
const int sizeOfResidence_X;
const int sizeOfResidence_Y;
const int waterRequest_E_residenceL;
const int electricityRequest_E_residenceL;
const int waterRequest_E_storeL;
const int electricityRequest_E_storeL;
const int waterRequest_E_factory;
const int electricityRequest_E_factory;
const int waterRequest_E_residenceH;
const int electricityRequest_E_residenceH;
const int waterRequest_E_storeH;
const int electricityRequest_E_storeH;
const int waterRequest_E_officeBuilding;
const int electricityRequest_E_officebuilding;
const int flux_pump;
const int flux_waterworks;
const int pipeFunctionRadiu;
const int flux_powerplant_Wind;
const int flux_powerplant_Coal;
const int flux_powerplant_Solar;
const int flux_powerplant_Nuclear;
const int cableFunctionRadiu;
const int shoppingRequest_E_L;
const int shoppingRequest_E_H;
const int customerRequest_E_L;
const int customerRequest_E_H;
const int productRequest_E_L;
const int productRequest_E_H;
const int jobRequest_E_L;
const int jobRequest_E_H;
const int workerRequest_E_storeL;
const int workerRequest_E_storeH;
const int workerRequest_E_factory;
const int workerRequest_E_officebuiding;
int money = 0;
int day = 0;
int population = 0;
int waterRequest_T = 0;
int waterSupply_T = 0;
int electricityRequest_T = 0;
int electricitySupply_T = 0;
int residenceLNum = 0;
int storeLNum = 0;
int factoryNum = 0;
int residenceHNum = 0;
int storeHNum = 0;
int officeBuildingNum = 0;
int pumpNum = 0;
int waterworksNum = 0;
int pipeLength = 0;
int powerplant_WindNum = 0;
int powerplant_CoalNum = 0;
int powerplant_SolarNum = 0;
int powerplant_NuclearNum = 0;
int cableLength = 0;
*/



// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIM));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SIM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME | WS_BORDER,
       (sysX - WNDX) / 2, (sysY - WNDY) / 2, WNDX, WNDY, 0, nullptr, nullptr, hInstance, nullptr);
   HWND hWndstatus = CreateWindowW(L"msctls_statusbar32", NULL, WS_CHILD | WS_VISIBLE,
       0, 0, 0, 0, hWnd, nullptr, hInstance, nullptr);
   LPRECT rct = (LPRECT)malloc(sizeof(LPRECT) * 2);
   GetWindowRect(hWndstatus, rct);
   MoveWindow(hWnd, (sysX - WNDX) / 2, (sysY - WNDY) / 2, WNDX, WNDY + rct->bottom - rct->top, true);
   MoveWindow(hWndstatus, 0, 0, 0, 0, true);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
