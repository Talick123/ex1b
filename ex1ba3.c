// Quick sort

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
void create_sort_arr(char* filename)
void quick_sort(int arr[], int first_i, int last_i);
void randomize_array(int arr[]);
void handle_quick_sort(int arr[], FILE ***fp);
int partition (int arr[], int low, int high);
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
	handle_quick_sort(arr, &fp)
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
void handle_quick_sort(int arr[], FILE ***fp)
{
	int first = 0, last = SIZE -1;
	struct timeval t0, t1;
	
	gettimeofday(&t0, NULL);
	quick_sort(arr, first, last);
	gettimeofday(&t1, NULL);
	fprintf(**fp, "%s %f\n", "q", (double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));
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
