#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <windows.h>
#include <string>
#include "LoginManager.h"

#pragma comment(lib, "Comctl32.lib")

class WindowManager {
public:
    WindowManager(const std::string& filePath);    // WindowManager 생성자
    ~WindowManager();   // WindowManager 소멸자

    static WindowManager* s_instance;

    // 창 생성 함수
    void CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

    // 로그인 버튼 클릭 이벤트 처리 함수
    void OnLoginButtonClick(HWND hwnd);

    // 새로운 화면 생성 함수
    void CreateNewScreen(const std::string& username);
private:
    // 윈도우 프로시저 콜백 함수
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;                            // 윈도우 핸들
    static const wchar_t* m_className;      // 윈도우 클래스 이름
    static const wchar_t* m_windowTitle;    // 윈도우 제목
    static const int m_width;               // 윈도우 너비
    static const int m_height;              // 윈도우 높이

    HWND m_editId;                          // 아이디 텍스트 상자
    HWND m_editPs;                          // 비밀번호 텍스트 상자
    HWND m_buttonLogin;                     // 로그인 버튼

    static const int ID_BUTTON_LOGIN = 1001;

    LoginManager loginManager; // LoginManager 객체 포인터
    std::string excelFilePath; // 엑셀 파일 경로

    void CreateEditIdBox();
    void CreateEditPsBox();
    void CreateButtonLogin();

    void ShowErrorMessage(HWND hwnd, LPCWSTR message);
};

#endif // WINDOW_MANAGER_H