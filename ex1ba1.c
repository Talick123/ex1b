
	/*
	File: ex1ba1.c
	Calculating Executable Times of Bubble and Quick Sort - Windows
	=====================================================================
	Written by: Tali Kalev, ID:208629691, Login: talikal
			and	Noga Levy, ID:315260927, Login: levyno

	This program receives in the argument vectors, the name of a file and
	an integer. The program creates 2 child proccesses - one for bubble sort
	and the other for quick sort.
	Each child creates an array with 50000 cells, inserts random integers and
	sorts them. Both children calculate the time it took them to sort the array
	and print this result into the file sent in the argument vector.
	The parent repeates this process of creating 2 children that sort the
	array 50 times.
	At the end of this process, the parent goes over the file in which
	the results were printed and calculates the minimum, maximum and average
	times for each sorting methods.
	The parent prints in the command line these calculations and when it is
	finished it prints its own executable time. Before the program finishes, it
	deletes the file used.

	Compile:   gcc -Wall ex1ba1.c -o ex1ba1
			   gcc -Wall ex1ba2.c -o ex1ba2
			   gcc -Wall ex1ba3.c -o ex1ba3

	Run: ./ex1ba1.exe <filename> <integer>

	Input: When running the executable file, add name of file and integer.
		   Example: ./ex1ba1.exe filename 17


	Output: Average bubble sort time, average quick sort time,
			minimum bubble sort time, minimum quick sort time,
			maximum bubble sort time, maximum bubble sort time,
			Parent sort time.
			Example: 4.505360 4.520000 4.449000 0.006000 4.598000 4.598000
					228.755000


*/

// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h> 
#include <time.h>

// ----------- const section ---------------------

const int NUM_OF_LOOPS = 50;

// -------prototype section-----------------------

FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void parent_calc(FILE *fp);
void calc_sort_times(char* argv[]);

//---------main section---------------------------

int main(int argc, char *argv[])
{
	clock_t time_req = clock();
	
	check_argv(argc);
	calc_sort_times(argv); 	

	printf("%lf\n", ((double)clock() - time_req) / CLOCKS_PER_SEC);
	if (remove(argv[1]) != 0)
		printf("Error! Unable to delete the file\n");

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
	int i;
	FILE* fp = NULL;

	for(i = 0; i < NUM_OF_LOOPS; i++)
	{
		_spawnlp(_P_WAIT, "ex1ba2.exe", "ex1ba2.exe",argv[1], argv[2], NULL);
		_spawnlp(_P_WAIT, "ex1ba3.exe", "ex1ba3.exe",argv[1], argv[2], NULL); 
	}
	fp = open_file(argv[1], "r");
	parent_calc(fp); //parent prints data from file
	close_file(&fp);
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

	rewind(fp);	//returning to start of file
	fscanf(fp, "%c", &type); //read char from file into 'type' variable

	while(!feof(fp))
	{
		fscanf(fp, "%lf", &curr);  //read data about specific sorting algorithm

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
		fscanf(fp, "%c", &type); //read next sort type
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
