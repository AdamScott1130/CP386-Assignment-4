/*
------------------------------------------------------------------------------------------
File:    Question2.c
Purpose: Assignment 4, Question 2
==========================================================================================
Program Description:
A memory manager that uses the "Best-Fit" algorithm 
------------------------------------------------------------------------------------------
Author:  Shailendra Singh
Version  2022-04-04
------------------------------------------------------------------------------------------
*/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Function declarations
long AllocateProcess(long size, char* processName, Hole* holeList, Process* processList);
long ReleaseProcess(char* processName, Hole* holeList, Process* processList);

//Struct declarations
typedef struct Process
{
    char* name;
    long startLocation;
    long size;
    Process* nextProcess;
}Process;

typedef struct Hole
{
    long startLocation; 
    long size;
    Hole* nextHole;
}Hole;


int main(int argc, char *argv[])
{
    //Turns standard output buffering off
    setbuf(stdout, NULL);

    //Get the total number of bytes in the continuous memory space
    long memorySize = 0;
    if(argc == 2)
    {
        memorySize = atol(argv[1]);
        printf("Allocated %ld bytes of memory\n", memorySize);
    }

    else
    {
        printf("Command Line Argument Invalid!\n");
    }

    //Initialize command line variables
    char* prompt = "command>";
    char* requestMemory = "RQ";
    char* releaseMemory = "RL";
    char* status = "Status";
    char* exit = "Exit";
    bool loopRunning = true;

    //Initialize memory variables
    long allocatedMemory = 0;
    Process* listOfProcesses = NULL;
    Hole* listOfHoles = (Hole*)malloc(sizeof(Hole));
    listOfHoles->size = memorySize;
    listOfHoles->startLocation = 0;
    listOfHoles->nextHole = NULL;
    
    //Return Statement
    return 0;

}