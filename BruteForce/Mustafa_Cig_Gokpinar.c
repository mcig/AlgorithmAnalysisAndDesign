#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Function Prototypes
char* readStrFromFile(FILE*, int);
int isValid(char*, int);
void bruteForce(int);

int main() {
	int size = 3;
	clock_t start, end;
	//start timer
	start = clock();

	//function call
	bruteForce(size);

	end = clock();
	//end timer

	//convert clockticks to seconds
	double seconds = (double) ((end - start) / (double) CLOCKS_PER_SEC);

	printf("This brute force process took %lf secs.\n", seconds);

	return 0;
}

char* readStrFromFile(FILE *fp, int size) {
	char *str = malloc(size * sizeof(char));
	while (!feof(fp)) {
		fscanf(fp, "%s", str);
	}
	return str;
}
int isValid(char *testKey, int size) {
	FILE *fp = fopen("password.txt", "r");
	char *password = readStrFromFile(fp, size);
	//if they are equal return 0 if not return -1
	int returnVal = strcmp(testKey, password) == 0 ? 0 : -1;
	free(password);
	fclose(fp);
	return returnVal;
}

void bruteForce(int size) {
	char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z' };
	char *testKey = malloc(size * sizeof(char));
	int i, *counters = calloc(size, sizeof(int));
	//counters makes track of the array positions of chars in alphabet
	do {
		for (i = 0; i < size; i++) {
			testKey[i] = alphabet[counters[i]];
		}
		//this is for incrementing and decrementing
		if (counters[2] >= 25) {
			counters[2] = 0;
			if (counters[1] >= 25) {
				counters[1] = 0;
				counters[0]++;
			} else {
				counters[1]++;
			}
		} else {
			counters[2]++;
		}
		//
		printf("Tried %s\n", testKey);
	} while (isValid(testKey, size) != 0);
	printf("I have found the password it was %s.\n", testKey);
	free(testKey);
	free(counters);
}
