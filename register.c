#include"my.h"

Msg per;
Msg_stoc msg_stoc;

static int msgid_ctos;
static int msgid_stoc;

void open_cli()
{
	MYSQL conn;
	int res;
	//MYSQL_RES * result;
	//MYSQL_ROW row;
	mysql_init(&conn);

	//第三、四和五个参数，需要自己修改一下
	if (mysql_real_connect(&conn, "localhost", "root", "p@s#0fSPV", "pvault", 0, NULL, 0)) {
		printf("coneect mysql successful\n");
		char insert_query[80];			
		//insert
		memset(insert_query, 0, sizeof(insert_query));
		strcat(insert_query, "insert into user(name,password) values('");
		strcat(insert_query, per.name);
		strcat(insert_query, "','");
		strcat(insert_query, per.passwd);
		strcat(insert_query, "')");
		printf("SQL语句: %s\n", insert_query);
		res = mysql_query(&conn, insert_query);
		if (!res) {
			printf("insert %lu rows\n", (unsigned long)mysql_affected_rows(&conn));
			sprintf(msg_stoc.check,"%s","no");
		}
		else {
			printf("insert error\n");
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
		//per.type = 1;	
		msgrcv(msgid_ctos,&per,sizeof(per)-sizeof(type),1,0);
		printf("name:%s,passwd:%s\n", per.name,per.passwd);
		sleep(1);	
		open_cli();
		//Msg m;
		msg_stoc.type = 2;
		sprintf(msg_stoc.check,"%s","no");
		printf("check:%s", msg_stoc.check);	
		msgsnd(msgid_stoc,&msg_stoc,sizeof(msg_stoc)-sizeof(type),0);	
	}
}