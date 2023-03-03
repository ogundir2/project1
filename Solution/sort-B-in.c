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

void bubblesort_ascending(int arr[4]) {
    int num, next;

    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<ROWS-i-1; j++)
        {
            num = arr[j];
            next = arr[j+1];
            if (num > next)
            {
                arr[j] = next;
                arr[j+1] = num;
            }
        }
    }
}

void bubblesort_descending(int arr[4]) {
    int num, next;

    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<ROWS-i-1; j++)
        {
            num = arr[j];
            next = arr[j+1];
            if (num < next)
            {
                arr[j] = next;
                arr[j+1] = num;
            }
        }
    }
}

int main()
{
	struct msgform msg;
	int msgid, pid, *pint, n;
    	n = 16;

	msgid = msgget(MSGKEY, 0777);

	pid = getpid();

	msg.mtype = 1;

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
            printf("%d ", msg.numbers[i][j]);
        }
	printf("\n");
    }


	msgsnd(msgid, &msg, sizeof(int)*16, 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 64, 1, 0) == -1) {
		printf("\nclient: msg queue has been removed.\n");
		exit(1);
	}
}
