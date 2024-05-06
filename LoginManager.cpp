#include "LoginManager.h"
#include <fstream>
#include <sstream>

// ������
LoginManager::LoginManager(const std::string& filePath) {
    // ���� ���Ͽ��� ����� ������ �о��
    ReadExcel(filePath);
}

// �Ҹ���
LoginManager::~LoginManager() {}

// ���� ���Ͽ��� ����� ������ �о���� �Լ�
void LoginManager::ReadExcel(const std::string& filePath) {
    // ���� ���� ����
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // ���� ���� ���� �� ���� ó��
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // �� �پ� �о ����� ������ �Ľ��Ͽ� ���Ϳ� ����
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, password, isMasterStr;
        if (!(iss >> id >> password >> isMasterStr)) {
            // �Ľ� ���� �� ���� ó��
            throw std::runtime_error("Error parsing line: " + line);
        }
        bool isMaster = (isMasterStr == "master");
        userInfoList.push_back({ id, password, isMaster });
    }

    file.close();
}

// �α��� �Լ�
bool LoginManager::Login(const std::string& id, const std::string& password) {
    // ����� ���� �߿��� �Էµ� ���̵�� ��ġ�ϴ� ���� ã��
    auto it = std::find_if(userInfoList.begin(), userInfoList.end(), [&id](const UserInfo& userInfo) {
        return userInfo.id == id;
        });

    if (it != userInfoList.end()) {
        // ���̵� �����ϸ� ��й�ȣ Ȯ��
        if (it->password == password) {
            // ��й�ȣ�� ��ġ�ϸ� �α��� ����
            return true;
        }
        else {
            // ��й�ȣ�� ��ġ���� ������ �α��� ����
            return false;
        }
    }
    else {
        // ���̵� �������� ������ �α��� ����
        return false;
    }
}