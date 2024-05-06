#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <windows.h>
#include <string>
#include "LoginManager.h"

#pragma comment(lib, "Comctl32.lib")

class WindowManager {
public:
    WindowManager(const std::string& filePath);    // WindowManager ������
    ~WindowManager();   // WindowManager �Ҹ���

    static WindowManager* s_instance;

    // â ���� �Լ�
    void CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

    // �α��� ��ư Ŭ�� �̺�Ʈ ó�� �Լ�
    void OnLoginButtonClick(HWND hwnd);

    // ���ο� ȭ�� ���� �Լ�
    void CreateNewScreen(const std::string& username);
private:
    // ������ ���ν��� �ݹ� �Լ�
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;                            // ������ �ڵ�
    static const wchar_t* m_className;      // ������ Ŭ���� �̸�
    static const wchar_t* m_windowTitle;    // ������ ����
    static const int m_width;               // ������ �ʺ�
    static const int m_height;              // ������ ����

    HWND m_editId;                          // ���̵� �ؽ�Ʈ ����
    HWND m_editPs;                          // ��й�ȣ �ؽ�Ʈ ����
    HWND m_buttonLogin;                     // �α��� ��ư

    static const int ID_BUTTON_LOGIN = 1001;

    LoginManager loginManager; // LoginManager ��ü ������
    std::string excelFilePath; // ���� ���� ���

    void CreateEditIdBox();
    void CreateEditPsBox();
    void CreateButtonLogin();

    void ShowErrorMessage(HWND hwnd, LPCWSTR message);
};

#endif // WINDOW_MANAGER_H