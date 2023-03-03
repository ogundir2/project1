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
	int	numbers[16];
};

void bubblesort_ascending(int arr[4]) {
    int num, next;

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n-i-1; j++)
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

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n-i-1; j++)
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

    for (int i=0; i<n; i++)
    {
        scanf("%d", &msg.numbers[i]);
    }

    printf("Original Array: ");
    for (int i=0; i<n; i++)
    {
        printf("%d ", msg.numbers[i]);
    }

    int num, next;

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            num = msg.numbers[j];
            next = msg.numbers[j+1];
            if (num > next)
            {
                msg.numbers[j] = next;
                msg.numbers[j+1] = num;
            }
        }
    }
	printf("\n");

	msgsnd(msgid, &msg, sizeof(int)*16, 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 64, 1, 0) == -1) {
		printf("\nclient: msg queue has been removed.\n");
		exit(1);
	}
}
