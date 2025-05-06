//A hotel restaurant has a total of 6 tables. Five of these are 2-person tables, and one is a 4-person table. Groups of either 2 or 4 people arrive randomly. 
//A group of 2 can only use a 2-person table, and a group of 4 can only use the 4-person table (they can't split across smaller tables). Once a group is done dining, 
//their table becomes available. Use semaphores to manage access to the tables such that there are no race conditions or conflicting allocations, and groups wait 
//if no suitable table is free.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TWO_TABLES 5
#define FOUR_TABLES 1
#define GROUP_COUNT 10

sem_t two_table_sem;
sem_t four_table_sem;
pthread_mutex_t print_lock;

void* group_of_two(void* arg) {
    int id = *(int*)arg;

    printf("Group of 2 [%d] is waiting for a 2-person table.\n", id);
    sem_wait(&two_table_sem);

    pthread_mutex_lock(&print_lock);
    printf("Group of 2 [%d] got a 2-person table and is dining...\n", id);
    pthread_mutex_unlock(&print_lock);

    sleep(2); // simulate dining time

    pthread_mutex_lock(&print_lock);
    printf("Group of 2 [%d] is done and released the table.\n", id);
    pthread_mutex_unlock(&print_lock);

    sem_post(&two_table_sem);
    pthread_exit(NULL);
}

void* group_of_four(void* arg) {
    int id = *(int*)arg;

    printf("Group of 4 [%d] is waiting for the 4-person table.\n", id);
    sem_wait(&four_table_sem);

    pthread_mutex_lock(&print_lock);
    printf("Group of 4 [%d] got the 4-person table and is dining...\n", id);
    pthread_mutex_unlock(&print_lock);

    sleep(3); // simulate dining time

    pthread_mutex_lock(&print_lock);
    printf("Group of 4 [%d] is done and released the table.\n", id);
    pthread_mutex_unlock(&print_lock);

    sem_post(&four_table_sem);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[GROUP_COUNT];
    int ids[GROUP_COUNT];

    sem_init(&two_table_sem, 0, TWO_TABLES);
    sem_init(&four_table_sem, 0, FOUR_TABLES);
    pthread_mutex_init(&print_lock, NULL);

    for (int i = 0; i < GROUP_COUNT; i++) {
        ids[i] = i + 1;

        // Randomly assign either a group of 2 or 4
        if (rand() % 2 == 0) {
            pthread_create(&threads[i], NULL, group_of_two, &ids[i]);
        } else {
            pthread_create(&threads[i], NULL, group_of_four, &ids[i]);
        }

        usleep(100000); // slight delay to better observe output
    }

    for (int i = 0; i < GROUP_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&two_table_sem);
    sem_destroy(&four_table_sem);
    pthread_mutex_destroy(&print_lock);

    return 0;
}
