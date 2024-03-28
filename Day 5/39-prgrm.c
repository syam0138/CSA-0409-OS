#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sortRequests(int requests[], int numRequests) {
    for (int i = 0; i < numRequests - 1; ++i) {
        for (int j = 0; j < numRequests - i - 1; ++j) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void cScan(int requests[], int numRequests, int initialPosition, int diskSize) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;

    sortRequests(requests, numRequests);

    printf("Sequence of head movement:\n");

    for (int i = 0; i < numRequests; ++i) {
        if (requests[i] >= currentHeadPosition) {
            int distance = abs(requests[i] - currentHeadPosition);
            totalHeadMovement += distance;

            printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, requests[i], distance);

            currentHeadPosition = requests[i];
        }
    }

    totalHeadMovement += currentHeadPosition;
    printf("Move to the beginning of the disk (Distance: %d)\n", currentHeadPosition);
    currentHeadPosition = 0;

    for (int i = 0; i < numRequests; ++i) {
        int distance = abs(requests[i] - currentHeadPosition);
        totalHeadMovement += distance;

        printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, requests[i], distance);

        currentHeadPosition = requests[i];
    }

    printf("\nTotal head movement: %d\n", totalHeadMovement);
}

int main() {
    int numRequests;
    int requests[MAX_REQUESTS];
    int initialPosition;
    int diskSize;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the disk requests (separated by spaces):\n");
    for (int i = 0; i < numRequests; ++i) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialPosition);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    cScan(requests, numRequests, initialPosition, diskSize);

    return 0;
}