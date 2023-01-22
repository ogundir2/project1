/*********  sort-A-in.c  *********************/



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
    char mtext[256];
	int	numbers[16];
};

int main()
{
	struct msgform msg;
	int msgid, pid, *pint, n;
    n = 16;

	msgid = msgget(MSGKEY, 0777);

	pid = getpid();
	pint = (int *) msg.mtext;
		*pint = pid;	/* copy pid into message text */
	msg.mtype = 1;

    for (int i=0; i<n; i++)
    {
        scanf("%d", &msg.numbers[i]);
    }

	
    for (int i=0; i<n; i++)
    {
        printf("%d ", msg.numbers[i]);
    }

    int num, next;

    for (int i=0; i<n; i++)
    {
        for (int j=0, j < n-i-1; j++)
        {
            num = msg.numbers[j];
            next = msg.numbers[j+1]
            if (num > next)
            {
                &msg.numbers[j] = next;
                &msg.numbers[j+1] = num;
            }
        }
    }

	msgsnd(msgid, &msg, sizeof(int)*16, 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 256, pid, 0) == -1) {
		printf("\nclient: msg queue has been removed.\n");
		exit(1);
	}
	printf("\nclient: receive from pid %d\n", *pint);
}
