/*
 * Mustafa_Cig_Gokpinar.c
 *
 *  Created on: 19 Kas 2020
 *      Author: mcig
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill_array(int*, int, int);
void print_array(int*, int);
void int_swap(int*, int*);
void bubble_sort(int*, int);
void combine(int*, int, int, int);
void merge_sort(int*, int, int);

int main() {
	srand(time(NULL));
	int size = 10;
	int *arrBubble = malloc(size * sizeof(int));
	int *arrMerge = malloc(size * sizeof(int));
	fill_array(arrBubble, size, size * 10);
	memcpy(arrMerge, arrBubble, size * sizeof(int));

	//Bubble Sort Test
	printf("Untouched Array for Bubble Sort: \n");
	print_array(arrBubble, size);
	printf("Sorted using Bubble Sort: \n");
	bubble_sort(arrBubble, size);
	print_array(arrBubble, size);

	printf("\n**********************************\n");

	//Merge Sort Test
	printf("Untouched Array for Merge Sort: \n");
	print_array(arrMerge, size);
	printf("Sorted using Merge Sort: \n");
	merge_sort(arrMerge, 0, size);

	print_array(arrMerge, size);

	//freeing memory
	free(arrBubble);
	free(arrMerge);
	return 0;
}

void int_swap(int *a, int *b) {
	int swapTmp = *a;
	*a = *b;
	*b = swapTmp;
}

void bubble_sort(int *arr, int size) {
	//This Algorithm has a complexity of O(n^2)
	int i, j;
	for (i = 0; i < size - 1; i++) { //This loop is called n-1 times
		for (j = 0; j < size - i - 1; j++) { //This loop is called (n-1) * (n - i - 1) times
			if (arr[j] > arr[j + 1]) { //This is takes constant time
				int_swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	//Overall we have O(n^2 + ...)
	//Which is equal to O(n^2)
}

void combine(int *parentArr, int l, int m, int r) {
	int sizeL = m - l + 1;
	int sizeR = r - m;
	int *tmpLeftArr = malloc(sizeL + 1 * sizeof(int));
	int *tmpRightArr = malloc(sizeR + 1 * sizeof(int));
	int idxL, idxR;

	//Filling tmpLeftArr
	for (idxL = 0; idxL < sizeL; idxL++) {
		tmpLeftArr[idxL] = parentArr[l + idxL];
	}
	//Filling tmpRightArr
	for (idxR = 0; idxR < sizeR; idxR++) {
		tmpRightArr[idxR] = parentArr[m + idxR + 1];
	}

	idxL = 0;
	idxR = 0;
	int idxParent = l;
	//filling the parent array with comparisons
	while (idxL < sizeL && idxR < sizeR) {
		if (tmpLeftArr[idxL] < tmpRightArr[idxR]) {
			parentArr[idxParent] = tmpLeftArr[idxL];
			idxL++;
		} else {
			parentArr[idxParent] = tmpRightArr[idxR];
			idxR++;
		}
		idxParent++;
	}

	while (idxL < sizeL) {
		parentArr[idxParent] = tmpLeftArr[idxL];
		idxL++;
		idxParent++;
	}

	while (idxR < sizeR) {
		parentArr[idxParent] = tmpRightArr[idxR];
		idxR++;
		idxParent++;
	}

	//freeing temp used memory
	free(tmpLeftArr);
	free(tmpRightArr);
}

void merge_sort(int *arr, int l, int r) {
	//This function overall takes O(n * log(n))
	int m = l + (r - l) / 2;
	if (r > l) {
		//As we always divide the array into 2 this process takes log(n) times
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		//For each divided array we call combine() which takes O(n)
		combine(arr, l, m, r);
	}
	//So overall we have a O(n) * O(log(n))
	//Which is equal to O(n * log(n))
}

void fill_array(int *arr, int size, int randomLimit) {
	int i;
	for (i = 0; i < size; i++) {
		arr[i] = rand() % randomLimit;
	}
}

void print_array(int *arr, int size) {
	int i;
	printf("Array = [ ");
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
}

