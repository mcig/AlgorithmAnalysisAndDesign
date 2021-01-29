//ON PAPER QUIZ ANSWERS SECTION 2 Mustafa Cig Gokpinar
//1.A 2.E 3.C 4.B 5.B

#include <stdio.h>
#define V 4

#define min(a,b) (a < b ? a:b)
void floydWarshall(int graph[][V]);
void printDistances(int solution[][V]);

int main() {
	int graph[][V] = { { 0, 2, 7, 3 }, { 8, 0, 2, 4 }, { 5, 3, 0, 6 }, { 9, 1,
			8, 0 } };
	printf("Current ");
	printDistances(graph);

	floydWarshall(graph);

	return 0;
}

void floydWarshall(int graph[][V]) {
	int i, j, k;
	int size = V;
	//Overall my code is O(V^3)
	for (i = 0; i < size; i++) { //this loop iterates vertex count times
		for (j = 0; j < size; j++) { //this loop also iterates vertex count times
			for (k = 0; k < size; k++) { //finally, this loop also iterates vertex count times
				int oldVal = graph[j][k];
				graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]); //Thus, this statement is executed V^3 times

				if (graph[j][k] != oldVal) { //if there is a change
					printf("\nEDITED %d ---(%d)--> %d\n", j, oldVal, k); //print it
					printf("TO %d ---(%d)--> %d\n", j, graph[j][k], k);
				}
				else{
					printf("\nKEPT %d ---(%d)--> %d\n", j, graph[j][k], k); //print it
				}
			}
		}
	}
	printf("\nSolved ");
	printDistances(graph);
}

void printDistances(int graph[][V]) {
	//Overall this code is O(V^2)
	int i, j;
	int size = V;
	printf("Graph:\n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%d ---(%d)--> %d\n", i, graph[i][j], j);
		}
	}
	printf("\n*****************************************\n");
}
