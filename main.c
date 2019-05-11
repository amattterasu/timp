#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "./source/graph.h"
#include "./source/heap.h"
#include "./source/foo.h"
#define SIZE 10
#define LENGTH 100

/* <!--          Solution of the first task          --> */
void Dijkstra (Graph* graph, int src) {
	int V = graph->V;
	int dist[V];	 

	minHeap* minHeap = createMinHeap(V);
    int flag[V];

	for (int v = 0; v < V; ++v) {
		flag[0] = -1;
		dist[v] = INT_MAX;
		minHeap->arr[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	minHeap->arr[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	minHeap->size = V;
	// dist
	while (!isEmpty(minHeap)) {

		minHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; 

		AdjListNode* out = graph->arr[u].head;
		// way
		while (out != NULL) {
			int v = out->res;

			if (isMinHeap(minHeap, v) && dist[u] != INT_MAX && out->weight + dist[u] < dist[v]) {
				flag[v]  = u;
				dist[v] = dist[u] + out->weight;

				decreaseKey(minHeap, v, dist[v]);
			}
			out = out->next;
		}
	}

	printSolution(dist, V, flag);
}

/* <!--          Solution of the second task          --> */
int TSP (char *str, int l, int r, int arr[][SIZE], int n, int min, char path[]) {
	int i;

	if (l == r) {
		int z, totalPath = 0;

		for (z = 1; str[z] != '\0'; z++)
			totalPath += arr[str[z - 1] - '0'][str[z] - '0'];

		totalPath += arr[str[z - 1] - '0'][str[0] - '0'];

		if (totalPath < min) { 
			min = totalPath;

			for (i = 0; i < n; i++)
				path[i] = str[i];
		}

	} else {

		for (i = l; i <= r; i++) {
			swap((str + l), (str + i));
			min = TSP(str, l + 1, r, arr, n, min, path);
			swap((str + l), (str + i));
		}
	}
	return min;
}

int main(int argc, char const *argv[])
{	
	printf("%s\n", "\n\t\t<!--        Solution of the first task (Dijkstra)     -->");

	int V, edge;
	printf("Enter no of tops: ");
	scanf("%d", &V);

	printf("Enter no of edges: ");
	scanf("%d", &edge);

	int from[edge], to[edge], weight[edge];

	Graph* graph = createGraph(V);

	printf("Enter directions and weights (format 'from -> to -> weight'):\n");
	for (int i = 0; i < edge; i++) {
		scanf("%d%d%d", &from[i], &to[i], &weight[i]);
		addEdge(graph, from[i] - 1, to[i] - 1, weight[i]);
	}
	printf("\n");
	
	Dijkstra(graph, 0);

	/* -------------------------------------------------------------*/

	printf("%s\n", "\n\t\t<!--        Solution of the second task (TSP)     -->");

	int arr[SIZE][SIZE];
	int i, j = 1, n, min = 10000;

	char path[LENGTH], str[LENGTH];

	printf("Enter no of tops: ");
	scanf("%d", &n);

	str[0] = '0'; //48 - 52 = 5++ (+1)
	for (i = 1; i < n; i++) {

		if ('0' + j - 1 == '0') {
			j++;
			i--;
			continue;
		}
		str[i] = '0' + j - 1;
		j++;
	}

	printf("Enter adjacency matrix (Distance to yourself = 10000):\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);

	int num = strlen(str);
	min = TSP(str, 1, num - 1, arr, n, min, path);

	printf("\nThe shortest path is: %d\n", min);

	printf("Path: ");
	for (i = 0; i < n; i++)
		printf("%d->", path[i] - '0' + 1);
	printf("%d\n", path[0] - '0' + 1);

	return 0;
}
