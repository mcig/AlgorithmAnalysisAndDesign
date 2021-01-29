#include <stdio.h>
#include <stdlib.h>

//Function macros
#define leftChildIdx(i) ((2 * (i)) + 1)
#define rightChildIdx(i) ((2 * (i)) + 2)
#define parentIdx(i) (((i) - 1) / 2)

//Func Prototypes
void heapify_array(int *arr, int size);
void heapsort(int *heap, int size);
//Helpers
void heapify_recursive(int *heap, int idx, int size);
void print_heap(int *heap, int size);
void int_swap(int *a, int *b);

int main() {
	int a[] = { 1, 5, 123, 6, 3, 12, 3, 4, 12, 5, 6, 786, 3, 34, 754, 234 };
	int size = sizeof(a) / sizeof(int);

	heapsort(a, size);
	print_heap(a, size);
	return 0;
}

void int_swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify_recursive(int *heap, int idx, int size) {
	int leftIdx = leftChildIdx(idx);
	int rightIdx = rightChildIdx(idx);
	int largest;
	if (leftIdx < size && heap[leftIdx] > heap[idx]) {
		largest = leftIdx;
	} else {
		largest = idx;
	}
	if (rightIdx < size && heap[rightIdx] > heap[largest]) {
		largest = rightIdx;
	}
	if (largest != idx) {
		int_swap(&heap[idx], &heap[largest]);
		heapify_recursive(heap, largest, size);
	}
}

void heapify_array(int *arr, int size) {
	int i;
	for (i = (size / 2) - 1; i >= 0; i--) {
		heapify_recursive(arr, i, size);
	}
}

void heapsort(int *arr, int size) {
	heapify_array(arr, size);
	print_heap(arr, size);
	int i;
	for (i = size - 1; i > 0; i--) {
		int_swap(&arr[0], &arr[i]);
		heapify_recursive(arr, 0, i - 1);
	}
}

void print_heap(int *heap, int size) {
	int i;
	printf("Heap: ");
	for (i = 0; i < size; i++)
		printf("%d ", heap[i]);
	printf("\n");
}
