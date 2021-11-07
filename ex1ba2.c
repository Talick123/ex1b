// Bubble sort

// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <sys/time.h>

// ----------- const section ---------------------

const int SIZE = 50000;

// -------prototype section-----------------------

FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void calc_sort_times(char *filename);
void bubble_sort(int arr[]);

void randomize_array(int arr[]);

void handle_bubble_sort(int arr[], FILE ***fp);

void swap(int* a, int* b);

//---------main section---------------------------

int main(int argc, char *argv[])
{
	struct timeval t0, t1;
	gettimeofday(&t0, NULL); //calculating start time
	
	check_argv(argc); //different value
	srand(atoi(argv[2])); //make sure number is correct
	create_sort_arr(argv[1]); 

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

//------------------------------------------------

void create_sort_arr(char* filename)
{
	FILE *fp = open_file(argv[1], "w");
	int arr[SIZE];
	randomize_arr(arr);
	handle_bubble_sort(arr, &fp)
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
void handle_bubble_sort(int arr[], FILE ***fp)
{
	struct timeval t0, t1;
	
	gettimeofday(&t0, NULL);
	bubble_sort(arr);
	gettimeofday(&t1, NULL);
	//return to beginning?
	fprintf(**fp, "%s %f\n", "b", (double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));
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

//------------------------------------------------


