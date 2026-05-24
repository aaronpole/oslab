#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    double a,b,c;
    double four_ac, b2, disc, result;

    printf("Enter the coefficients a, b and c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (pipe(fd) == -1){
        perror("Pipe Failed");
        return 1;
    }

    pid = fork();

    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }

    else if (pid == 0){
        close(fd[0]);
        four_ac = 4*a*c;
        write(fd[1], &four_ac, sizeof(four_ac));
        close(fd[1]);
    }

    else {
        close (fd[1]);
        b2 = b*b;
        read(fd[0], &four_ac, sizeof(four_ac));
        close(fd[0]);
        disc = b2 - four_ac;
        if (disc < 0){
            printf("The equation has no real roots.\n");
        }
        else {
            result = sqrt(disc);
            printf("Value of b^2 - 4ac is: %lf\n", result);
        }
    }
    return 0;
}