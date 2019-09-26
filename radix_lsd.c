#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// functions prototypes
void randomize_arr(int *, int, int);
int get_max(int *, int);
int digits_to_code(int, int);
int digit_at_place(int, int, int);
int is_sorted(int *, int);
void display_arr(int *, int);
void sort_by_digit(int *, int, int, int);
void radix_sort(int *, int, int);


// main
int main(int argc, char *argv[]) {
    int size_of_array = 50;
    int max_random = 100;
    int chosen_base = 2;
    srand(time(NULL));

    if (argc == 4) {
        size_of_array = atoi(argv[1]);
        max_random = atoi(argv[2]);
        chosen_base = atoi(argv[3]);
    }

    int array[size_of_array];

    randomize_arr(array, size_of_array, max_random);
    display_arr(array, size_of_array);

    radix_sort(array, size_of_array, chosen_base);

    printf("Avant\n");

    display_arr(array, size_of_array);

    if (is_sorted(array, size_of_array))
        printf("SORTED !!\n");
    else
        printf("NOT SORTED\n");

    return 0;
}


// functions definitions

/* Compute the digit at the specified place in number, according to base */
int digit_at_place(int number, int place, int base) {
    for (int i = 0; i < place; ++i) {
        number /= base;
    }
    return number % base;
}

/* Display the array of size size */
void display_arr(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n\n");
}

/* Sort the array by the specified digit  */
void sort_by_digit(int *arr, int digit, int array_size, int base) {
    int **all_buckets = (int **)calloc(base, sizeof(int *));

    printf("0\n");

    for (int i = 0; i < base; ++i) {
      all_buckets[i] = (int *)calloc(array_size, sizeof(int));
    }


    int *buckets_indices = (int *)calloc(base, sizeof(int));

    display_arr(buckets_indices, base);

    printf("1\n");
    for (int i=0; i < array_size; i++) {
	/* printf("11\n"); */
        int d = digit_at_place(arr[i], digit, base);
	/* printf("12\n"); */
        int index = buckets_indices[d];
	printf("buckets_indices: %d\n", buckets_indices[d]);
	/* printf("13\n"); */
	all_buckets[d][index] = arr[i];
	/* printf("14\n"); */
	buckets_indices[d]++;
    }
    printf("2\n");
    int i = 0, j = 0, current_bucket = 0;
    printf("3\n");
    while (i < array_size) {
	if (j == buckets_indices[current_bucket]) {
	    current_bucket++;
	    j = 0;
	}

	arr[i] = all_buckets[current_bucket][j];

	i++;
	j++;
    }
    printf("4\n");

    for (int i = 0; i < base; ++i) {
      free(all_buckets[i]);
    }
    free(buckets_indices);
}

/* do the radix sort on the array */
void radix_sort(int *arr, int size, int base) {
    int number_of_passes = digits_to_code(get_max(arr, size), base);

    for (int i = 0; i < number_of_passes; ++i) {
        sort_by_digit(arr, i, size, base);
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
        return digits_to_code(n / base, base) + 1;
}
