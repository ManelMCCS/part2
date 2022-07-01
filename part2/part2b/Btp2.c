#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Create a global variable to to observe its changes
int global_test_var = 0;

// A regular C function that executs as a thread
void *myThreadFunction(void *vargp)
{
    int id = *(int *)vargp;

    // Create a static variable to observe its changes
    static int static_test_var = 0;

    // Change static and global variables
    static_test_var++;
    global_test_var++;

    // Change again and print
    printf("Thread ID(%p): %d, Static(%p): %d, Global(%p): %d\n",
           &id, id, &static_test_var, ++static_test_var, &global_test_var, ++global_test_var);

    return NULL;
}

int main()
{
    pthread_t thread_id_array[3]; // Thread ID

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread_id_array[i], NULL, myThreadFunction, (void *)&thread_id_array[i]);
        usleep(100);
    }

    for (int i = 0; i < 3; i++)
        pthread_join(thread_id_array[i], NULL);

    exit(0);
}
