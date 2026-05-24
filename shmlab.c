#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 500

// Function to reverse string
void reverse(char str[]) {
    int len = strlen(str);

    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {

    int shmid;
    char *shared_memory;

    char str1[100], str2[100], str3[100], str4[100];

    // User input
    printf("Enter string 1: ");
    scanf("%s", str1);

    printf("Enter string 2: ");
    scanf("%s", str2);

    printf("Enter string 3: ");
    scanf("%s", str3);

    printf("Enter string 4: ");
    scanf("%s", str4);

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);

    if (shmid < 0) {
        perror("Shared memory creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // Child Process
    else if (pid == 0) {

        shared_memory = (char *)shmat(shmid, NULL, 0);

        // Reverse second string
        reverse(str2);

        // Concatenate strings
        strcpy(shared_memory, str1);
        strcat(shared_memory, str2);
        strcat(shared_memory, str3);
        strcat(shared_memory, str4);

        shmdt(shared_memory);
        exit(0);
    }

    // Parent Process
    else {

        wait(NULL);

        shared_memory = (char *)shmat(shmid, NULL, 0);

        printf("\nConcatenated String: %s\n", shared_memory);

        shmdt(shared_memory);

        // Delete shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}