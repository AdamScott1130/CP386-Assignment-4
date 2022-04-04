#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Purpose: This program implements the Banker's Algorithm of resource allocation to
// avoid deadlocks.

// Authors: Adam Scott 190600780 and Shailendra Singh

// Function definitions

int RQ(){
	// RQ is a thread function that requests resources based on the user's input.
	// Input: array of integers representing a resource request and and the current maximum and available arrays.
	// Output: 0 if the resources were successfully allocated, otherwise 1.
	return 1;
}

int safeState() {
	// safeState checks whether the program would be in a safe state if the input request
	// would leave the system in a deadlock.
	// Input: array representing the resource request and the current maximum and available arrays.

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


int main(){
	// main reads the file in from sample_in.txt, then accepts user input commands
	// Input: Array of integers representing the available resources.

	// read the maximum resources in from the file.


	// check that the initial conditions result in a safe state.


	// Loop forever (exits when command exit is sent).
	// Parse keyboard input (COMMAND, THREAD ID, [RESOUCES])

	return 0;
}
