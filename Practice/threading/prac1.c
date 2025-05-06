//A large E-Commerce platform handles multiple users trying to purchase the same product simultaneously. Each user request is handled by a separate thread. The task is to correctly update the product's inventory (quantity) in real-time without using mutexes, semaphores, or atomic libraries like <stdatomic.h>.
//Design a multi-threaded program that simulates this scenario, ensuring that quantity reflects the total number of successful purchases.
//Note: You are not allowed to use mutex, semaphores.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for usleep

int quantity = 0; // Shared resource

void *shop(void *param) {
    int user_id = *(int *)param;

    // Simulate time taken in real transaction
    int temp = quantity; // read
    usleep(100);         // simulate delay
    temp = temp + 1;     // increment
    quantity = temp;     // write

    printf("User %d purchased. Temporary quantity: %d\n", user_id, quantity);

    pthread_exit(0);
}

int main() {
    pthread_t threads[3];
    int user_ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, shop, &user_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final quantity of product purchased: %d\n", quantity);
    return 0;
}
