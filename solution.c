#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared data
int shared_value = 0;
int reader_count = 0;

// Synchronization primitives
pthread_mutex_t reader_count_mutex;
pthread_mutex_t resource_mutex;

// Global variables for number of readers and writers
int num_readers, num_writers;

// Reader function
void* reader(void* arg) {
    int reader_id = *((int*)arg);
    free(arg);
    
    // Entry section
    pthread_mutex_lock(&reader_count_mutex);
    reader_count++;
    if (reader_count == 1) {
        // First reader locks the resource
        pthread_mutex_lock(&resource_mutex);
    }
    pthread_mutex_unlock(&reader_count_mutex);
    
    // Critical section - reading
    printf("Reader %d is reading value %d\n", reader_id, shared_value);
    fflush(stdout);
    
    // Exit section
    pthread_mutex_lock(&reader_count_mutex);
    reader_count--;
    if (reader_count == 0) {
        // Last reader unlocks the resource
        pthread_mutex_unlock(&resource_mutex);
    }
    pthread_mutex_unlock(&reader_count_mutex);
    
    return NULL;
}

// Writer function
void* writer(void* arg) {
    int writer_id = *((int*)arg);
    free(arg);
    
    // Entry section
    pthread_mutex_lock(&resource_mutex);
    
    // Critical section - writing
    shared_value = writer_id;
    printf("Writer %d is writing value %d\n", writer_id, shared_value);
    fflush(stdout);
    
    // Exit section
    pthread_mutex_unlock(&resource_mutex);
    
    return NULL;
}

int main() {
    // Read input
    scanf("%d %d", &num_readers, &num_writers);
    
    // Initialize mutexes
    pthread_mutex_init(&reader_count_mutex, NULL);
    pthread_mutex_init(&resource_mutex, NULL);
    
    // Create thread arrays
    pthread_t* reader_threads = (pthread_t*)malloc(num_readers * sizeof(pthread_t));
    pthread_t* writer_threads = (pthread_t*)malloc(num_writers * sizeof(pthread_t));
    
    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        int* reader_id = (int*)malloc(sizeof(int));
        *reader_id = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, reader_id);
    }
    
    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        int* writer_id = (int*)malloc(sizeof(int));
        *writer_id = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, writer_id);
    }
    
    // Wait for all reader threads to complete
    for (int i = 0; i < num_readers; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    
    // Wait for all writer threads to complete
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    
    // Clean up
    pthread_mutex_destroy(&reader_count_mutex);
    pthread_mutex_destroy(&resource_mutex);
    free(reader_threads);
    free(writer_threads);
    
    return 0;
}