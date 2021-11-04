
/*

File: ex1a.c
Calculating Executable Times of Bubble and Quick Sort
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

This program receives in the argument vectors, the name of a file and 
an integer. The program uses the integer to draw random numbers into
an array of 50000 cells. The parent of the program creates 2 children
via the command fork(). One child sorts the array using bubble sort
while the other uses quick sort. Both children calculate the time it
took them to sort the array and print this result into the file sent
in the argument vector.
The parent repeates this process of creating 2 children that sort the
array 50 times.
At the end of this process, the parent goes over the file in which
the results were printed and calculates the minimum, maximum and average
times for each sorting methods.
The parent prints in the command line these calculations and when it is 
finished it prints the time its own executable time.

Compile: gcc -Wall ex1a.c -o ex1a
Run: ./ex1a <filename> <integer>

Input: When running the executable file, add name of file and integer.
	   Example: ./ex1a filename 17
	 

Output: Average bubble sort time, average quick sort time, 	
		minimum bubble sort time, minimum quick sort time, 
		maximum bubble sort time, maximum bubble sort time,
		Parent sort time.
		Example: 8.232045 8.259982 7.979422 0.012284 8.485131 8.485131
				411.873370

*/

// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> //no need?
#include <sys/time.h>
#include <process.h>
#include <windows.h> //needed for spawn?

// ----------- const section ---------------------

const int SIZE = 50000;
const int NUM_OF_LOOPS = 50;

// -------prototype section-----------------------

FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );

void parent_calc(FILE *fp);

void handle_child(int child_num, int arr[], FILE **fp);

//---------main section---------------------------
/*
-parent opens file
-parent creates children and sends to them 1. name of file (argv[1]) 2. argv[2] 
-the child uses srand, builds a randomized array, calculates sort time, sorts, prints into document, closes file?? 

*/

int main(int argc, char *argv[])
{
	struct timeval t0, t1;
	gettimeofday(&t0, NULL); //calculating start time
	
	check_argv(argc);
	calc_sort_times(argv); 

	gettimeofday(&t1, NULL); //calculating end time
	//printing time parent took to run
	printf("%f\n",(double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));

	return EXIT_SUCCESS;
}

//------------------------------------------------

//function opens file and checks that process was completed successfully
FILE * open_file(char* filename,  char *mode)
{
	FILE *fp = fopen(filename, mode);

	//if unsuccessful stops program
	if (fp == NULL)
	{
		printf("Error! cannot open %s  \n", filename);
		exit (EXIT_FAILURE);
	}
    return fp;
}

//-------------------------------------------------

//function receives filename and calculates sort time
//of bubble and quick sort via children
void calc_sort_times(char *argv[])
{
	int i, j;
	
	FILE *fp = open_file(argv[1], "r");

	for(i = 0; i < NUM_OF_LOOPS; i++)
	{
		_spawnl(_P_WAIT, "path", "ex1ba2.exe",argv[1], argv[2], NULL);
		_spawnl(_P_WAIT, "path", "exe1ba3.exe",argv[1], argv[2], NULL); 
	}

	parent_calc(fp); //parent prints data from file
	close_file(&fp);
	remove(filename); //deleting file
}

//------------------------------------------------

//function receives file filled with run time data and prints
//out average, min and max of all run time data 
void parent_calc(FILE *fp)
{
	double sum_bsort, sum_qsort, min_bsort, min_qsort, 
				max_bsort, max_qsort, curr; 
	char type;

	//setting initial values
	sum_bsort = sum_qsort = max_bsort = max_qsort = 0;
	min_qsort = min_bsort = 100;

	//returning to start of file
	rewind(fp);
	fscanf(fp, "%c", &type); //read char from file into 'type' variable

	while(!feof(fp))
	{
		//read data about specific sorting algorithm
		fscanf(fp, "%lf", &curr);

		if(type == 'b') //if bubble sort
		{
			//compares numbers and adds to sum
			if(curr < min_bsort)
				min_bsort = curr;
			if(curr > max_bsort)
				max_bsort = curr;
			sum_bsort += curr;
		}
		else	//if quick sort
		{
			//compares numbers and adds to sum
			if(curr < min_qsort)
				min_qsort = curr;
			if(curr > max_qsort)
				max_qsort = curr;
			sum_qsort += curr;
		}

		//read next sort type
		fscanf(fp, "%c", &type); 
	}
	//dividing sums to get average
	sum_bsort /= NUM_OF_LOOPS;
	sum_qsort /= NUM_OF_LOOPS;
	
	//prints onto screen values calculated
	printf("%lf %lf %lf %lf %lf %lf\n", sum_bsort, sum_qsort, min_bsort, 
													min_qsort, max_bsort, max_qsort);
	
}

//------------------------------------------------

//function closes file
void close_file(FILE **fp)
{
  int res = fclose(*fp);
	//checks if action failed
	if(res !=0)
		printf("Error! Failed to close file.\n");
}

//------------------------------------------------

//function checks that both input file and output file names are
//given in argument vector
void check_argv(int argc )
{
	if(argc != 3)
	{
		printf("Error! Incorrect number of arguments.\n");
		exit(EXIT_FAILURE);
	}
}
