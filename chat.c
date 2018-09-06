#include"my.h"

static int msgid_ctos;
static int msgid_stoc;
Msg per;

int main(int argc,char *argv[])
{
	
	msgid_ctos = get_ctos_msg();
	msgid_stoc = get_stoc_msg();
	msgrcv(msgid_ctos,&per,sizeof(per)-8,5,0);
	if(per.type != 5)
		return 0;
		

	char cmd,tmp_cmd;
	char ip[16]="\0";
	short port;
	char text[1000]="\0";

	typedef struct sockaddr*  SA;
	struct sockaddr_in selfaddr,saddr;
	socklen_t len = sizeof(saddr);

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		perror("socket");
		exit(-1);
	}

	selfaddr.sin_family  = AF_INET;
	selfaddr.sin_port = htons(8888);
	selfaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(sockfd,(SA)&selfaddr,sizeof(selfaddr));
	if(ret<0)
	{
		close(sockfd);
		perror("bind");
		exit(-1);
	}

	for(;;)
	{
		puts("please input s(send message) r(recv message) a(replay  message) q(quit)");
		scanf("%c",&cmd);
		getchar();//取 回车

		if(cmd=='s')
		{
			puts("please input:ip port text");
			scanf("%s%hd%s",ip,&port,text);// %hd short类型的格式控制符
			getchar();//取回车
			
			bzero(&saddr,sizeof(saddr));
			saddr.sin_family  = AF_INET;
			saddr.sin_port = htons(port);
			saddr.sin_addr.s_addr = inet_addr(ip);
			sendto(sockfd,text,strlen(text)+1,0,(SA)&saddr,sizeof(saddr));
		}
		else if(cmd=='r')
		{
			ret = recvfrom(sockfd,text,sizeof(text),MSG_DONTWAIT,(SA)&saddr,&len);
			if(ret<0)
			{
				tmp_cmd = cmd;
				puts("have not message!");
				continue;
			}

			inet_ntop(AF_INET,&saddr.sin_addr.s_addr,ip,sizeof(ip));
			printf("ip:%s port:%d  say:%s\n",ip,ntohs(saddr.sin_port),text);
		}
		else if(cmd=='a'&&tmp_cmd=='r')//tmp_cmd 记录上一次操作的命令
		{
			puts("please input text");
			//gets(text);
			fgets(text,1000,stdin);
			
			sendto(sockfd,text,strlen(text)+1,0,(SA)&saddr,sizeof(saddr));
		}
		else if(cmd=='q')
		{
			close(sockfd);
			exit(-1);
		}
		else 
		{
			puts("input cmd error");

		}

		tmp_cmd = cmd;	
	}

	close(sockfd);
	return 0;	
}