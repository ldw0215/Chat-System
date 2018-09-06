#include"my.h"

Msg per;
Msg_stoc msg_stoc;

static int msgid_ctos;
static int msgid_stoc;

void login(void)
{
	MYSQL conn;
	int res;
	MYSQL_RES * result;
	MYSQL_ROW row;
	mysql_init(&conn);

	//第三、四和五个参数，需要自己修改一下
	if (mysql_real_connect(&conn, "localhost", "root", "p@s#0fSPV", "pvault", 0, NULL, 0)) {
		printf("coneect mysql successful\n");
	char select_query[64] = {0};
	snprintf(select_query,64,"select name,password from user where name='%s'",per.name);
	printf("SQL语句: %s\n", select_query);
	if (mysql_query(&conn, select_query) != 0) {
		fprintf(stderr, "查询失败\n");
		exit(1);
	}
	else {
	if ((result = mysql_store_result(&conn)) == NULL) {
			fprintf(stderr, "保存结果集失败\n");
			exit(1);
		}
		else {
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("name is %s , ", row[0]);
				printf("age is %s\n", row[1]);
				if((0 == strcmp(row[0],per.name)) && (0 == strcmp(row[1],per.passwd)))
					strcpy(per.info,"login success!");
			}
		}
	}
	
	}
}

int main()
{
	msgid_ctos = get_ctos_msg();
	msgid_stoc = get_stoc_msg();

	//int	sockfd = socket_rcv();
	while(1)
	{
		int n;
		long type;
		//per.type = 3;	
		msgrcv(msgid_ctos,&per,sizeof(per)-sizeof(type),3,0);
		//printf("name:%s,passwd:%s\n", per.name,per.passwd);
		sleep(1);	
		login();
		//Msg m;
		msg_stoc.type = 4;
		sprintf(msg_stoc.check,"%s","yes");
		printf("check:%s", per.info);	
		msgsnd(msgid_stoc,&msg_stoc,sizeof(msg_stoc)-sizeof(type),0);	
	}
}