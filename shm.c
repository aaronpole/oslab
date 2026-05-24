#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key,1024, 0666|IPC_CREAT);
    char *shared_mem;

    shared_mem = (char*)shmat(shmid,NULL,0);

    if (fork() == 0){
        sleep(1);
        printf("Child reads shared memory: %s\n", shared_mem);
        shmdt(shared_mem);
    } else{
        strcpy(shared_mem, "Hello from parent process!");
        printf("Parent writes message\n");
        wait(NULL);
        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}