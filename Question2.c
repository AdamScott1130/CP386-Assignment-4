/*
------------------------------------------------------------------------------------------
File:    Question2.c
Purpose: Assignment 4, Question 2
==========================================================================================
Program Description:
A memory manager that uses the "Best-Fit" algorithm 
------------------------------------------------------------------------------------------
Author:  Adam Scott, Shailendra Singh
Version  2022-04-04
------------------------------------------------------------------------------------------
*/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Constants
#define NAME_LENGTH 20

//Struct declarations
typedef struct Process
{
    char* name;
    long startLocation;
    long size;
    struct Process* nextProcess;
}Process;

typedef struct ProcessList
{
    Process* head;
    long numberOfProcesses;
}ProcessList;

typedef struct Hole
{
    long startLocation; 
    long size;
    struct Hole* nextHole;
}Hole;


typedef struct HoleList
{
    Hole* head;
    long numberOfHoles;
}HoleList;


//Function declarations
long AllocateProcess(long size, char* processName, HoleList* holeList, ProcessList* processList);
long ReleaseProcess(char* processName, HoleList* holeList, ProcessList* processList);
void Status(long memorySize, long memoryAllocated, HoleList* holeList, ProcessList* processList);

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
        exit(-1);
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
    ProcessList* listOfProcesses = (ProcessList*)malloc(sizeof(ProcessList));
    listOfProcesses->head = NULL;
    listOfProcesses->numberOfProcesses = 0;
    HoleList* listOfHoles = (HoleList*)malloc(sizeof(HoleList));
    listOfHoles->head = (Hole*)malloc(sizeof(Hole));
    listOfHoles->numberOfHoles = 1;
    listOfHoles->head->size = memorySize;
    listOfHoles->head->startLocation = 0;
    listOfHoles->head->nextHole = NULL;

    Status(memorySize, allocatedMemory, listOfHoles, listOfProcesses);
    AllocateProcess(200000,"P0", listOfHoles, listOfProcesses);
    
    //Return Statement
    return 0;

}

void Status(long memorySize, long memoryAllocated, HoleList* holeList, ProcessList* processList)
{
    printf("Partitions [Allocated memory = %ld]:\n", memorySize);

    //Print out all the processes
    Process* currentProcess = processList->head;
    long startAddress;
    long endAddress;
    while(currentProcess != NULL)
    {
        startAddress = currentProcess->startLocation;
        endAddress = startAddress + currentProcess->size-1;
        printf("Address[%ld:%ld] Process %s\n", startAddress, endAddress, currentProcess->name);

        currentProcess = currentProcess->nextProcess;
    }
    printf("\n");

    //Print out all the holes
    long freeMemory = memorySize - memoryAllocated;
    printf("Holes [Free memory = %ld]:\n", freeMemory);
    Hole* currentHole = holeList->head;
    while(currentHole != NULL)
    {
        startAddress = currentHole->startLocation;
        endAddress = startAddress + currentHole->size-1;
        printf("Address: [%ld:%ld] len = %ld\n", startAddress, endAddress, currentHole->size);
        currentHole = currentHole->nextHole;
    }
}

long AllocateProcess(long size, char* processName, HoleList* holeList, ProcessList* processList)
{
    //Check if there is a hole big enough for the process
    Hole* previousHole = NULL;
    Hole* currentHole = holeList->head;
    bool holeFound = false;
    long startLocation = 0;
    while(currentHole != NULL)
    {
        //Hole found
        if(currentHole->size >= size)
        {
            //Occupy space within hole
            currentHole->size -= size;
            startLocation = currentHole->startLocation;
            currentHole->startLocation += size;
            holeFound = true;
        }

        //HOle not found, cycle to next hole
        else
        {
            previousHole = currentHole;
            currentHole = currentHole->nextHole;
        }
    }

    //If the hole was not found, fail to allocate the process
    if(!holeFound)
    {
        printf("No hole of sufficient size\n");
        
        //Return 0 bytes allocated
        return 0;
    }

    //Tell user memory is allocated
    printf("Successfully allocated %ld to process %s\n", size, processName);

    //When the hole is found, remove the remaining part of the hole from the list (this is done so it can be added back in a sorted way)
    previousHole->nextHole = currentHole->nextHole;
    currentHole->nextHole = NULL;
    holeList->numberOfHoles--;

    //If the removed hole has no size, discard it completely
    if(currentHole->size == 0)
    {
        free(currentHole);
        currentHole = NULL;
    }

    //If the removed hole still has some size, try to insert it back into the list
    else
    {
        //If the list of holes is now empty, simply place it back in
        if(holeList->numberOfHoles == 0)
        {
            holeList->head = currentHole;
        }

        //The list of holes ain't empty, place it back in and keep it sorted
        else
        {
            //Use the triple ref technique lol (https://www.youtube.com/watch?v=0ZEX_l0DFK0)
            Hole** tracer = &holeList->head;
            while((*tracer != NULL) && currentHole->size > (*tracer)->size)
            {
                tracer = &(*tracer)->nextHole;
            }

            currentHole->nextHole = *tracer;
            *tracer = currentHole;
        }

        holeList->numberOfHoles++;
    }

    //Check if this is the first process allocated
    if(processList->numberOfProcesses == 0)
    {
        //Setup processList head and increment number of process
        processList->head = (Process*)malloc(sizeof(Process));
        processList->head->name = (char*)malloc(sizeof(char)*NAME_LENGTH);
        strcpy(processList->head->name, processName);
        processList->head->size = size;
        processList->head->startLocation = startLocation;
        processList->head->nextProcess = NULL;
        processList->numberOfProcesses++;
    }

    //If it is not the first process allocated, add it as the head
    else
    {
        //Create new process object
        Process* newProcess = (Process*)malloc(sizeof(Process));
        newProcess->name = (char*)malloc(sizeof(char)*NAME_LENGTH);
        strcpy(newProcess->name, processName);
        newProcess->size = size;
        newProcess->startLocation = startLocation;

        //Insert into beginning
        newProcess->nextProcess = processList->head;
        processList->head = newProcess;
        processList->numberOfProcesses++;

    }
}