#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// functions prototypes
void randomize_arr(int *, int, int);
int get_max(int *, int);
int digits_to_code(int, int);
int digit_at_place(int, int);
int is_sorted(int *, int);
void display_arr(int *, int);
void sort_by_digit(int *, int, int);
void radix_sort(int *, int);


// main
int main(int argc, char *argv[]) {
    int size_of_array = 50;
    int max_random = 100;
    srand(time(NULL));

    if (argc == 3) {
	size_of_array = atoi(argv[1]);
	max_random = atoi(argv[2]);
    }

    int array[size_of_array];

    randomize_arr(array, size_of_array, max_random);
    radix_sort(array, size_of_array);

    if (is_sorted(array, size_of_array))
	printf("SORTED !!\n");
    else
	printf("NOT SORTED\n");

    return 0;
}


// functions definitions

/* Compute the digit at the specified place in number */
int digit_at_place(int number, int place) {
    for (int i = 0; i < place; ++i) {
	number = number >> 1;
    }
    return number % 2;
}

/* Display the array of size size */
void display_arr(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n\n");
}

/* Sort the array by the specified digit  */
void sort_by_digit(int *arr, int digit, int size) {
    int bucket_a[size];
    int bucket_b[size];
    int a = 0, b = 0;

    for (int i=0; i < size; i++) {
        if (digit_at_place(arr[i], digit) == 0) {
            bucket_a[a] = arr[i];
            a++;
        }
        else {
            bucket_b[b] = arr[i];
            b++;
        }
    }

    for(int i=0; i < a; i++)
	arr[i] = bucket_a[i];
    for (int i=0; i < b; i++)
	arr[a+i] = bucket_b[i];
}

/* do the radix sort on the array */
void radix_sort(int *arr, int size) {
    int number_of_passes = bits_to_code(get_max(arr, size));

    for (int i = 0; i < number_of_passes; ++i) {
	sort_by_digit(arr, i, size);
    }
}

/* randomize an array */
void randomize_arr(int *arr, int size, int max) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % max;
    }
}

/* test if an array is sorted */
int is_sorted(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
	if (arr[i-1] > arr[i])
	    return 0;
    }
    return 1;
}

int get_max(int *arr, int size) {
    int max = 0;
    for (int i = 0; i < size; ++i) {
	max = (max > arr[i]) ? max : arr[i];
    }
    return max;
}

int digits_to_code(int n, int base) {
    if (n < base)
	return 1;
    else
	return digits_to_code(n / base) + 1;
}
