#include <iostream>
#include <winsock2.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

const std::string host = "localhost";
const std::string user = "root";
const std::string pw = "~Vudghk201";
const std::string db = "bbs";

int main(int argc, char* argv[])
{
    MYSQL* connection = NULL;
    MYSQL conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;

    if (mysql_init(&conn) == NULL)
    {
        std::cout << "mysql_init() error!" << std::endl;
        return 1;
    }

    connection = mysql_real_connect(&conn, host.c_str(), user.c_str(), pw.c_str(), db.c_str(), 3306, nullptr, 0);
    if (connection == NULL)    // 연결 에러 처리
    {
        std::cout << mysql_errno(&conn) << " 에러 : " << mysql_error(&conn) << std::endl;
        return 1;
    }
    else
    {
        std::cout << "연결 성공" << std::endl;    // 연결 성공 메시지 출력

        if (mysql_select_db(&conn, db.c_str()))    // 데이터베이스 선택
        {
            std::cout << mysql_errno(&conn) << " 에러 : " << mysql_error(&conn) << std::endl;
            return 1;
        }

        const char* query = "select * from korea";
        int state = 0;

        state = mysql_query(connection, query);
        if (state == 0)
        {
            sql_result = mysql_store_result(connection);            // Result Set에 저장
            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)    // Result Set에서 1개씩 배열에 가져옴
            {
                std::cout << sql_row[0] << " " << sql_row[1] << " " << sql_row[2] << " " << sql_row[3] << std::endl;    // 저장된 배열을 출력
            }
            mysql_free_result(sql_result);        // Result Set 해제한다
        }

        mysql_close(connection);        // db서버 종료
    }

    return 0;
}
