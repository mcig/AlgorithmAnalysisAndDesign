#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define FILE_PATH_1  "./berlin52.txt" // EDIT THIS LINE
#define FILE_PATH_2  "./burma14.txt"  // EDIT THIS LINE

#define SIZE_1 52 // DO NOT EDIT THIS LINE
#define SIZE_2 14 // DO NOT EDIT THIS LINE

typedef struct { // DO NOT EDIT THIS LINE
	int id;      // DO NOT EDIT THIS LINE
	double x;    // DO NOT EDIT THIS LINE
	double y;    // DO NOT EDIT THIS LINE
} POINT;         // DO NOT EDIT THIS LINE

POINT* read_file();                             // DO NOT EDIT THIS LINE
double greedy(POINT *problem, int idx);         // DO NOT EDIT THIS LINE
double get_distance(POINT p1, POINT p2);        // DO NOT EDIT THIS LINE
//Helpers
int get_closest_city(POINT *tsp, int idx, int size, int *visitedNodes);
void print_node(POINT pnt);
int main() {
	srand(time(NULL));
	clock_t start, end;

	POINT *TSP = read_file(); // Read from txt file and initializing TSP instance(array of points)

	start = clock();

	double min_distance = greedy(TSP, rand() % SIZE_2); //TODO DON'T FORGET TO SWITCH THIS TO 2
	// Starting index of the city chosen arbitrarily between 0-SIZE

	end = clock();

	printf("\nMinimum distance: %.2f\n", min_distance);
	printf("\nFunction took %f seconds to execute \n",
			(double) (end - start) / (double) CLOCKS_PER_SEC);

	free(TSP);
	return 0;
}

POINT* read_file() {
	POINT *instance = malloc(sizeof(POINT) * SIZE_2); //TODO DON'T FORGET TO SWITCH THIS TO 2
	FILE *fp = fopen(FILE_PATH_2, "r"); //TODO DON'T FORGET TO SWITCH THIS TO 2
	int instanceIdx = 0;
	if (fp == NULL)
		return NULL;

	while (!feof(fp)) {
		char dataLine[25];
		fgets(dataLine, 24, fp);
		if (dataLine[strlen(dataLine) - 1] == '\n') //remove \n
			dataLine[strlen(dataLine) - 1] = '\0';
		char *token = strtok(dataLine, ","); //split output using commas
		int outputIdx = 0; //idx of comma seperated vals
		while (token != NULL) {
			char *dummyPointer; //Apparently strtod needs this

			if (outputIdx == 0)
				instance[instanceIdx].id = atoi(token);
			else if (outputIdx == 1)
				instance[instanceIdx].x = strtod(token, &dummyPointer);
			else
				instance[instanceIdx].y = strtod(token, &dummyPointer);

			token = strtok(NULL, ","); //move token
			outputIdx++; //increase data idx
		}
		instanceIdx++;
	}
	fclose(fp);
	return instance;
}

double get_distance(POINT p1, POINT p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)); //mathematical for getting dist
}

int get_closest_city(POINT *tsp, int fromIdx, int size, int *visitedNodes) {
	int i, toIdx = -1; //the city idx
	double minDistance = 999999999.000;
	for (i = 0; i < size; i++) {
		if (visitedNodes[i] != 1) { //unvisited
			if (get_distance(tsp[fromIdx], tsp[i]) <= minDistance) {
				minDistance = get_distance(tsp[fromIdx], tsp[i]);
				toIdx = i;
			}
		}
	}
	return toIdx; //returns -1 þf all nodes are visited
}

void print_node(POINT pnt) {
	printf("id:%d, x:%lf, y:%lf\n", pnt.id, pnt.x, pnt.y);
}

double greedy(POINT *problem, int idx) {
	int size = SIZE_2; //TODO DON'T FORGET TO SWITCH THIS TO 2
	int *visitedNodes = calloc(size, sizeof(int)); //0: unvisited 1: visited
	double totalDist = 0.0;
	printf("My Path:\n");
	//Visit first node
	visitedNodes[idx] = 1;
	print_node(problem[idx]);
	//Visit second node
	int toIdx = get_closest_city(problem, idx, size, visitedNodes);
	visitedNodes[toIdx] = 1;
	print_node(problem[toIdx]);
	totalDist += get_distance(problem[idx], problem[toIdx]);

	//Visit rest of the nodes
	while (toIdx != -1) {
		int fromIdx = toIdx;
		toIdx = get_closest_city(problem, fromIdx, size, visitedNodes);
		if(toIdx == -1)
			break;
		visitedNodes[toIdx] = 1;
		print_node(problem[toIdx]);
		totalDist += get_distance(problem[fromIdx], problem[toIdx]);
	}

	free(visitedNodes);
	return totalDist;
}
