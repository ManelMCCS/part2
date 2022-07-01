#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// A regular C function that executs as a thread
void *myThreadFunction(void *vargp)
{
	int id = *(int *)vargp;
	sleep(2);
	printf("Printing from Thread %d \n", id);
	return NULL;
}

int main()
{
	pthread_t thread_id_1, thread_id_2; // Thread ID

	printf("Creating 2 Threads\n");

	pthread_create(&thread_id_1, NULL, myThreadFunction, (void *)(&thread_id_1));
	pthread_create(&thread_id_2, NULL, myThreadFunction, (void *)(&thread_id_2));

	pthread_join(thread_id_1, NULL);
	pthread_join(thread_id_2, NULL);

	printf("After Running Threads\n");
	exit(0);
}
