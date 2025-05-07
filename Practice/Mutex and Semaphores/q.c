// You are required to implement a multithreaded simulation of a parking lot system in the C programming language. The parking lot has four floors, with each floor containing exactly 20 parking spots. Each floor should manage its own parking availability independently.

// There is a single shared payment counter for the entire parking lot, and only one car can use it at a time. In this simulation, each car should be represented as a separate thread. When a car arrives, it should randomly choose one of the four floors to look for an available parking space.

// If a spot is available, the car should park for a short duration to simulate the time spent parked. After that, it vacates the spot and proceeds to the payment counter. The payment counter must be accessed in a thread-safe manner, ensuring mutual exclusion, meaning only one car can make a payment at any given time.

// Your program must simulate at least 100 cars arriving, parking, paying, and exiting concurrently. You should use POSIX threads (pthreads) for multithreading and use appropriate synchronization mechanisms like mutexes to protect shared resources and manage concurrency correctly.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_FLOORS 4
#define SPOTS_PER_FLOOR 20
#define NUM_CARS 100

pthread_mutex_t floor_mutexes[NUM_FLOORS];
pthread_mutex_t payment_mutex;

int parking_spots[NUM_FLOORS] = {20, 20, 20, 20};

void* car_thread(void* arg) {
    int car_id = *(int*)arg;
    int parked_floor = -1;

    // Try to find a floor with available space
    for (int attempt = 0; attempt < NUM_FLOORS; ++attempt) {
        int floor = rand() % NUM_FLOORS;
        pthread_mutex_lock(&floor_mutexes[floor]);

        if (parking_spots[floor] > 0) {
            parking_spots[floor]--;
            parked_floor = floor;
            printf("Car %d parked on Floor %d. Spots left: %d\n", car_id, floor + 1, parking_spots[floor]);
            pthread_mutex_unlock(&floor_mutexes[floor]);
            break;
        }

        pthread_mutex_unlock(&floor_mutexes[floor]);
        usleep(10000);  // wait before retrying
    }

    if (parked_floor == -1) {
        printf("Car %d could not find parking and left.\n", car_id);
        return NULL;
    }

    // Simulate parking duration
    usleep((rand() % 3 + 1) * 500000); // 0.5 to 1.5 seconds

    // Vacate the parking spot
    pthread_mutex_lock(&floor_mutexes[parked_floor]);
    parking_spots[parked_floor]++;
    printf("Car %d leaving Floor %d. Spots now: %d\n", car_id, parked_floor + 1, parking_spots[parked_floor]);
    pthread_mutex_unlock(&floor_mutexes[parked_floor]);

    // Use the payment counter
    pthread_mutex_lock(&payment_mutex);
    printf("Car %d is paying...\n", car_id);
    usleep(300000);  // Simulate payment time (0.3 sec)
    printf("Car %d finished payment and exited.\n", car_id);
    pthread_mutex_unlock(&payment_mutex);

    return NULL;
}

int main() {
    pthread_t cars[NUM_CARS];
    int car_ids[NUM_CARS];

    // Initialize mutexes
    for (int i = 0; i < NUM_FLOORS; ++i) {
        pthread_mutex_init(&floor_mutexes[i], NULL);
    }
    pthread_mutex_init(&payment_mutex, NULL);

    // Create threads for each car
    for (int i = 0; i < NUM_CARS; ++i) {
        car_ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_thread, &car_ids[i]);
        usleep(20000);  // Slight delay between arrivals
    }

    // Wait for all cars to finish
    for (int i = 0; i < NUM_CARS; ++i) {
        pthread_join(cars[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_FLOORS; ++i) {
        pthread_mutex_destroy(&floor_mutexes[i]);
    }
    pthread_mutex_destroy(&payment_mutex);

    return 0;
}
