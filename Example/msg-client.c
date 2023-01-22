/*********  msg-client.c  *********************/



#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 	1101	

struct msgform {
	long	mtype;
	char	mtext[256];
};

int main()
{
	struct msgform msg;
	int msgid, pid, *pint;

	msgid = msgget(MSGKEY, 0777);

	pid = getpid();
	pint = (int *) msg.mtext;
		*pint = pid;	/* copy pid into message text */
	msg.mtype = 1;

	msgsnd(msgid, &msg, sizeof(int), 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 256, pid, 0) == -1) {
		printf("client: msg queue has been removed.\n");
		exit(1);
	}
	printf("client: receive from pid %d\n", *pint);
}
