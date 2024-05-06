#include "WindowManager.h"
#include <Windows.h>
#include <stdexcept>

const wchar_t* WindowManager::m_className = L"MainWindowClass";             // 윈도우 클래스 이름 정의
const wchar_t* WindowManager::m_windowTitle = L"강남대 교육방송국 KUB";      // 윈도우 제목 정의
// 윈도우 너비, 높이 정의
const int WindowManager::m_width = 1000;
const int WindowManager::m_height = 800;

WindowManager* WindowManager::s_instance = nullptr;
// WindowManager 생성자
WindowManager::WindowManager(const std::string& filePath) : m_hwnd(nullptr), loginManager(nullptr), excelFilePath(filePath) {}

// WindowManager 소멸자
WindowManager::~WindowManager() {}

// 창 생성 함수
// hInstance : 현재 실행 중인 인스턴스의 핸들
// nCmdShow : 윈도우를 보여줄 방법을 지정하는 값
void WindowManager::CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // 윈도우 클래스 구조체 정의 및 초기화
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc; // 윈도우 프로시저 콜백 함수 지정
    wc.hInstance = hInstance;
    wc.lpszClassName = m_className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 기본 커서 사용

    s_instance = this;

    // 윈도우 클래스 등록
    RegisterClass(&wc);

    // 로그인 버튼을 위한 ID를 등록
    // 등록된 ID로 CreateWindow 함수를 사용하여 윈도우를 생성할 수 있습니다.
    // ID_BUTTON_LOGIN 상수는 WindowManager.h에 정의되어 있어야 합니다.
    UINT buttonLoginID = ID_BUTTON_LOGIN;
    RegisterWindowMessageW((LPWSTR)&buttonLoginID);

    // 윈도우 생성
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

    // 윈도우 생성 실패 시 처리
    if (m_hwnd == NULL) {
        return;
    }

    CreateEditIdBox();
    CreateEditPsBox();
    CreateButtonLogin();

    // 윈도우를 화면에 표시
    ShowWindow(m_hwnd, nCmdShow);
}

// 윈도우 프로시저 콜백 함수
// Windows 프로그래밍에서 중요한 개념!!
// Windows 시스템에서 윈도우 메시지를 처리하는 데 사용
// 윈도우가 생성되고 사용자가 이벤트 (ex. 마우스 클릭, 키보드 입력 등)를 수생하면,
// 시스템은 해당 이벤트에 대한 메시지를 윈도우 프로시져에 보냄
// hwnd : 메시지를 수신하는 윈도우의 핸들
// uMsg : 수신된 메시지의 종류를 나타내는 메시지 식별자
// wParam : 메시지와 관련된 추가적인 정보를 전달하는 매개변수
// -> 보통 마우스나 키보드 이벤트에서 발생한 추가 정보를 전달
// -> 이벤트에서의 상태를 전달
// lParam : 메세지와 관련된 추가적인 정보를 전달하는 매개변수
// -> wParam과 다르게 더 많은 정보를 전달
// -> 주로 메시지와 관련된 좌표 정보나 포인터 등을 전달
LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_BUTTON_LOGIN: // 로그인 버튼의 ID에 따라 처리
            // 로그인 버튼 클릭 이벤트 처리
            s_instance->OnLoginButtonClick(hwnd); // s_instance를 사용하여 OnLoginButtonClick 함수 호출
            break;
            // 다른 버튼의 클릭 이벤트 처리 등
        }
        break;
    }
    case WM_DESTROY:    // 윈도우가 파괴 때 종료 메시지 전송
        PostQuitMessage(0);
        return 0;
    default:            // 기본 처리
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
// Windows 시스템은 윈도우가 생성될 때마다 윈도우 프로시저의 주소를 저장하고,
// 해당 윈도우에 발생하는 모든 메시지는 해당 프로시저로 전달
// 이것이 "콜백" 함수라 불리는 이유이며, 시스템이 이 함수를 호출하여 발생한 이벤트를 처리하도록 요청하기 때문이다

// 로그인 버튼 클릭 이벤트 처리 함수
void WindowManager::OnLoginButtonClick(HWND hwnd) { // hwnd 매개변수 추가
    // 아이디와 비밀번호 입력 상자에서 입력된 내용 가져오기
    wchar_t id[100];
    GetWindowText(m_editId, id, 100);
    std::wstring username(id);

    wchar_t ps[100];
    GetWindowText(m_editPs, ps, 100);
    std::wstring password(ps);

    // 로그인 수행
    bool loginSuccess = loginManager.Login(std::string(username.begin(), username.end()), std::string(password.begin(), password.end()));

    if (loginSuccess) {
        // 로그인 성공 시 새로운 화면 생성
        CreateNewScreen(std::string(username.begin(), username.end()));
    }
    else {
        // 로그인 실패 시 에러 메시지 표시
        ShowErrorMessage(hwnd, L"아이디 혹은 비밀번호를 확인하세요");
    }
}

void WindowManager::CreateEditIdBox() {
    // 아이디 입력 상자 생성
    m_editId = CreateWindowEx(
        0,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        m_width - 250, 50, 200, 25, // 오른쪽 상단에 위치하도록 좌표 및 크기 조정
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

void WindowManager::CreateEditPsBox() {
    // 비밀번호 입력 상자 생성
    m_editPs = CreateWindowEx(
        0,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
        m_width - 250, 100, 200, 25, // 오른쪽 상단에 위치하도록 좌표 및 크기 조정
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

void WindowManager::CreateButtonLogin() {
    // 로그인 버튼 생성
    m_buttonLogin = CreateWindowEx(
        0,
        L"BUTTON",
        L"로그인",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        m_width - 250, 150, 200, 30, // 오른쪽 상단에 위치하도록 좌표 및 크기 조정
        m_hwnd,
        NULL,
        NULL,
        NULL
    );
}

// 새로운 화면 생성 함수 구현
void WindowManager::CreateNewScreen(const std::string& username) {
    // 여기에 새로운 화면 생성하는 코드 추가
}

void WindowManager::ShowErrorMessage(HWND hwnd, LPCWSTR message) {
    MessageBox(hwnd, message, L"Error", MB_ICONERROR);
}