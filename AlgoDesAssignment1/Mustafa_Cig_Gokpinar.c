#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

typedef struct {
	int source,                                // DON'T EDIT THIS LINE
			destination,                           // DON'T EDIT THIS LINE
			weight;                                // DON'T EDIT THIS LINE
} EDGE;                                         // DON'T EDIT THIS LINE

typedef struct {
	int num_vertices,                          // DON'T EDIT THIS LINE
			num_edges;                             // DON'T EDIT THIS LINE
	EDGE *edges;                               // DON'T EDIT THIS LINE
} GRAPH;                                        // DON'T EDIT THIS LINE

//Heap related Function-like macros
#define leftChildIdx(i) ((2 * (i)) + 1)
#define rightChildIdx(i) ((2 * (i)) + 2)
#define parentIdx(i) (((i) - 1) / 2)

//Heapsort Function Prototypes
void heapify_array(EDGE *arr, int size);
void heapsort(EDGE *edgeArr, int size);
void heapify_recursive(EDGE *edgeArr, int idx, int size);

//Heapsort Helpers
void print_mst(EDGE *mst, int size);
void edge_swap(EDGE *a, EDGE *b);

/******************************************/

//is_cycle helpers
int find_representative(int **vertices_set, int v);
void union_vertices(int **vertices_set, int size, int v1, int v2);

//Kruskal's helpers
int** init_and_fill_vertices_set(int size);
void free_vertices_set(int **vertices_set, int size);

/*****************************************/
GRAPH* init_graph(int vertices, int edges);    // DON'T EDIT THIS LINE
void fill_graph(GRAPH *graph);                 // DON'T EDIT THIS LINE

int is_cycle(int **vertices_set, EDGE edge);
void Kruskals_MST(GRAPH *graph);               // DON'T EDIT THIS LINE

int main() {
	GRAPH *graph = init_graph(10, 14);         // DON'T EDIT THIS LINE
	fill_graph(graph);                         // DON'T EDIT THIS LINE
	Kruskals_MST(graph);                       // DON'T EDIT THIS LINE

	free(graph->edges);
	free(graph);
	return 0;
}

GRAPH* init_graph(int vertices, int edges) {

	GRAPH *graph = calloc(1, sizeof(*graph));  // DON'T EDIT THIS LINE
	if (graph == NULL) {                        // DON'T EDIT THIS LINE
		printf("Cannot allocate memory!");     // DON'T EDIT THIS LINE
		exit(EXIT_FAILURE);                    // DON'T EDIT THIS LINE
	}
	graph->num_vertices = vertices;            // DON'T EDIT THIS LINE
	graph->num_edges = edges;                  // DON'T EDIT THIS LINE
	graph->edges = calloc(edges, sizeof(EDGE));          // DON'T EDIT THIS LINE

	if (graph->edges == NULL) {                  // DON'T EDIT THIS LINE
		printf("Cannot allocate memory!");     // DON'T EDIT THIS LINE
		exit(EXIT_FAILURE);                    // DON'T EDIT THIS LINE
	}
	return graph;                              // DON'T EDIT THIS LINE
}

void fill_graph(GRAPH *graph) {

	graph->edges[0].source = 1;                // DON'T EDIT THIS LINE
	graph->edges[0].destination = 3;           // DON'T EDIT THIS LINE
	graph->edges[0].weight = 12;               // DON'T EDIT THIS LINE

	graph->edges[1].source = 1;                // DON'T EDIT THIS LINE
	graph->edges[1].destination = 2;           // DON'T EDIT THIS LINE
	graph->edges[1].weight = 4;                // DON'T EDIT THIS LINE

	graph->edges[2].source = 2;                // DON'T EDIT THIS LINE
	graph->edges[2].destination = 5;           // DON'T EDIT THIS LINE
	graph->edges[2].weight = 10;               // DON'T EDIT THIS LINE

	graph->edges[3].source = 3;                // DON'T EDIT THIS LINE
	graph->edges[3].destination = 5;           // DON'T EDIT THIS LINE
	graph->edges[3].weight = 2;                // DON'T EDIT THIS LINE

	graph->edges[4].source = 3;                // DON'T EDIT THIS LINE
	graph->edges[4].destination = 4;           // DON'T EDIT THIS LINE
	graph->edges[4].weight = 7;                // DON'T EDIT THIS LINE

	graph->edges[5].source = 4;                // DON'T EDIT THIS LINE
	graph->edges[5].destination = 5;           // DON'T EDIT THIS LINE
	graph->edges[5].weight = 3;                // DON'T EDIT THIS LINE

	graph->edges[6].source = 4;                // DON'T EDIT THIS LINE
	graph->edges[6].destination = 6;           // DON'T EDIT THIS LINE
	graph->edges[6].weight = 8;                // DON'T EDIT THIS LINE

	graph->edges[7].source = 5;                // DON'T EDIT THIS LINE
	graph->edges[7].destination = 6;           // DON'T EDIT THIS LINE
	graph->edges[7].weight = 9;                // DON'T EDIT THIS LINE

	graph->edges[8].source = 6;                // DON'T EDIT THIS LINE
	graph->edges[8].destination = 7;           // DON'T EDIT THIS LINE
	graph->edges[8].weight = 11;               // DON'T EDIT THIS LINE

	graph->edges[9].source = 6;                // DON'T EDIT THIS LINE
	graph->edges[9].destination = 8;           // DON'T EDIT THIS LINE
	graph->edges[9].weight = 1;                // DON'T EDIT THIS LINE

	graph->edges[10].source = 7;               // DON'T EDIT THIS LINE
	graph->edges[10].destination = 8;          // DON'T EDIT THIS LINE
	graph->edges[10].weight = 13;              // DON'T EDIT THIS LINE

	graph->edges[11].source = 7;               // DON'T EDIT THIS LINE
	graph->edges[11].destination = 10;         // DON'T EDIT THIS LINE
	graph->edges[11].weight = 6;               // DON'T EDIT THIS LINE

	graph->edges[12].source = 8;               // DON'T EDIT THIS LINE
	graph->edges[12].destination = 9;          // DON'T EDIT THIS LINE
	graph->edges[12].weight = 5;               // DON'T EDIT THIS LINE

	graph->edges[13].source = 9;               // DON'T EDIT THIS LINE
	graph->edges[13].destination = 10;         // DON'T EDIT THIS LINE
	graph->edges[13].weight = 14;              // DON'T EDIT THIS LINE
}

int is_cycle(int **vertices_set, EDGE edge) {
	int repS = find_representative(vertices_set, edge.source);
	int repD = find_representative(vertices_set, edge.destination);
	return repS == repD ? 1 : 0; //if they are from the same set there exists a cycle
}

int** init_and_fill_vertices_set(int size) {
	int **vertices_set = malloc(sizeof(int*) * size);
	int i;
	for (i = 0; i < size; i++) {
		vertices_set[i] = malloc(sizeof(int) * 2);
		vertices_set[i][0] = i + 1;
		vertices_set[i][1] = i + 1; //in the beginning each item represents itself
	}
	return vertices_set;
}

void free_vertices_set(int **vertices_set, int size) {
	int i;
	for (i = 0; i < size; i++) {
		free(vertices_set[i]);
	}
	free(vertices_set);
}

int find_representative(int **vertices_set, int v) {
	return vertices_set[v - 1][1];
}

void union_vertices(int **vertices_set, int size, int v1, int v2) {
	int i = 0;
	int repV1 = find_representative(vertices_set, v1);
	int repV2 = find_representative(vertices_set, v2);
	//sets all values represented by repV1 to repV2
	for (i = 0; i < size; i++) {
		if (vertices_set[i][1] == repV1)
			vertices_set[i][1] = repV2;
	}
}

void Kruskals_MST(GRAPH *graph) {
	int numEdges = graph->num_edges;
	int numVertices = graph->num_vertices;

	//we are allocating extra arrays so we don't manipulate our current graph
	EDGE *graphEdges = calloc(sizeof(EDGE), numEdges);
	memcpy(graphEdges, graph->edges, sizeof(EDGE) * numEdges);
	int currentEdgeIdx = 0;

	EDGE *mstEdges = calloc(sizeof(EDGE), numEdges);
	int sizeMstEdges = 0;

	//we will take an disjoint set-like approach to vertices
	//we will use an 2d array for this.
	//vertices_set[i][0] always represent the vertex.
	//vertices_set[i][1] always represents the current set's representative
	int **vertices_set = init_and_fill_vertices_set(numVertices);

	heapsort(graphEdges, numEdges);

	while ((sizeMstEdges < numVertices - 1) && currentEdgeIdx < numEdges) {
		EDGE minEdge = graphEdges[currentEdgeIdx]; //find min edge
		currentEdgeIdx++;
		if (is_cycle(vertices_set, minEdge) == 0) { //if it doesnt create a cycle
			mstEdges[sizeMstEdges] = minEdge; //push it into mstEdge array
			sizeMstEdges++;
			//recalibrate representatives
			union_vertices(vertices_set, numVertices, minEdge.source,
					minEdge.destination);
		}
	}

	print_mst(mstEdges, sizeMstEdges); //print mst

	free(graphEdges);
	free(mstEdges);
	free_vertices_set(vertices_set, numVertices);
	return;
}

void edge_swap(EDGE *a, EDGE *b) {
	//Basic int swap
	EDGE tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify_recursive(EDGE *edgeHeap, int idx, int size) {
	//recording indices
	int leftIdx = leftChildIdx(idx);
	int rightIdx = rightChildIdx(idx);
	int largest;

	//if left child doesn't overflow and smaller than our start IDX
	if (leftIdx < size && edgeHeap[leftIdx].weight > edgeHeap[idx].weight) {
		largest = leftIdx; //largest is left child
	} else { //else largest is start IDX
		largest = idx;
	}

	//if right child doesn't overflow and smaller than our largest
	if (rightIdx < size
			&& edgeHeap[rightIdx].weight > edgeHeap[largest].weight) {
		largest = rightIdx; //largest is right child
	}

	if (largest != idx) { //if largest is not our given IDX
		//We need to perform a swap with the largest
		edge_swap(&edgeHeap[idx], &edgeHeap[largest]);
		//Then call this function recursively
		heapify_recursive(edgeHeap, largest, size);
	}

	//If our largest is equal to given idx
	//we terminate the current recursive call
}

void heapify_array(EDGE *edgeArr, int size) {
	int i; //to heapify an array it is enough to traverse half of it
	for (i = (size / 2) - 1; i >= 0; i--) {
		heapify_recursive(edgeArr, i, size);
		//starting from (size/2) - 1, we rebalance tree iteratively
	}
}

void heapsort(EDGE *edgeArr, int size) {
	heapify_array(edgeArr, size); // first build an heap from array
	int i;
	for (i = size - 1; i > 0; i--) { //for each element
		edge_swap(&edgeArr[0], &edgeArr[i]); //swap it with max
		heapify_recursive(edgeArr, 0, i - 1); //rebalance heap so max stays at idx 0
	}
}

void print_mst(EDGE *mst, int size) {
	//pretty printer with basic loop
	int i;
	printf("MST: \n");
	for (i = 0; i < size; i++)
		printf("%d <----(%d)---> %d\n", mst[i].source, mst[i].weight,
				mst[i].destination);
	printf("\n");
}
