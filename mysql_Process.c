
#include "mysql_Process.h"


// void main(){
//     MYSQL *conn;
//     MYSQL_RES *res;
//     MYSQL_ROW row;

//     conn = mysql_init(NULL);
//     if (conn == NULL) {
//         fprintf(stderr, "mysql_init() failed\n");
//         exit(-1);
//     }

//     if (mysql_real_connect(conn, "162.14.66.9", "root", "08290829", "Chat_DB", 0, NULL, 0) == NULL) {
//         fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
//         mysql_close(conn);
//         exit(-1);
//     }

//     if (mysql_query(conn, "SELECT * FROM user")) {
//         fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
//         mysql_close(conn);
//         exit(-1);
//     }
    

//     res = mysql_use_result(conn);
//     if (res == NULL) {
//         fprintf(stderr, "mysql_use_result() failed\n");
//         mysql_close(conn);
//         exit(-1);
//     }

//     while ((row = mysql_fetch_row(res)) != NULL) {
//         printf("%s\t%s\t%s\n", row[0], row[1], row[2]); // 根据表结构修改打印方式
//     }

//     mysql_free_result(res);
//     mysql_close(conn);

// }
