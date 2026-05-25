#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, faults = 0;
    int time[10], counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        counter++;

        // Check if page already exists
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter;
                break;
            }
        }

        // Page Fault
        if (!found) {
            int pos = 0;

            // Find Least Recently Used page
            for (int j = 1; j < f; j++) {
                if (time[j] < time[pos])
                    pos = j;
            }

            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }

        // Display frames
        printf("%d\t", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}