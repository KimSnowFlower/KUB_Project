#include <windows.h>
#include "WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::string excelFilePath = "E:\\KUB\\KUB_LOGIN.xlsx"; // ¿¢¼¿ ÆÄÀÏ °æ·Î
    WindowManager windowManager(excelFilePath);
    windowManager.CreateMainWindow(hInstance, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}