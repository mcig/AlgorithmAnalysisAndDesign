#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5 // Number of nodes

typedef struct {
    int top, capacity; // DO NOT EDIT THIS LINE
    int *array;        // DO NOT EDIT THIS LINE
}STACK;

int GRAPH[N][N] = {
        /*       A   B   C   D   E   F   G   H   I   J  */
        /*A*/  { 0,  1,  1,  1,  0},    // EDIT THIS LINE
        /*B*/  { 0,  0,  1,  0,  0},    // EDIT THIS LINE
        /*C*/  { 0,  0,  0,  0,  1},    // EDIT THIS LINE
        /*D*/  { 0,  0,  0,  0,  1},    // EDIT THIS LINE
        /*E*/  { 0,  0,  0,  0,  0},    // EDIT THIS LINE

};

STACK *init_stack(int capacity);
void push(STACK *stack, int item);
int pop(STACK *stack);
int peek(STACK *stack);
int isFull(STACK *stack);
int isEmpty(STACK *stack);

void perform_topological_sort();
void topological_sort(int node,STACK *stack,int *visitedFlags);

int main() {
    perform_topological_sort();
    return 0;
}

STACK *init_stack(int capacity) {
    STACK *stack = calloc(1, sizeof(*stack));
    if(stack == NULL){
        printf("Error:");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)calloc(1, stack->capacity * sizeof(int));
    return stack;
}

int isFull(STACK *stack){ return stack->top == stack->capacity - 1; }

int isEmpty(STACK *stack){ return stack->top == -1; }

void push(STACK *stack, int item){
    if(isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(STACK *stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

int peek(STACK *stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top];
}

void topological_sort(int node,STACK *stack,int *visitedFlags) {
    visitedFlags[node] = 1;
    int i;
    for(i=0;i<N;i++){
    	if(GRAPH[node][i] == 1 && visitedFlags[i] == 0)//if there is an edge and node is not visited yet
    		topological_sort(i,stack,visitedFlags);
    }
	push(stack,node);
}

void perform_topological_sort() {
    STACK *stack = init_stack(N);
    int *visitedFlags = calloc(N, sizeof(int));//sets arr to all 0's
    int i;
    for(i=0;i<N;i++){
    	if(visitedFlags[i] == 0)
    		topological_sort(i,stack,visitedFlags);
    }

    char arr[N] = "ABCDE";//for prettier printing
    while(peek(stack) != -1){
    	int node = pop(stack);
    	printf("%c(%d) ",arr[node],node);
    }

    free(stack->array);
    free(stack);
    free(visitedFlags);
}
// EDIT THIS LINE
