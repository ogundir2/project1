#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>

#define N 4
#define NUM_PROCESSES 8

void sort_columns(int arr[N][N], int col) {
    int temp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j][col] > arr[j + 1][col]) {
                temp = arr[j][col];
                arr[j][col] = arr[j + 1][col];
                arr[j + 1][col] = temp;
            }
        }
    }
}

void sort_odd_rows(int arr[N][N], int row) {
    int temp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[row][j] > arr[row][j + 1]) {
                temp = arr[row][j];
                arr[row][j] = arr[row][j + 1];
                arr[row][j + 1] = temp;
            }
        }
    }
}

void sort_even_rows(int arr[N][N], int row) {
    int temp;
    for (int i = N - 1; i > 0; i--) {
        for (int j = N - 1; j > N - i - 1; j--) {
            if (arr[row][j] < arr[row][j - 1]) {
                temp = arr[row][j];
                arr[row][j] = arr[row][j - 1];
                arr[row][j - 1] = temp;
            }
        }
    }
}


int main(void) {
    int arr[N][N];
    int num_phases = log2(N) + 1;
    int fd[NUM_PROCESSES][2];
    pid_t pid;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("Original Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int phase = 0; phase < num_phases; phase++) {
        int count = 0;
        int row_sort_type = phase % 2;
        for (int i = 0; i < N; i++) {
            if (row_sort_type == 0) {
                pipe(fd[count]);
                pid = fork();
                if (pid == 0) {
                    close(fd[count][0]);
                    sort_columns(arr, i);
                    write(fd[count][1], &arr, sizeof(arr));
                    exit(0);
                }
                count++;
            } else {
                if (i % 2 == 1) {
                    pipe(fd[count]);
                    pid = fork();
                    if (pid == 0) {
                        close(fd[count][0]);
                        sort_odd_rows(arr, i);
                        write(fd[count][1], &arr, sizeof(arr));
                        exit(0);
                    }
                    count++;
                } else {
                    pipe(fd[count]);
                    pid = fork();
                    if (pid == 0) {
                        close(fd[count][0]);
                        sort_even_rows(arr, i);
                        write(fd[count][1], &arr, sizeof(arr));
                        exit(0);
                    }
                    count++;
                }
            }
        }

        for (int i = 0; i < count; i++) {
            close(fd[i][1]);
            read(fd[i][0], &arr, sizeof(arr));
            wait(NULL);
        }
    }

    printf("Sorted Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
