/* for dijkstra*/
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
 
    printPath(parent, parent[j]);
    printf("%d ", j + 1);
}

void printSolution(int dist[], int n, int parent[]) {
    int src = 0;
    printf("Vertex\t\t Distance\tPath");

    for (int i = 1; i < n ; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src + 1, i + 1, dist[i], src + 1);
        printPath(parent, i);
    }
    printf("\n");
}

/* for tsp*/
void swap(char *a, char *b) {
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}