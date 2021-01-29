#include <stdio.h>
#include <stdlib.h>

int coin_change(int desiredAmount, int *allBanknotes, int *changeBanknotes);
void bubble_sort(int *arr, int size);
void print_array(int *arr, int size);

int main() {
	int size = 8, desiredAmount = 93;
	int allBanknotes[8] = { 100, 20, 50, 500, 10, 1, 2, 5 };
	int *changeBanknotes = malloc(desiredAmount * sizeof(int)); //allocating the worst case

	printf("We are trying to get %d Here is all the banknotes we have:\n",
			desiredAmount);
	print_array(allBanknotes, size);

	int sizeOfChangeArray = coin_change(desiredAmount, allBanknotes,
			changeBanknotes);

	printf("We reached %d with using these banknotes:\n", desiredAmount);
	print_array(changeBanknotes, sizeOfChangeArray);

	free(changeBanknotes);
	return 0;
}

int coin_change(int desiredAmount, int *allBanknotes, int *changeBanknotes) {
	//My algorithm is overall O(n^2) + O(desiredAmount) which turns into just O(n^2);
	//However if we use nlogn sorts, we can decrease the complexity down to O(nlogn) + O(desiredAmount) which turns into just O(nlogn);

	bubble_sort(allBanknotes, (int) sizeof(allBanknotes));	//This takes O(n^2)
	//bubble sort is changed to sort in descending order
	int idxAllBanknotes = 0;
	int idxChangeBanknotes = 0;
	while (desiredAmount > 0) {	//this loop at worst takes O(desiredAmount);
		int currBanknote = allBanknotes[idxAllBanknotes];
		if (currBanknote > desiredAmount)
			idxAllBanknotes++;
		else {
			desiredAmount -= currBanknote;
			changeBanknotes[idxChangeBanknotes] = currBanknote;
			idxChangeBanknotes++;
		}
	}
	return idxChangeBanknotes;
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
			if (arr[j] < arr[j + 1]) { //This is takes constant time
				int_swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	//Overall we have O(n^2 + ...)
	//Which is equal to O(n^2)
}

void print_array(int *arr, int size) {
	int i;
	printf("[ ");
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
}
