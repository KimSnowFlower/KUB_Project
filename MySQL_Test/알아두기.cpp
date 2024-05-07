/*
MySQL for C / API 자료형
- MySQL Database와 연결을 관리하는 존재
- MySQL_RES SELECT : 결과를 반환하는 쿼리의 결과를 나타내는 데이터형
- MySQL_ROW MYSQL_RES : 하나의 기록 보관소를 가져갈 때 올 떄 자료형
- MySQL_FIELD 필드의 이름과 필드의 유형 등 필드에 관한 정보를 저장하는 데이터형

프로그래밍
MYSQL *mysql_init(MYSQL *mysql);
-> mysql을 구조체를 호출하는 것.
-> 먼저 처음으로 뛰어야 함

접속 및 해제
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigend long client_flag)
-> mysql : 현재 mysql 구조체의 주소 address
-> host : 호스트 이름이나 ip Address / NULL 이거나 "localhost"는 로컬 호스트로 연결된 것으로 본다
-> user : user ID / 만약 NULL이라면 unix는 현재 로그인 이름
-> passwd - user PASSWD
-> port : 0 아니면 TCP/IP 연결 포트 번호
-> unix_socket : NULL 아니면 문자열을 소켓 또는 사용했던 Named PIPE를 지정
-> client_flag : 대체로 0
mysql 서버와 connect 함

void mysql_close(MYSQL *sock);
-> mysql 서버와 disconnect 함

접속 후 db 관리 함수
int mysql_select_db(MYSQL *mysql, const char *db);
-> mysql : mysql 구조체의 주소 address
-> db : 데이터베이스명
-> 데이터 베이스를 선택 (반환 : 0 아닌 에러)

int myysql_query(MYSQL *mysql, const char *q);
-> mysql : mysql 구조체의 주소 address
-> q : 쿼리 - 질의문
-> 쿼리가 실행 가능한 문인지 판단후 반환합니다. (반환 : 0이 아닌 값은 에러)

MYSQL_RES *mysql_store_result(MYSQL *mysql);
-> mysql_query()로 실행한 쿼리 Result Set을 저장

MYSQL_ROW mysql_fetch_row(MYSQL_REST *result);
-> Result Set에서 하나의 row를 배열로 가져옵니다

void mysql_free_result(MYSQL_RES *result);
-> Result Set을 제거
-> 쿼리 작업을 모두 끝낸 Result Set을 반드시 free로 해제해줘야 함

에러 메시지 함수
unsigned int mysql_errno(MYSQL *mysql);
-> mysql 에러 Number를 리턴

const char* mysql_error(MYSQL *mysql);
-> mysql 에러 메시지를 리턴합니다.

error ex) printf("%d error:%s\n", mysql_errno*(&conn), mysql_error(&conn));
*/
