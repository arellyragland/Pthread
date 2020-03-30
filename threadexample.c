/*
This program gives an example of how threads are created and executed.
To compile: gcc -pthread threadexample.c
To run: ./a.out
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

//define constant NUMBERTHREADS as 10
#define NUMBERTHREADS 10

const char* getUserName()
{
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw)
	{
		return pw->pw_name;
	}
	return "";
}

void * printworld(void * tid)
{
	int status;
	/* This function prints the thread’s identifier and then exits. */
	printf("Hello World. Greetings from thread %d\n", tid);

	/*create a bash command to run*/
	char command[50];
	sprintf(command, "ps aux | grep parallel >> processesowned.txt");
	
	/*create a bash command to run*/
	char command1[50];
	sprintf(command1, "echo '\nThread #%d \n' >> processesowned.txt", tid);
	printf ("Username is %s", getUserName());

	/*run the command*/
	status = system(command1);
	status = system(command);

	/*print a farewell message*/
	printf("Bye World from thread %d\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
void* ret = NULL;
/* The main program creates 10 threads and then exits. */
	pthread_t threads[NUMBERTHREADS];
	int status, i;
	//count through 10 threads
	for(i=0; i < NUMBERTHREADS; i++) {
		//run main thread
		printf("Main here. Creating thread %d\n", i);
		//create 10 threads
		status = pthread_create(&threads[i], NULL, printworld, (void *)i);
		//check for errors with creating threads
		if (status != 0) {
			printf("Oops. pthread create returned error code %d\n", status);
			exit(-1);
		}
		pthread_join(threads[i],&ret);
	}
	exit(0);
}
