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

    int index = 0;
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
            frames[index] = page;
            index = (index + 1) % frameCount;
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