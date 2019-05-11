typedef struct adjlistnode {
	int res;
	int weight;
	struct adjlistnode* next;
} AdjListNode;

typedef struct adjlist {
	AdjListNode *head; 
} AdjList;

typedef struct graph {
	int V;
	AdjList* arr;
} Graph;

AdjListNode* getFreeAdjListNode(int res, int weight) {
	AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
	newNode->res = res;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

Graph* createGraph(int V) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->V = V;
	graph->arr = (AdjList*) malloc(V * sizeof(AdjList));

	for (int i = 0; i < V; ++i)
		graph->arr[i].head = NULL;

	return graph;
}

void addEdge(Graph* graph, int src, int res, int weight) {
	AdjListNode* newNode = getFreeAdjListNode(res, weight);
	
	newNode->next = graph->arr[src].head;
	graph->arr[src].head = newNode;

	newNode = getFreeAdjListNode(src, weight);
	newNode->next = graph->arr[res].head;
	graph->arr[res].head = newNode;
}