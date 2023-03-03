/*********  sort-A-in.c  *********************/



#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 	1102	
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
    int fds[8][2];

	msgid = msgget(MSGKEY, 0777);

	// pid = getpid();

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
	printf("Original Array:\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", msg.numbers[i][j]);
        }
	printf("\n");
    }
	printf("\n");


    for (i=0; i<8; i++) {
        if (pipe(fds[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
	}
    }

    int arr[4];

    for (i=0; i<8; i++) {
        pid = fork();
        if (pid == 0) { // Child process
            if (i%2 == 0) {
                read(fds[i][0], arr, sizeof(arr));
            }
            break;
        } else if (pid > 0) {   // Parent process
            if (i%2 == 0) {
                for (j=0; j < 4; j++) {
                    write(fds[j*2][1], msg.numbers[j], sizeof(int)*4);
                }
            }
        }
    }

    int phase = 1;

    while (phase < 5) {

        if (pid == 0) {
            if (phase % 2 == 0) {   // Even phase
                bubblesort_ascending(arr);
		int ind = i/2;
		for (int m=0; m < ROWS; m++)
		{
			msg.numbers[m][ind] = arr[m];
		}
            } else {    // Odd phase
                if (i %2 == 0) {
                    bubblesort_ascending(arr);
			int ind = i/2;
			for (int m=0; m<COLS; m++) {
				msg.numbers[ind][m] = arr[m];
			}
                } else {
                    bubblesort_descending(arr);
			int ind = i/2;
			for (int m=0; m <COLS; m++) {
				msg.numbers[ind][m] = arr[m];
			}
                }
            }

            write(fds[i][1], arr, sizeof(arr));
        } else {
            read(fds[i][1], msg.numbers[j], sizeof(int)*4);
        }

        phase++;
    }

	msgsnd(msgid, &msg, sizeof(int)*16, 0);
		/* pid is used as the msg type below */
	if (msgrcv(msgid, &msg, 64, 1, 0) == -1) {
		printf("\nclient: msg queue has been removed.\n");
		exit(1);
	}
}
