#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    int min;
    int max;
    bool *data;
    int size;
} sieve;

void *thread_function(void *thread_data){
    sieve *c_sieve = (sieve*) thread_data;

    int min = c_sieve->min;
    int max = c_sieve->max;
    int MAX = c_sieve->size;

    for(int i = min; i <= max; i++){
        if(c_sieve->data[i]) {
            for (int j = 2; i * j <= MAX; j++) {
                c_sieve->data[i * j] = false;
            }
        }
    }

    return NULL;
}

int main (int argc, char * argv[]) {
    int N = atoi(argv[1]);
    int MAX;
    if(argc <= 2){
        MAX = INT_MAX;
    } else {
        MAX = atoi(argv[2]);
    }

    bool* data = (bool*) malloc((MAX + 1) * sizeof(bool));
    if(data == NULL){
        perror("Allocate error");
        exit(1);
    }

    for(int i = 1; i <= MAX; i++){
        data[i] = true;
    }

    pthread_t *threads = (pthread_t*) malloc(N * sizeof(pthread_t));
    if(threads == NULL){
        perror("Allocate error");
        exit(2);
    }

    sieve *thread_data = (sieve*) malloc(N * sizeof(sieve));
    if(thread_data == NULL){
        perror("Allocate error");
        exit(3);
    }


    int max_check_number = 1;
    while(max_check_number * max_check_number <= MAX){
        max_check_number++;
    }
    max_check_number--;

    int for_one_thread = max_check_number / N;

    for(int i = 0; i < N; i++){
        thread_data[i].min = for_one_thread * i + 1;
        if(i == 0){
            thread_data[i].min = 2;
        }
        thread_data[i].max = for_one_thread * (i + 1);
        if((i == N - 1) && (thread_data[i].max != MAX)) {
            thread_data[i].max = MAX;
        }
        thread_data[i].size = MAX;
        thread_data[i].data = data;

        int res = pthread_create(&(threads[i]), NULL, thread_function, &thread_data[i]);
        if(res != 0){
            perror("Create error");
            exit(4);
        }
    }

    for(int i = 0; i < N; i++){
        int res = pthread_join(threads[i], NULL);
        if(res != 0){
            perror("Join error");
            exit(5);
        }
    }

    for(int i = 1; i <= MAX; i++){
        if(data[i]){
            printf("%d ", i);
        }
    }

    free(data);
    free(thread_data);
    free(threads);
    return 0;
}
