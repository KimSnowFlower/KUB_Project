/*
MySQL for C / API �ڷ���
- MySQL Database�� ������ �����ϴ� ����
- MySQL_RES SELECT : ����� ��ȯ�ϴ� ������ ����� ��Ÿ���� ��������
- MySQL_ROW MYSQL_RES : �ϳ��� ��� �����Ҹ� ������ �� �� �� �ڷ���
- MySQL_FIELD �ʵ��� �̸��� �ʵ��� ���� �� �ʵ忡 ���� ������ �����ϴ� ��������

���α׷���
MYSQL *mysql_init(MYSQL *mysql);
-> mysql�� ����ü�� ȣ���ϴ� ��.
-> ���� ó������ �پ�� ��

���� �� ����
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigend long client_flag)
-> mysql : ���� mysql ����ü�� �ּ� address
-> host : ȣ��Ʈ �̸��̳� ip Address / NULL �̰ų� "localhost"�� ���� ȣ��Ʈ�� ����� ������ ����
-> user : user ID / ���� NULL�̶�� unix�� ���� �α��� �̸�
-> passwd - user PASSWD
-> port : 0 �ƴϸ� TCP/IP ���� ��Ʈ ��ȣ
-> unix_socket : NULL �ƴϸ� ���ڿ��� ���� �Ǵ� ����ߴ� Named PIPE�� ����
-> client_flag : ��ü�� 0
mysql ������ connect ��

void mysql_close(MYSQL *sock);
-> mysql ������ disconnect ��

���� �� db ���� �Լ�
int mysql_select_db(MYSQL *mysql, const char *db);
-> mysql : mysql ����ü�� �ּ� address
-> db : �����ͺ��̽���
-> ������ ���̽��� ���� (��ȯ : 0 �ƴ� ����)

int myysql_query(MYSQL *mysql, const char *q);
-> mysql : mysql ����ü�� �ּ� address
-> q : ���� - ���ǹ�
-> ������ ���� ������ ������ �Ǵ��� ��ȯ�մϴ�. (��ȯ : 0�� �ƴ� ���� ����)

MYSQL_RES *mysql_store_result(MYSQL *mysql);
-> mysql_query()�� ������ ���� Result Set�� ����

MYSQL_ROW mysql_fetch_row(MYSQL_REST *result);
-> Result Set���� �ϳ��� row�� �迭�� �����ɴϴ�

void mysql_free_result(MYSQL_RES *result);
-> Result Set�� ����
-> ���� �۾��� ��� ���� Result Set�� �ݵ�� free�� ��������� ��

���� �޽��� �Լ�
unsigned int mysql_errno(MYSQL *mysql);
-> mysql ���� Number�� ����

const char* mysql_error(MYSQL *mysql);
-> mysql ���� �޽����� �����մϴ�.

error ex) printf("%d error:%s\n", mysql_errno*(&conn), mysql_error(&conn));
*/
