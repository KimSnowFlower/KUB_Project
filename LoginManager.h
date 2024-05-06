#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <vector>

// ����� ������ ��� ����ü
struct UserInfo {
    std::string id;
    std::string password;
    bool isMaster;
};

class LoginManager {
public:
    LoginManager(const std::string& filePath); // ������
    ~LoginManager(); // �Ҹ���

    bool Login(const std::string& id, const std::string& password); // �α��� �Լ�

private:
    std::vector<UserInfo> userInfoList; // ����� ������ �����ϴ� ����

    // ���� ���Ͽ��� ����� ������ �о���� �Լ�
    void ReadExcel(const std::string& filePath);
};

#endif