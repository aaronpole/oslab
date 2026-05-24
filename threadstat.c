#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

double mean, median, stddev;
int n, arr[100];

void *mean_thread(void *arg){
    double sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    mean = (double)sum / n;
    return NULL;
}

void *median_thread(void *arg){
    int temp;
    for (int i =0; i < n-1; i++){
        for (int j = 0; j < n- i - 1; j++){
            if (arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    if (n % 2 == 0){
        median = (arr[n/2 - 1] + arr[n/2]) / 2.0;
    } else{
        median = arr[n/2];
    }
    return NULL;
}


void *stddev_thread(void *arg){
    double sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += pow(arr[i]-mean, 2);
    }
    stddev = sqrt(sum / n);
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    n = argc-1;

    for (int i = 0; i < n; i++){
        arr[i] = atoi(argv[i+1]);
    }

    pthread_t t1,t2,t3;

    pthread_create(&t1, NULL, mean_thread, NULL);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, median_thread, NULL);
    pthread_create(&t3, NULL, stddev_thread, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Mean: %.2lf\n", mean);
    printf("Median: %.2lf\n", median);
    printf("Standard Deviation: %.2lf\n", stddev);
    return 0;
}