#include "LoginManager.h"
#include <fstream>
#include <sstream>

// 생성자
LoginManager::LoginManager(const std::string& filePath) {
    // 엑셀 파일에서 사용자 정보를 읽어옴
    ReadExcel(filePath);
}

// 소멸자
LoginManager::~LoginManager() {}

// 엑셀 파일에서 사용자 정보를 읽어오는 함수
void LoginManager::ReadExcel(const std::string& filePath) {
    // 엑셀 파일 열기
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // 파일 열기 실패 시 예외 처리
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // 한 줄씩 읽어서 사용자 정보를 파싱하여 벡터에 저장
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, password, isMasterStr;
        if (!(iss >> id >> password >> isMasterStr)) {
            // 파싱 실패 시 예외 처리
            throw std::runtime_error("Error parsing line: " + line);
        }
        bool isMaster = (isMasterStr == "master");
        userInfoList.push_back({ id, password, isMaster });
    }

    file.close();
}

// 로그인 함수
bool LoginManager::Login(const std::string& id, const std::string& password) {
    // 사용자 정보 중에서 입력된 아이디와 일치하는 정보 찾기
    auto it = std::find_if(userInfoList.begin(), userInfoList.end(), [&id](const UserInfo& userInfo) {
        return userInfo.id == id;
        });

    if (it != userInfoList.end()) {
        // 아이디가 존재하면 비밀번호 확인
        if (it->password == password) {
            // 비밀번호가 일치하면 로그인 성공
            return true;
        }
        else {
            // 비밀번호가 일치하지 않으면 로그인 실패
            return false;
        }
    }
    else {
        // 아이디가 존재하지 않으면 로그인 실패
        return false;
    }
}