#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int knapsack_recursive(int *vals, int *weights, int idx, int crntCap);
int** knapsack_dynamic(int *vals, int *weights, int size, int Cap);

//helpers
int** alloc_2d_int_arr(int size);
void free_2d_int_arr(int **arr, int size);
int max(int a, int b);

int main() {
	int arr_size = 4, bag_capacity = 5;
	int vals[] = { 100, 20, 60, 40 };
	int weights[] = { 3, 2, 4, 1 };
	clock_t start, end;
	double seconds;

	//RECURSIVE O(2^arr_size)
	start = clock();
	int result = knapsack_recursive(vals, weights, arr_size, bag_capacity);
	end = clock();
	seconds = (double) ((end - start) / (double) CLOCKS_PER_SEC);
	printf("Recursive Solution: %d\n", result);
	printf("This recursive process took %lf secs.\n", seconds);

	 //DYNAMIC O(arr_size * bag_capacity)
	 start = clock();
	 int **solution_table_dynamic = knapsack_dynamic(vals, weights, arr_size,
	 bag_capacity);
	 end = clock();
	 seconds = (double) ((end - start) / (double) CLOCKS_PER_SEC);
	 printf("Dynamic Solution: %d\n", solution_table_dynamic[arr_size][arr_size]);
	 printf("This dynamic process took %lf secs.\n", seconds);

	 free_2d_int_arr(solution_table_dynamic, arr_size + 1);
	return 0;
}

int knapsack_recursive(int *vals, int *weights, int crntIdx, int crntCap) {
	//The complexity of this function is O(2^size) which is very high
	//because for each idx we calculate 2 paths an it grows exponentially
	if (crntIdx == 0 || crntCap == 0)
		return 0; //Same approach with filling the first row and column with 0s in dynamic solution

	if (weights[crntIdx - 1] > crntCap) {
		return knapsack_recursive(vals, weights, crntIdx - 1, crntCap);
	} else {
		return max(vals[crntIdx - 1]
						+ knapsack_recursive(vals, weights, crntIdx - 1, crntCap - weights[crntIdx - 1]),
			knapsack_recursive(vals, weights, crntIdx - 1, crntCap));
	}

}

int** knapsack_dynamic(int *vals, int *weights, int size, int Cap) {
	//O(size * Cap) is the overall complexity of this code
	int i, j, **solution_table = alloc_2d_int_arr(size + 1);
	for (i = 0; i < size + 1; i++) { //this loop executes size times
		for (j = 0; j < Cap; j++) { //this loop executes size * Cap times
			//THESE codes are executed n*w times
			if (i == 0 || j == 0)
				solution_table[i][j] = 0;
			else if (weights[i - 1] <= j) {
				solution_table[i][j] = max(
						vals[i - 1] + solution_table[i - 1][j - weights[i - 1]],
						solution_table[i - 1][j]);
			} else {
				solution_table[i][j] = solution_table[i - 1][j];
			}
		}
	}
	return solution_table;
}

int** alloc_2d_int_arr(int size) {
	int i, **arr = malloc(sizeof(int*) * size);
	for (i = 0; i < size; i++)
		arr[i] = malloc(sizeof(int) * i);
	return arr;
}

void free_2d_int_arr(int **arr, int size) {
	int i;
	for (i = 0; i < size; i++)
		free(arr[i]);
	free(arr);
}

int max(int a, int b) {
	return a > b ? a : b;
}
