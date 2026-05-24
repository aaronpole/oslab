#include <stdio.h>
#include <pthread.h>

typedef struct {
    int a;
    int b;
    int sum;
} data_t;

void* add(void* arg){
    data_t* data = (data_t*)arg;
    data->sum = data->a + data->b;
    return NULL;
}

int main(){
    pthread_t t1, t2;
    data_t data1 = {5, 10, 0};
    data_t data2 = {20, 30, 0};

    pthread_create(&t1, NULL,add, &data1);
    pthread_create(&t2, NULL, add, &data2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum from thread 1: %d\n", data1.sum);
    printf("Sum from thread 2: %d\n", data2.sum);

    if (data1.sum > data2.sum){
        printf("Thread 1 has the greater sum.\n");
    } else if (data1.sum < data2.sum){
        printf("Thread 2 has the greater sum.\n");
    } else{
        printf("Both threads have the same sum.\n");
    }
    return 0;
}