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

void scan(int requests[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;

    sortRequests(requests, numRequests);

    int direction = 1;

    printf("Sequence of head movement:\n");

    int i;
    // Find the index where the current head position is present in the sorted requests
    for (i = 0; i < numRequests; ++i) {
        if (requests[i] >= currentHeadPosition) {
            break;
        }
    }

    // Move towards higher track numbers
    for (; i < numRequests && i >= 0; i += direction) {
        int distance = abs(requests[i] - currentHeadPosition);
        totalHeadMovement += distance;

        printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, requests[i], distance);

        currentHeadPosition = requests[i];
    }

    direction = -direction; 
    for (i -= direction; i < numRequests && i >= 0; i += direction) {
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

    scan(requests, numRequests, initialPosition);

    return 0;
}