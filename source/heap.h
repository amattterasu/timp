typedef struct minheapnode {
	int v;
	int dist;
} minHeapNode;

typedef struct minHeap {
	int size;	 
	int capacity; 
	int *pos;	 
	minHeapNode **arr;
} minHeap;

minHeapNode* newMinHeapNode(int v, int dist) {
	minHeapNode* HeapNode = (minHeapNode*) malloc(sizeof(minHeapNode));
	HeapNode->v = v;
	HeapNode->dist = dist;
	return HeapNode;
}

minHeap* createMinHeap(int capacity) {
	minHeap* MinHeap = (minHeap*) malloc(sizeof(minHeap));
	MinHeap->pos = (int *)malloc(capacity * sizeof(int));
	MinHeap->size = 0;
	MinHeap->capacity = capacity;
	MinHeap->arr = (minHeapNode**) malloc(capacity * sizeof(minHeapNode*));
	return MinHeap;
}

void swapMinHeapNode(minHeapNode** a, minHeapNode** b) {
	minHeapNode* tmp = *a;
	*a = *b;
	*b = tmp;
}

void minHeapify(minHeap* minHeap, int id) {
	int smallest, left, right;
	smallest = id;
	left = 2 * id + 1;
	right = 2 * id + 2;

	if (left < minHeap->size &&
		minHeap->arr[left]->dist < minHeap->arr[smallest]->dist)
	smallest = left;

	if (right < minHeap->size &&
		minHeap->arr[right]->dist < minHeap->arr[smallest]->dist)
	smallest = right;

	if (smallest != id) {
		minHeapNode *smallestNode = minHeap->arr[smallest];
		minHeapNode *idNode = minHeap->arr[id];

		minHeap->pos[smallestNode->v] = id;
		minHeap->pos[idNode->v] = smallest;

		swapMinHeapNode(&minHeap->arr[smallest], &minHeap->arr[id]);

		minHeapify(minHeap, smallest);
	}
}

int isEmpty(minHeap* minHeap) {
	return minHeap->size == 0;
}

minHeapNode* extractMin(minHeap* minHeap) {
	if (isEmpty(minHeap))
		return NULL;

	minHeapNode* root = minHeap->arr[0];

	minHeapNode* lastNode = minHeap->arr[minHeap->size - 1];
	minHeap->arr[0] = lastNode;

	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

void decreaseKey(minHeap* minHeap, int v, int dist) {
	int i = minHeap->pos[v];

	minHeap->arr[i]->dist = dist;

	while (i && minHeap->arr[i]->dist < minHeap->arr[(i - 1) / 2]->dist) {
		minHeap->pos[minHeap->arr[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->arr[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

bool isMinHeap(minHeap *minHeap, int v) {
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}