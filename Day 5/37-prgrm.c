#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void fcfs(int requests[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;

    printf("Sequence of head movement:\n");

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

    fcfs(requests, numRequests, initialPosition);

    return 0;
}