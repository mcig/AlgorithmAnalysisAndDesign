#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // # OF VERTICES // DONT EDIT THIS LINE

// FUNCTION DECLARATIONS
void dijsktra(int graph[V][V], int src, int target); // DONT EDIT THIS LINE
void printSolution(int distances[], int src, int target); // DONT EDIT THIS LINE
void printGraph(); // DONT EDIT THIS LINE

int minDistance(int visitedNodes[], int distances[]);

//Hints
/*
 -	Pay attention to initial values of variables.
 -	Finding minimum distance is the goal, but don’t forget to save its index!
 -	Target parameter is useless and only for printing. The algorithm must find the all distances from the source vertex.
 */

// GLOBALS
int G[V][V] = { // ADJENCY MATRIX
		/*       A   B   C   D   E */
		/*A*/{ 0, 2, 3, 0, 10 }, // DONT EDIT THIS LINE
				/*B*/{ 2, 0, 1, 6, 0 }, // DONT EDIT THIS LINE
				/*C*/{ 3, 1, 0, 4, 0 }, // DONT EDIT THIS LINE
				/*D*/{ 0, 6, 4, 0, 1 }, // DONT EDIT THIS LINE
				/*E*/{ 10, 0, 0, 1, 0 }, // DONT EDIT THIS LINE
		};

int main() {
	/* The program contains two nested loops each of which has a complexity of O(n).
	 * n is number of vertices.
	 * So the complexity of algorithm is O(n2).
	 * */
	printGraph(G);
	dijsktra(G, 0, 4);
	return 0;
}

int minDistance(int visitedNodes[], int distances[]) {
	int min = INT_MAX, idxMin;
	int i;
	for (i = 0; i < V; i++) {
		if (visitedNodes[i] == 0 && distances[i] <= min) {
			min = distances[i];
			idxMin = i;
		}
	}
	return idxMin;
}

void dijsktra(int graph[V][V], int src, int target) {
	int distances[V]; // DONT EDIT THIS LINE
	int i, j, visitedNodes[V];

	for (i = 0; i < V; i++) {
		distances[i] = INT_MAX;
		visitedNodes[i] = 0;
	}
	distances[src] = 0; //rewriting src's value to 0

	for (i = 0; i < V - 1; i++) {
		int minVertexIdx = minDistance(visitedNodes, distances);
		visitedNodes[minVertexIdx] = 1;
		for (j = 0; j < V; j++) {
			if (visitedNodes[j] == 0
					&& distances[minVertexIdx] + graph[minVertexIdx][j]
							< distances[j] && graph[minVertexIdx][j] != 0) {
				distances[j] = distances[minVertexIdx] + graph[minVertexIdx][j];
			}
		}
	}
	printSolution(distances, src, target);
}

void printSolution(int distances[], int src, int target) {
	int i;
	printf("\nThe shortest path between %c to %c: %d\n", (src + 65),
			(target + 65), distances[target]);
	printf("\nVertex\tDistance from source\n");
	for (i = 0; i < V; ++i) {
		printf("%c\t\t%d\n", (i + 65), distances[i]);
	}
}
void printGraph() {
	int i, j;
	printf("\n");
	for (i = 0; i < V; ++i) {
		for (j = 0; j < V; ++j) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
}
