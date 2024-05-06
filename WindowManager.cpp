#include "WindowManager.h"
#include <Windows.h>
#include <stdexcept>

const wchar_t* WindowManager::m_className = L"MainWindowClass";             // ������ Ŭ���� �̸� ����
const wchar_t* WindowManager::m_windowTitle = L"������ ������۱� KUB";      // ������ ���� ����
// ������ �ʺ�, ���� ����
const int WindowManager::m_width = 1000;
const int WindowManager::m_height = 800;

WindowManager* WindowManager::s_instance = nullptr;
// WindowManager ������
WindowManager::WindowManager(const std::string& filePath) : m_hwnd(nullptr), loginManager(nullptr), excelFilePath(filePath) {}

// WindowManager �Ҹ���
WindowManager::~WindowManager() {}

// â ���� �Լ�
// hInstance : ���� ���� ���� �ν��Ͻ��� �ڵ�
// nCmdShow : �����츦 ������ ����� �����ϴ� ��
void WindowManager::CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // ������ Ŭ���� ����ü ���� �� �ʱ�ȭ
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc; // ������ ���ν��� �ݹ� �Լ� ����
    wc.hInstance = hInstance;
    wc.lpszClassName = m_className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // �⺻ Ŀ�� ���

    s_instance = this;

    // ������ Ŭ���� ���
    RegisterClass(&wc);

    // �α��� ��ư�� ���� ID�� ���
    // ��ϵ� ID�� CreateWindow �Լ��� ����Ͽ� �����츦 ������ �� �ֽ��ϴ�.
    // ID_BUTTON_LOGIN ����� WindowManager.h�� ���ǵǾ� �־�� �մϴ�.
    UINT buttonLoginID = ID_BUTTON_LOGIN;
    RegisterWindowMessageW((LPWSTR)&buttonLoginID);

    // ������ ����
    m_hwnd = CreateWindowEx(
        0,
        m_className,
        m_windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // ������ ���� ���� �� ó��
    if (m_hwnd == NULL) {
        return;
    }

    CreateEditIdBox();
    CreateEditPsBox();
    CreateButtonLogin();

    // �����츦 ȭ�鿡 ǥ��
    ShowWindow(m_hwnd, nCmdShow);
}

// ������ ���ν��� �ݹ� �Լ�
// Windows ���α׷��ֿ��� �߿��� ����!!
// Windows �ý��ۿ��� ������ �޽����� ó���ϴ� �� ���
// �����찡 �����ǰ� ����ڰ� �̺�Ʈ (ex. ���콺 Ŭ��, Ű���� �Է� ��)�� �����ϸ�,
// �ý����� �ش� �̺�Ʈ�� ���� �޽����� ������ ���ν����� ����
// hwnd : �޽����� �����ϴ� �������� �ڵ�
// uMsg : ���ŵ� �޽����� ������ ��Ÿ���� �޽��� �ĺ���
// wParam : �޽����� ���õ� �߰����� ������ �����ϴ� �Ű�����
// -> ���� ���콺�� Ű���� �̺�Ʈ���� �߻��� �߰� ������ ����
// -> �̺�Ʈ������ ���¸� ����
// lParam : �޼����� ���õ� �߰����� ������ �����ϴ� �Ű�����
// -> wParam�� �ٸ��� �� ���� ������ ����
// -> �ַ� �޽����� ���õ� ��ǥ ������ ������ ���� ����
LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_BUTTON_LOGIN: // �α��� ��ư�� ID�� ���� ó��
            // �α��� ��ư Ŭ�� �̺�Ʈ ó��
            s_instance->OnLoginButtonClick(hwnd); // s_instance�� ����Ͽ� OnLoginButtonClick �Լ� ȣ��
            break;
            // �ٸ� ��ư�� Ŭ�� �̺�Ʈ ó�� ��
        }
        break;
    }
    case WM_DESTROY:    // �����찡 �ı� �� ���� �޽��� ����
        PostQuitMessage(0);
        return 0;
    default:            // �⺻ ó��
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
// Windows �ý����� �����찡 ������ ������ ������ ���ν����� �ּҸ� �����ϰ�,
// �ش� �����쿡 �߻��ϴ� ��� �޽����� �ش� ���ν����� ����
// �̰��� "�ݹ�" �Լ��� �Ҹ��� �����̸�, �ý����� �� �Լ��� ȣ���Ͽ� �߻��� �̺�Ʈ�� ó���ϵ��� ��û�ϱ� �����̴�

// �α��� ��ư Ŭ�� �̺�Ʈ ó�� �Լ�
void WindowManager::OnLoginButtonClick(HWND hwnd) { // hwnd �Ű����� �߰�
    // ���̵�� ��й�ȣ �Է� ���ڿ��� �Էµ� ���� ��������
    wchar_t id[100];
    GetWindowText(m_editId, id, 100);
    std::wstring username(id);

    wchar_t ps[100];
    GetWindowText(m_editPs, ps, 100);
    std::wstring password(ps);

    // �α��� ����
    bool loginSuccess = loginManager.Login(std::string(username.begin(), username.end()), std::string(password.begin(), password.end()));

    if (loginSuccess) {
        // �α��� ���� �� ���ο� ȭ�� ����
        CreateNewScreen(std::string(username.begin(), username.end()));
    }
    else {
        // �α��� ���� �� ���� �޽��� ǥ��
        ShowErrorMessage(hwnd, L"���̵� Ȥ�� ��й�ȣ�� Ȯ���ϼ���");
    }
}

void WindowManager::CreateEditIdBox() {
    // ���̵� �Է� ���� ����
    m_editId = CreateWindowEx(
        0,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        m_width - 250, 50, 200, 25, // ������ ��ܿ� ��ġ�ϵ��� ��ǥ �� ũ�� ����
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

void WindowManager::CreateEditPsBox() {
    // ��й�ȣ �Է� ���� ����
    m_editPs = CreateWindowEx(
        0,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
        m_width - 250, 100, 200, 25, // ������ ��ܿ� ��ġ�ϵ��� ��ǥ �� ũ�� ����
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

void WindowManager::CreateButtonLogin() {
    // �α��� ��ư ����
    m_buttonLogin = CreateWindowEx(
        0,
        L"BUTTON",
        L"�α���",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        m_width - 250, 150, 200, 30, // ������ ��ܿ� ��ġ�ϵ��� ��ǥ �� ũ�� ����
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

// ���ο� ȭ�� ���� �Լ� ����
void WindowManager::CreateNewScreen(const std::string& username) {
    // ���⿡ ���ο� ȭ�� �����ϴ� �ڵ� �߰�
}

void WindowManager::ShowErrorMessage(HWND hwnd, LPCWSTR message) {
    MessageBox(hwnd, message, L"Error", MB_ICONERROR);
}