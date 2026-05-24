#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    
    pid_t pid;
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    pid = fork();
    if (pid < 0){
        perror("Fork failed");
        return 1;
    } else if (pid == 0){

        printf("Child process: %d executing exam.c\n", getpid());

        char str1[20], str2[20];
        sprintf(str1, "%d", num1);
        sprintf(str2, "%d", num2);  

        char *args[] = {"./exam", str1, str2, NULL};
        execvp(args[0], args);

        perror("Exec failed");
        return 1;
    } else{
        printf("Parent process: %d created child process %d\n", getpid(), pid);
        wait(NULL);
        printf("Child process %d finished execution\n", pid);
        return 0;
    }
}