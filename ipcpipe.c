#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(){
    int fd[2];
    pid_t pid;
    char buffer[100];
    char message[] = "Hello from the parent process!";

    if (pipe(fd) == -1){
        perror("Pipe Failed");
        return 1;
    }

    pid = fork();

    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }

    if (pid == 0){
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child process received message: %s\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], message, strlen(message)+1);
        close(fd[1]);

    }
    return 0;
}