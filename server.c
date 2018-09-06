#include"my.h"

static pid_t sub_pid[9];

static int msgid_ctos;
static int msgid_stoc;

void sigint(int signum)
{
	int i;
	for(i=0;i<3;i++)
	{
		kill(sub_pid[i],SIGKILL);
	}
	
}

int main(int argc,char*argv[])
{
	signal(SIGINT,sigint);

	msgid_ctos=get_ctos_msg();
	msgid_stoc=get_stoc_msg();
	
	sub_pid[0]=vfork();
	if(0==sub_pid[0])
	{
		execl("register","register",NULL);
	}


	sub_pid[1]=vfork();
	if(0==sub_pid[1])
	{
		execl("login","login",NULL);
	}


	sub_pid[2]=vfork();
	if(0==sub_pid[2])
	{
		execl("chat","chat",NULL);
	}

	wait(NULL);
	return 0;

}
