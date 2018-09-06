#ifndef CHAT_H_
#define CHAT_H_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<strings.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <termios.h>
#include<mysql.h>

#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<strings.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>


typedef struct {	//消息队列结构体
		long type;
		char name[20];
		char passwd[20];
		char check[8];
		char info[20];
}Msg;

typedef struct//服务器到客户端消息结构体
{
	int type;//消息类型
	char info[255];//提示信息
	char check[10];
}Msg_stoc;

int get_msg(key_t key)
{
	int msgid=msgget(key,0644|IPC_CREAT);
	if(-1==msgid)
	{
		perror("msgget");
		exit(0);
	}
	return msgid;
}
int get_ctos_msg(void)
{
	key_t key=ftok(".",'c');
	return get_msg(key);

}
int get_stoc_msg(void)
{
	key_t key=ftok(".",'c');
	return get_msg(key);
}


#endif
