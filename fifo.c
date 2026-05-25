#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f;
    int i, j;
    int next = 0;      // FIFO pointer
    int found;
    int faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++)
        frames[i] = -1;

    // Table header
    printf("\nPage\t");
    for (i = 0; i < f; i++)
        printf("Frame%d\t", i + 1);
    printf("Status\n");

    // FIFO Simulation
    for (i = 0; i < n; i++) {
        found = 0;

        // Check hit
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[next] = pages[i];
            next = (next + 1) % f;
            faults++;
        }

        // Print row
        printf("%d\t", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frames[j]);
        }

        if (found)
            printf("Hit\n");
        else
            printf("Fault\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
