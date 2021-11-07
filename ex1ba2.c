/*
	File: ex1ba2.c
	Calculating Executable Times of Bubblesort Algorithm - Windows
	=====================================================================
	Written by: Tali Kalev, ID:208629691, Login: talikal
			and	Noga Levy, ID:315260927, Login: levyno

	This program receives in the argument vectors, the name of a file and
	an integer. The program creates an array with 50000 cells, inserts random 
	integers and sorts them using the bubblesort algorithm. The program 
	calculates the time it took to sort the array and print this result into 
	the file sent in the argument vector.

	Compile: gcc -Wall ex1ba2.c -o ex1ba2

	Run:	The program is run through executable file ex1ba1.exe:
			./ex1ba1.exe <filename> <integer>

	Input: When running the executable file, add name of file and integer.
		   Example: ./ex1ba1.exe filename 17


	Output: The running time is printed into file given.
			Example: b 0.024952
*/
// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------- const section ---------------------

const int SIZE = 50000;

// -------prototype section-----------------------

void create_sort_arr(char* filename);
FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void bubble_sort(int arr[]);
void create_sort_arr(char* filename);
void randomize_array(int arr[]);
void handle_bubble_sort(int arr[], FILE **fp);

//---------main section---------------------------

int main(int argc, char *argv[])
{	
	check_argv(argc); //make sure number is correct
	srand(atoi(argv[2])); //changes char to int
	create_sort_arr(argv[1]); 

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

//------------------------------------------------

void create_sort_arr(char* filename)
{
	FILE *fp = open_file(filename, "a+");
	int arr[SIZE];
	randomize_array(arr);
	handle_bubble_sort(arr, &fp);
}

//function recieves array and enters randomized numbers into it
void randomize_array(int arr[])
{
	int index;
	
	for(index = 0; index < SIZE; index++)
		arr[index] = (rand() % 1000); 
}

//------------------------------------------------

//function receives array and file, sorts array and puts calculated
//run time into file
void handle_bubble_sort(int arr[], FILE **fp)
{
	clock_t time_req = clock();

	bubble_sort(arr);
	
	fprintf(*fp, "%s %lf\n", "b", ((double)clock() - time_req) / CLOCKS_PER_SEC);
}

//------------------------------------------------

//function receives array and sorts it using the bubble sort algorithm
void bubble_sort(int arr[])
{
	int step, i, temp;
	// loop to access each array element
	for (step = 0; step < SIZE - 1; ++step) {
		// loop to compare array elements
		for (i = 0; i < SIZE - step - 1; ++i) {
			// compare two adjacent elements
			// change > to < to sort in descending order
			if (arr[i] > arr[i + 1]) {
				// swapping occurs if elements
				// are not in the intended order
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
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




