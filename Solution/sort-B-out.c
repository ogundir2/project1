/*************  sort-B-out.c  ****************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define MSGKEY	1102
#define ROWS 4
#define COLS 4

struct msgform {
	long	mtype;
    int numbers[ROWS][COLS];
} msg;

int	msgid;

int main()
{
	int i, j, pid, n;
	extern void cleanup();

	/* in case any signal arrives (such as ^C) */
	/* do cleanup() automatically */
	for (i=0; i<15; i++)
		signal(i, cleanup);

	msgid = msgget(MSGKEY, 0777|IPC_CREAT);

	msgrcv(msgid, &msg, 64, 1, 0);
	printf("server: receive from pid %d\n", pid);


	// Print the sorted array
    printf("Sorted Array:\n ");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", msg.numbers[i][j]);
        }
	printf("\n");
    }


	msgsnd(msgid, &msg, sizeof(int)*16, 0);
	sleep(1);
	cleanup();
}

void cleanup()
{
	msgctl(msgid, IPC_RMID, 0);
	printf("\nCleaned up.\n");
	exit(0);
}
