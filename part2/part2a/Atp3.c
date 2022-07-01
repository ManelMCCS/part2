#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "p3_helper.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf("DEBUG: "__VA_ARGS__)
#else
#define DEBUG_PRINTF(...) \
	do                    \
	{                     \
	} while (0)
#endif

// The number of jobs to process
#define JOBS_NO 8

// The number of concurrent workers
#define SIMULTANEOUS_WORKERS_MAX 2

// typedef struct {
// 	unsigned long input_value; //The value we want to compute
// 	unsigned char processed_flag; // boolean - Flag the result
// 	unsigned long result; //Stores the result after processing
// 	unsigned int worker_pid; //Worker process id - to track the process pid.
// } JOB_Handler;

void dispatch_jobs_v0(JOB_Handler jobs[], int number_of_jobs)
{
	// Process all jobs - monolithic approach
	for (int i = 0; i < number_of_jobs; i++)
	{
		DEBUG_PRINTF("Working job: %d (%lu)\n", i + 1, jobs[i].input_value);
		JOB_update_result_and_processing_status_clear(jobs + i, prime_count(jobs[i].input_value));
	}

	DEBUG_PRINTF("All jobs processed!\n");
}

void dispatch_jobs_v1(JOB_Handler jobs[], int number_of_jobs)
{
	// Process all jobs - One process (worker) per job
	int ret;
	for (int i = 0; i < number_of_jobs; i++)
	{
		if ((ret = fork()) == 0)
		{
			printf("Child(%d) says: Hello!\n", getpid());
			DEBUG_PRINTF("Working job: %d (%lu)\n", i + 1, jobs[i].input_value);
			int job_results = prime_count(jobs[i].input_value);

			exit(job_results);
		}
		else
		{
			JOB_processing_status_update(jobs + i, ret /*worker pid*/);
		}
	}

	DEBUG_PRINTF("All jobs processed!\n");
}

void dispatch_jobs_v2(JOB_Handler jobs[], int number_of_jobs)
{
	// Process all jobs - One process (worker) per job, with
	// a limit on the number of simultaneous workers (SIMULTANEOUS_WORKERS_MAX)
}

int main(int argc, char const *argv[])
{
	/*
	 * In  this main function we'll
	 * 1 - Parametrize a set of job tasks
	 * 2 - Call the job processing function
	 * 3 - Print the processing results
	 */

	JOB_Handler local_var_job_array[JOBS_NO];

	// Seeding...
	srand(time(NULL));
	unsigned long JOB_input_value;

	unsigned long numbers_array[JOBS_NO] = {1000,
											5000,
											3000,
											9000,
											5000,
											6000,
											7000,
											8000};

	// Fill in some random values
	for (int i = 0; i < JOBS_NO; i++)
	{
		// JOB_input_value = (1 + (rand() % 10)) * 1000; //[1..10]*10000
		JOB_init(local_var_job_array + i, numbers_array[i] * 10);
	}

	// Process all jobs - blocking function
	;
	// dispatch_jobs_v0(local_var_job_array, JOBS_NO);
	dispatch_jobs_v1(local_var_job_array, JOBS_NO);
	// dispatch_jobs_v2(local_var_job_array, JOBS_NO);

	// Print the results
	for (int i = 0; i < JOBS_NO; i++)
	{
		printf("Job %d, ", i + 1);

		if (local_var_job_array[i].processed_flag)
			printf(" Processed. Result=%lu", local_var_job_array[i].result);
		else
			printf(" Not Processed.");

		printf("\n");
	}

	return 0;
}

// Job 1,  Processed. Result=1229
// Job 2,  Processed. Result=5133
// Job 3,  Processed. Result=3245
// Job 4,  Processed. Result=8713
// Job 5,  Processed. Result=5133
// Job 6,  Processed. Result=6057
// Job 7,  Processed. Result=6935
// Job 8,  Processed. Result=7837
