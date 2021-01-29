#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TABLESIZE 10

typedef struct {
	int key;
	int hashedData;
} KEYDATA_t[1], *KEYDATA;

typedef struct {
	int tableSize;
	int (*hashFunction)(void*); //holds the hash function in the struct
	KEYDATA *Table;
} HASHTABLE_t[1], *HASHTABLE;

//Struct function prototypes
HASHTABLE hashtable_init(int size, int (*hashFunction)(void*));
void hashtable_free(HASHTABLE ht);
int hashtable_put(HASHTABLE ht, void *data);
void hashtable_print_integer(HASHTABLE ht);
//

//HASH Function Prototypes
int first_hashing(void *data);
int second_hashing(void *data);
//

//Helper Prototypes
HASHTABLE create_and_fill_with_integers(int *arr, int size,
		int (*hashFunction)(void*));
void fill_arr_with_randoms(int *arr, int size);
int sum_digits(int a);
//

//MAIN
int main(int argc, char **argv) {
	srand(time(NULL));

	int arr1[TABLESIZE];
	fill_arr_with_randoms(arr1, TABLESIZE);

	int arr2[TABLESIZE];
	fill_arr_with_randoms(arr2, TABLESIZE);

	HASHTABLE firstTable = create_and_fill_with_integers(arr1, TABLESIZE,
			first_hashing);
	HASHTABLE secondTable = create_and_fill_with_integers(arr2, TABLESIZE,
			second_hashing);

	printf("FIRST ");
	hashtable_print_integer(firstTable);

	printf("\n*****************************************\n");

	printf("SECOND ");
	hashtable_print_integer(secondTable);

	printf("\n*****************************************\n");

	hashtable_free(firstTable);
	hashtable_free(secondTable);
	return 0;
}
//

//HASH Function Declarations
int first_hashing(void *data) {
	int result = sum_digits(*(int*) data);
	while (result >= TABLESIZE) // for cases like 99 - > 18 - > 9
		result = sum_digits(result);
	return result;
}

int second_hashing(void *data) {
	return *(int*) data % TABLESIZE;
}
//

//Helper Declarations
int sum_digits(int a) {
	if (a < 10)
		return a;
	else {
		int lastDigit = a % 10;
		return lastDigit + sum_digits(a / 10);
	}
}

void fill_arr_with_randoms(int *arr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		arr[i] = rand() % 200;
	}
}

HASHTABLE create_and_fill_with_integers(int *arr, int size,
		int (*hashFunction)(void*)) {
	HASHTABLE ht = hashtable_init(size, hashFunction);
	int i = 0;
	for (i = 0; i < size; i++) {
		hashtable_put(ht, &arr[i]);
	}

	return ht;
}
//

//Structure Function definitions
HASHTABLE hashtable_init(int size, int (*hashFunction)(void*)) {
	HASHTABLE ht = (HASHTABLE) malloc(sizeof(HASHTABLE_t));
	ht->tableSize = size;
	ht->hashFunction = hashFunction;
	ht->Table = malloc(sizeof(KEYDATA) * ht->tableSize);

	int i;
	for (i = 0; i < ht->tableSize; i++) {
		ht->Table[i] = malloc(sizeof(KEYDATA_t));
		ht->Table[i]->key = 0;
		ht->Table[i]->hashedData = 0;
	}
	return ht;
}

void hashtable_free(HASHTABLE ht) {
	int i;
	for (i = 0; i < ht->tableSize; i++) {
		free(ht->Table[i]);
	}
	free(ht->Table);
	free(ht);
}

int hashtable_put(HASHTABLE ht, void *data) {
	int hashedValue = ht->hashFunction(data);

	ht->Table[hashedValue]->key = *(int*) data;
	ht->Table[hashedValue]->hashedData = hashedValue;
	return hashedValue;
}

void hashtable_print_integer(HASHTABLE ht) {
	int i = 0;
	printf("HASHTABLE\n");
	for (i = 0; i < ht->tableSize; i++) {
		int unhashed = ht->Table[i]->key;
		int hashed = ht->Table[i]->hashedData;
		printf("| [%d]: Unhashed: %d Hashed: %d", i, unhashed, hashed);
		printf(" |\n");
	}
}
//

