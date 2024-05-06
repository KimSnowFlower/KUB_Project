#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <vector>

// 사용자 정보를 담는 구조체
struct UserInfo {
    std::string id;
    std::string password;
    bool isMaster;
};

class LoginManager {
public:
    LoginManager(const std::string& filePath); // 생성자
    ~LoginManager(); // 소멸자

    bool Login(const std::string& id, const std::string& password); // 로그인 함수

private:
    std::vector<UserInfo> userInfoList; // 사용자 정보를 저장하는 벡터

    // 엑셀 파일에서 사용자 정보를 읽어오는 함수
    void ReadExcel(const std::string& filePath);
};

#endif