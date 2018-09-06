#include "my.h"

Msg m;
Msg_stoc msg_stoc;

static int msgid_ctos;
static int msgid_stoc;

void showmenu()
{
	puts("-------CHAT----------");
	puts("|  1:发送  2:接收   |");
	puts("|      3:退出       |");
	puts("--------------------");
}

void show()
{
	puts("-------CHAT----------");
	puts("|  1:注册  2:登录   |");
	puts("|      0:退出       |");
	puts("--------------------");
}

void send1()
{
	printf("%s","send");
	char buf[16] = {'\0'};
	char str[200] = {'\0'};
	struct sockaddr_in dui,zj;
	int n;
	short x;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(-1);

	}
	zj.sin_family = AF_INET;
	zj.sin_port = htons(5555);
	zj.sin_addr.s_addr = htonl(INADDR_ANY);
	n = bind(sockfd,(struct sockaddr *)&zj,sizeof(zj));
	if(n < 0)
	{
		close(sockfd);
		perror("bind");
		exit(-1);

	}
	//puts("请输入对方号码 端口 IP ");
	//scanf("%hd%s",&x,buf);
	getchar();
	dui.sin_addr.s_addr = inet_addr("10.10.3.129");
	dui.sin_port = htons(8888);
	dui.sin_family = AF_INET;
	puts("请输入想要发送的内容：");
	//gets(str);
	fgets(str,200,stdin);
	
	n = sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&dui,sizeof(dui));
	if(n <= 0)
	{
		close(sockfd);
		perror("sendto");
		exit(-1);

	}
	close(sockfd);
	return;
	
}
#if 1 
void asend(int sockfd,struct sockaddr_in dui)
{
	char buf[200] = {'\0'};
	int n;
	puts("请输入要回复的内容：");
	fgets(buf,200,stdin);
	//gets(buf);
	n = sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&dui,sizeof(dui));
	if(n <= 0)
	{
		perror("sendto");
		close(sockfd);
		exit(-1);

	}
	close(sockfd);
	return ;
}

void choose1(char ch ,int sockfd,struct sockaddr_in dui)
{
	switch(ch)
	{
	case 'a':
		asend(sockfd,dui);
		break;
	case 'n':
		break;
	default:
		puts("input error!");
		break;

	}
}
#endif
void recv1()
{
	struct sockaddr_in dui,zj;
	socklen_t len = sizeof(dui);
	int n;
	char buf[200] = {'\0'};
	char ch;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(-1);

	}
	zj.sin_family = AF_INET;
	zj.sin_port = htons(5555);
	zj.sin_addr.s_addr = htonl(INADDR_ANY);
	n = bind(sockfd,(struct sockaddr *)&zj,sizeof(zj));
	if(n < 0)
	{
		close(sockfd);
		perror("bind");
		exit(-1);

	}
	n = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&dui,&len);
	if(n <= 0)
	{
		close(sockfd);
		perror("recvfrom");
		exit(-1);
	}
	puts(buf);
	puts("是否要回复： 回复-》a,不回复-》n");
	ch = getchar();
	getchar();
	choose1(ch,sockfd,dui);
}

void choose(int ch)
{
	printf("%d",ch);
	switch(ch)
	{
	case 1:
		m.type = 5;
		msgsnd(msgid_ctos,&m,sizeof(m)-sizeof(m.type),0);
		send1();
		break;
	case 2:
		recv1();
		break;
	case 3:
		exit(0);
		break;
	default:
		puts("input error!");
		break;

	}
}

void regis()
{
	//getchar();
	printf("请输入姓名：");
	scanf("%s",m.name);
	
	printf("请输入密码：");
	scanf("%s",m.passwd);
	m.type=1;
}

void login(void)
{
	//getchar();
	printf("请输入用户名：");
	scanf("%s",&m.name);

	printf("请输入密码：");
	scanf("%s",&m.passwd);
	m.type=3;

}
/*
void msg_rcv(int type)
{
	if(-1==msgrcv(msgid_stoc,&msg_stoc,sizeof(msg_stoc),type,0))
	{
		perror("msgrcv");
		_exit(-1);
	}
	show_msg(msg_stoc.m_str,3);
}*/

int main(int argc ,char *argv[])
{
	msgid_ctos=get_ctos_msg();
	msgid_stoc=get_stoc_msg();
	
	int temptype;
	
	while(1)
	{
		show();
		int a = 0;
		scanf("%d",&a);
		getchar();
		switch(a)
		{
				case 0:return 0;
				case 1:regis();temptype=2;break;	//注册
				case 2:login();temptype=4;break;   //登录
		}
		
		int ret;
		long type=0;
		
		
		printf("name:%s,passwd:%s\n", m.name,m.passwd);
		msgsnd(msgid_ctos,&m,sizeof(m)-sizeof(m.type),0);

		sleep(2);
		msgrcv(msgid_stoc,&msg_stoc,sizeof(msg_stoc),temptype,0);
		//msg_rcv(temptype);
		
		if(0 == strcmp(msg_stoc.check,"yes"))	
		{
			printf("%s",msg_stoc.info);
			break;
		}
	}
	
	while(1)
	{
		showmenu();
		int ch;
		puts("请输入功能");
		scanf("%d",&ch);
		getchar();
		printf("%d",ch);
		choose(ch);
	}
	return ;
}
