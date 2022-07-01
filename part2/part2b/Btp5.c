#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "p5_helper.h"

#define BUFFER_MAX_SIZE 4

unsigned int data_space[BUFFER_MAX_SIZE];
circ_buff_t buffer = {
    data_space,
    BUFFER_MAX_SIZE,
    0,
    0};
/**
 * @brief producer function pointer. Create a random number between 0 and 999
 * and make a buffer push only if the buffer is available.
 *
 * @param arg
 * @return void*
 */
void *producer_fp(void *arg)
{
    unsigned int push_value;
    while (1)
    {
        push_value = (rand() % 1000); // random [0,999]
        if (circ_buff_push(&buffer, push_value) == 0)
            printf("Producer: %u\n", push_value);
        else
            printf("Producer: buffer is full\n");

        usleep(100 * 1000); // 100 ms
    }

    return NULL;
}

void *consumer_fp(void *arg)
{
    unsigned int pop_value;
    while (1)
    {
        if (circ_buff_pop(&buffer, &pop_value) == 0)
            printf("                              Consumer: returned %u\n", pop_value);
        else
            printf("                              Consumer: buffer is empty\n");

        usleep(150 * 1000); // 150 ms
    }

    return NULL;
}
int main(void)
{
    // Seeding...
    srand(time(NULL));

    pthread_t thread_id_array[2];

    pthread_create(&(thread_id_array[0]), NULL, &producer_fp, NULL);
    pthread_create(&(thread_id_array[1]), NULL, &consumer_fp, NULL);

    pthread_join(thread_id_array[0], NULL);
    pthread_join(thread_id_array[1], NULL);

    return 0;
}