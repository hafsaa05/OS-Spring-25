#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>  // for usleep

#define NUM_READERS 5
#define NUM_WRITERS 2
#define STRING_LENGTH 60

pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
sem_t mutex, rw_mutex;

int readers_count = 0;
FILE *file;

// Generate a random lowercase character
char generateRandomChar() {
    return (char)('a' + rand() % 26);
}

// Reader thread function
void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);  // First reader locks access to file
        }
        sem_post(&mutex);

        // Reading from file
        fseek(file, 0, SEEK_SET);
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fprintf(stdout, "Reader %ld: %s", (long)arg, buffer);
        }

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);  // Last reader unlocks access
        }
        sem_post(&mutex);

        usleep(1000);  // Sleep for 1ms
    }
    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex);  // Writer locks access to file

        // Generate random string
        srand(time(NULL) + (long)arg);  // Seed random uniquely
        char randomString[STRING_LENGTH + 1];
        for (int i = 0; i < STRING_LENGTH; i++) {
            randomString[i] = generateRandomChar();
        }
        randomString[STRING_LENGTH] = '\0';

        // Write to file and console
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s\n", randomString);
        fprintf(stdout, "Writer %ld: %s\n", (long)arg, randomString);
        fflush(file);  // Ensure write is flushed to disk

        sem_post(&rw_mutex);  // Release lock
        usleep(1000);         // Sleep for 1ms
    }
    return NULL;
}

// Main function
int main() {
    file = fopen("shared_file.txt", "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)(long)i);
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)(long)i);
    }

    // Wait for all threads to finish (infinite loop here, so won't end)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    fprintf(stdout, "Reader pthread join completed\n");

    // Clean up
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    fclose(file);

    return 0;
}
