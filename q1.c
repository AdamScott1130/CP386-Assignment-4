#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Purpose: This program implements the Banker's Algorithm of resource allocation to
// avoid deadlocks.

// Authors: Adam Scott 190600780 and Shailendra Singh 190777790

// Function definitions


int safeState(int threadID, int request[4], int allocated[5][4], int need[5][4], int available[4]) {
	// safeState checks whether the program would be in a safe state if the input request
	// could leave the system in a deadlock.
	// Input: array representing the resource request and the current maximum and available arrays.
	// Output: 1 if the request results in a safe state, 0 if it may result in a deadlock

	// First, add the request to the thread's row in the need matrix
	for (int i = 0; i < 4; i += 1) {
		need[threadID][i] += request[i];
	}

	// Next, find a safe sequence (safety algorithm)
	int finish[5] = {0,0,0,0,0};
	int safeCounter = 5;
	int sequence[5];
	int flag = 0;
	while (safeCounter != 0) {
		// reset flag to 0 on each iteration. If at the end, flag = 0, then it did not
		// reach 'flag = 1' on every iteration. That means that not every process was able to be allocated
		// its resources and execute, so the state would be unsafe. If flag = 1 at the end, then we have a safe state.
		flag = 0;
		for(int i = 0; i < 5; i += 1) {
			if(finish[i] == 0) { // check that the thread has not already been executed and had its resources freed.
				int j;
				for (j = 0; j < 5; j += 1) {
					// check whether each resource in i's need matrix is more than what is available
					if (need[i][j] > available[j]) {
						break;
					}
				}
				// If we reach the end with j = # of resources, then all resources have more available
				// instances than process i has need, i.e., this process can execute
				if (j == 5) {
					// mark that process i can run
					finish[i] = 1;
					// must reach this line on final iteration in order to be safe
					flag = 1;
					safeCounter += -1;
					// give its resources back to the CPU
					for (int k = 0; k < 5; k += 1) {
						available[k] += allocated[i][k];
					}
					break;
				}
			}
		}
		// not a safe state, so return 0
		if (flag == 0) {
			return 0;
		}
	}
	// safe state, so return 1
	return 1;
}





int RQ(int threadID, int request[4], int allocated[5][4], int need[5][4], int available[4]){
	// RQ is a function that requests resources based on the user's input.
	// Input: array of integers representing a resource request and and the current maximum and available arrays.
	// Output: 0 if the resources were successfully allocated, otherwise 1.
	if (safeState(threadID, request, allocated, need, available)) {
		printf("Request results in safe state! Allocating resources...!\n");
		return 0;
	}
	printf("Request results in unsafe state. Thread %d must wait.\n", threadID);
	return 1;
}


int RL(){
	// RL us a thread function that releases resources based on the user's input
	// Input: array of integers representing the release request and the current maximum and available arrays.
	// Output: 0 if the resources were successfully released, otherwise 1.


	// check that the release reuqest does not leave the thread with negative resources

	// release the resources, update relevant arrays
	return 1;
}

int status() {
	// status prints the available, maximum, allocation, and need arrays.
	return 0;
}

int run() {
	// run creates threads which will execute in some safe sequence. Because the Banker's algorithm has been
	// implemented, we should never have a deadlock while running threads.
}
int exitProgram() {
	// terminates the program
	exit(0);
}

int main(int argc, char *argv[]){
	// main reads the file in from sample_in.txt, then accepts user input commands
	// Input: Array of integers representing the available resources.

	if (argc < 2){
		printf("No available resources passed! Exiting...\n");
		exit(-1);
	}

	printf("HERE1\n");
	int numRows = 5; // number of threads
	int numCols = 4; // number of resources

	int maximum[5][4] = {{6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 5, 7, 5}};
	int allocated[5][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
	int need[5][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
	printf("HERE2\n");
	int available[argc-1];
	for (int i = 1; i < argc-1; i+=1) {
		available[i-1] = atoi(argv[i]);
	}

	for (int i = 0; i < numRows; i += 1) {
		for (int j = 0; j < numCols; j += 1)  {
			need[i][j] = maximum[i][j] - allocated[i][j];
			// printf(" %d ", need[i][j]);
		}
	}
	int request[4] = {0,0,0,0};
	printf("HERE3\n");

	int testRQ = RQ(0, request, allocated, need, available);
	return 0;
}
