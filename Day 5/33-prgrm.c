#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main() {
    int frames[MAX_FRAMES];
    int pageSequence[MAX_PAGES];
    int pageFaults = 0;
    int frameCount, pageRequestCount;

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter the number of page requests: ");
    scanf("%d", &pageRequestCount);

    printf("Enter the page request sequence:\n");
    for (int i = 0; i < pageRequestCount; ++i) {
        scanf("%d", &pageSequence[i]);
    }

    for (int i = 0; i < frameCount; ++i) {
        frames[i] = -1;
    }

    for (int i = 0; i < pageRequestCount; ++i) {
        int page = pageSequence[i];
        int pageFound = 0;

        for (int j = 0; j < frameCount; ++j) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            int futureDelay[MAX_FRAMES] = {0};
            int found = 0;

            for (int j = 0; j < frameCount; ++j) {
                for (int k = i + 1; k < pageRequestCount; ++k) {
                    if (pageSequence[k] == frames[j]) {
                        futureDelay[j] = k - i;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    futureDelay[j] = pageRequestCount + 1; 
                }
                found = 0;
            }

            int maxIndex = 0;
            for (int j = 1; j < frameCount; ++j) {
                if (futureDelay[j] > futureDelay[maxIndex]) {
                    maxIndex = j;
                }
            }

            frames[maxIndex] = page;
            pageFaults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frameCount; ++j) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0; 
}