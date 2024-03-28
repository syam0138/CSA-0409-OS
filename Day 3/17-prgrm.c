#include<stdio.h>

// Number of processes
#define P 5

// Number of resources
#define R 3

// Function to find the need of each process
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

// Function to check if the current state is safe
int isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    int finish[P] = {0};

    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    finish[p] = 1;
                    processes[count++] = p;
                    found = 1;
                }
            }
        }
        if (found == 0)
            return 0; // Unsafe state
    }
    return 1; // Safe state
}

// Function to perform the Banker's algorithm
void bankersAlgorithm(int processes[], int avail[], int max[][R], int allot[][R]) {
    if (isSafe(processes, avail, max, allot)) {
        printf("\nSafe state, Safe sequence is: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", processes[i]);
        }
        printf("\n");
    } else {
        printf("\nUnsafe state\n");
    }
}

int main() {
    // Available instances of resources
    int avail[R] = {3, 3, 2};

    // Maximum R that can be allocated to processes
    int max[P][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to processes
    int allot[P][R] = {{0, 1, 0},
                       {2, 0, 0},
                       {3, 0, 2},
                       {2, 1, 1},
                       {0, 0, 2}};

    int processes[P];

    bankersAlgorithm(processes, avail, max, allot);

    return 0;
}