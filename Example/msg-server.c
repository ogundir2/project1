/*************  msg-server.c  ****************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define MSGKEY	1101

struct msgform {
	long	mtype;
	char	mtext[256];
} msg;

int	msgid;

int main()
{
	int i, pid, *pint;
	extern void cleanup();

	/* in case any signal arrives (such as ^C) */
	/* do cleanup() automatically */
	for (i=0; i<15; i++)
		signal(i, cleanup);

	msgid = msgget(MSGKEY, 0777|IPC_CREAT);

	msgrcv(msgid, &msg, 256, 1, 0);
	pint = (int *) msg.mtext;
	pid = *pint;
	printf("server: receive from pid %d\n", pid);
	msg.mtype = pid;
	*pint = getpid();
	msgsnd(msgid, &msg, sizeof(int), 0);
	sleep(1);
	cleanup();
}

void cleanup()
{
	msgctl(msgid, IPC_RMID, 0);
	printf("\nCleaned up.\n");
	exit(0);
}
