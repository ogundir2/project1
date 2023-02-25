/*********  sort-A-in.c  *********************/



#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 	1101	
#define ROWS 4
#define COLS 4

struct msgform {
	long	mtype;
	int	numbers[ROWS][COLS];
};

int main()
{
	struct msgform msg;
	int msgid, pid, *pint, n;
    	n = 16;

	msgid = msgget(MSGKEY, 0777);

	pid = getpid();

	msg.mtype = 1;

    // int arr[ROWS][COLS];
    int i, j;

    // Read integers into a 2D array
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (scanf("%d", &msg.numbers[i][j]) != 1) {
                printf("\nCould not read integer.\n");
                return 1;
            }
        }
    }

    // Print the original array
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d", msg.numbers[i][j]);
        }
    }

    // int num, next;

    // for (int i=0; i<n; i++)
    // {
    //     for (int j=0; j<n-i-1; j++)
    //     {
    //         num = msg.numbers[j];
    //         next = msg.numbers[j+1];
    //         if (num > next)
    //         {
    //             msg.numbers[j] = next;
    //             msg.numbers[j+1] = num;
    //         }
    //     }
    // }
	// printf("\n");

	// msgsnd(msgid, &msg, sizeof(int)*16, 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 64, 1, 0) == -1) {
		printf("\nclient: msg queue has been removed.\n");
		exit(1);
	}
}
