/*

	File: ex1ba3.c
	Calculating Executable Times of Quicksort Algorithm - Windows
	=====================================================================
	Written by: Tali Kalev, ID:208629691, Login: talikal
			and	Noga Levy, ID:315260927, Login: levyno

	This program receives in the argument vectors, the name of a file and
	an integer. The program creates an array with 50000 cells, inserts random
	integers and sorts them using the quicksort algorithm. The program
	calculates the time it took to sort the array and print this result into
	the file sent in the argument vector.

	Compile:  gcc -Wall ex1ba3.c -o ex1ba3

	Run:	The program is run through executable file ex1ba1.exe:
			./ex1ba1.exe <filename> <integer>

	Input: When running the executable file, add name of file and integer.
		   Example: ./ex1ba1.exe filename 17


	Output: The running time is printed into file given.
			Example: q 0.024952
*/
// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------- const section ---------------------

const int SIZE = 50000;

// -------prototype section-----------------------

FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void create_sort_arr(char* filename);
void quick_sort(int arr[], int first_i, int last_i);
void randomize_array(int arr[]);
void handle_quick_sort(int arr[], FILE **fp);
int partition (int arr[], int low, int high);
void swap(int* a, int* b);

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
	handle_quick_sort(arr, &fp);
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
void handle_quick_sort(int arr[], FILE **fp)
{
	int first = 0, last = SIZE - 1;
	clock_t time_req = clock();

	quick_sort(arr, first, last);
	
	fprintf(*fp, "%s %lf\n", "q", ((double)clock() - time_req) / CLOCKS_PER_SEC);
}

//------------------------------------------------

//function receives array, starting and ending point and sorts the array
//using the quick sort algorithm
void quick_sort(int arr[], int first_i, int last_i)
{
    if(first_i < last_i)
    {
        int q;
        q = partition(arr, first_i, last_i);
        quick_sort(arr, first_i, q-1);
        quick_sort(arr, q+1, last_i);
    }
}

//------------------------------------------------

//function receives array and partitions accordingly
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  // selecting last element as pivot
    int i = (low - 1);  // index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If the current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
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

//------------------------------------------------

//function swaps two numbers
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
