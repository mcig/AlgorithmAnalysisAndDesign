/*
 int triple_max(int a, int b, int c) {
 // a is max: -1
 // b is max: 0
 // c is max: 1
 int res = 0;
 if (a > b) {
 if (a > c)
 res = -1;
 else
 res = 1;
 } else if (b > c)
 res = 0;
 else
 res = 1;
 return res;
 }

 void heapify_top_down(int *heap, int size) {
 int idx = 0;
 if (size <= 2) {
 if (heap[idx] < heap[leftChildIdx(idx)])
 int_swap(&heap[idx], &heap[leftChildIdx(idx)]);
 return;
 }

 int max = triple_max(heap[leftChildIdx(idx)], heap[idx],
 heap[rightChildIdx(idx)]);

 while (max != 0) {
 if (max == -1) {
 int_swap(&heap[idx], &heap[leftChildIdx(idx)]);
 idx = leftChildIdx(idx);
 } else {
 int_swap(&heap[idx], &heap[rightChildIdx(idx)]);
 idx = rightChildIdx(idx);
 }
 if (leftChildIdx(idx) >= size)
 break;
 max = triple_max(heap[leftChildIdx(idx)], heap[idx],
 heap[rightChildIdx(idx)]);
 }
 }

 void insert_into_heap(int *heap, int key, int *size, int *cap) {
 if (*size == *cap) {
 *cap *= 2;
 heap = (int*) realloc(heap, sizeof(int) * (*cap));
 }

 heap[*size] = key;
 heapify_bottom_up(heap, *size);

 *size += 1;
 printf("INS ");
 print_heap(heap, *size);
 }

 int delete_from_heap(int *heap, int *size) {
 if (*size <= 0)
 return -1;

 int deletedVal = heap[0];
 int_swap(&heap[0], &heap[*size - 1]);
 *size -= 1;
 if (*size > 1)
 heapify_top_down(heap, *size);

 printf("DEL ");
 print_heap(heap, *size);
 return deletedVal;
 }

 void heapify_bottom_up(int *heap, int childIdx) {
 while (heap[parentIdx(childIdx)] < heap[childIdx]) {
 //Swap values
 int_swap(&heap[childIdx], &heap[parentIdx(childIdx)]);
 //new idx = parents index
 childIdx = parentIdx(childIdx);
 }
 }

 void insert_into_heap(int *heap, int key, int *size, int *cap);
 int delete_from_heap(int *heap, int *size);
 int triple_max(int a, int b, int c);
 void heapify_bottom_up(int *heap, int idx);
 void heapify_top_down(int *heap, int size);
 */
/*
 int size = 0, cap = 10;

 int *maxHeap = (int*) malloc(sizeof(int) * cap);
 insert_into_heap(maxHeap, 1, &size, &cap);
 insert_into_heap(maxHeap, 142, &size, &cap);
 insert_into_heap(maxHeap, 13, &size, &cap);
 insert_into_heap(maxHeap, 6, &size, &cap);
 printf("******************\n");
 delete_from_heap(maxHeap, &size);
 delete_from_heap(maxHeap, &size);
 delete_from_heap(maxHeap, &size);
 insert_into_heap(maxHeap, 6, &size, &cap);
 insert_into_heap(maxHeap, 64, &size, &cap);
 insert_into_heap(maxHeap, 6111, &size, &cap);
 delete_from_heap(maxHeap, &size);
 delete_from_heap(maxHeap, &size);
 free(maxHeap);
 */
