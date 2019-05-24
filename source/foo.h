void inputMatrixDijkstra(int nNode, int start, 
        int visited[nNode], int parent[nNode], int distance[nNode], int arrWeight[][nNode]) {

    printf("Input the matrix (0 to yourself, 999999 if not connected)\n");
    for (int i = 0; i < nNode; i++) {

        for (int j = 0; j < nNode; j++) {

            if (i == j) {
                arrWeight[i][j] = 0;
                continue;
            }
            printf("%d ->> %d  ", i + 1, j + 1);
            scanf("%d", &arrWeight[i][j]);
        }
    }       

    printf("Input starting index, between 1 and %d\n", nNode);
    scanf("%d", &start);
    start--;

    if (start < 0 || start > nNode - 1) {
        printf("ERROR incorrect starting vertex number\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nNode; i++) {
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = MAX;
    }

    distance[start] = 0;
}

int inputMatrixTSP(int matrix[][SIZE], int done[SIZE]) {
    int i, j, n;

    printf("Input the no of villages: ");
    scanf("%d", &n);

    printf("\nInput the path Matrix");

    for (i = 0; i < n; i++) {

        printf("\nInput row of Matrix: %d\n", i + 1);

        for (j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

        done[i] = 0;
    }

    return n;
}

void swap(char *a, char *b) {
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}