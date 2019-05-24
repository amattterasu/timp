#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#define MAX 999999
#define SIZE 10
#define INF 999
#define LENGTH 100
#include "./source/foo.h"

/* <!--          Solution of the first task          --> */
void Dijkstra (int nNode, int current, int* visited, 
                            int* parent, int *distance, int arrWeight[][nNode]) {
    visited[current] = 1;

    for (int i = 0; i < nNode; i++) {

        if (arrWeight[current][i] == MAX) continue;

        int newDist = distance[current] + arrWeight[current][i];

        if (newDist < distance[i]) {
            distance[i] = newDist;
            parent[i] = current;
        }
    }
    
    int min = MAX;
    int minIndex;

    for (int i = 0; i < nNode; i++) {

        if (visited[i]) continue;

        if (distance[i] < min) {
            min = distance[i];
            minIndex = i;
        }
    }

    if (min == MAX) return;
    
    Dijkstra(nNode, minIndex, visited, parent, distance, arrWeight);
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
    /* <!--       Dijkstra      -->*/
    int nNode, start;
    printf("Input the number of nodes: ");
    scanf("%d", &nNode);
    int arrWeight[nNode][nNode];
    int visited[nNode], parent[nNode], distance[nNode];

    inputMatrixDijkstra(nNode, start, visited, parent, distance, arrWeight);

    Dijkstra(nNode, start, visited, parent, distance, arrWeight);

    /* <!--      Print Dijkstra      -->*/
    printf("\nPath FROM %d TO:\n\t", start + 1);
    for (int i = 0; i < nNode; i++) {

        if (i == start) {
            printf("%d: not applicable\n", i + 1);
            continue;
        }

        int current = i;

        int path[nNode];
        int num = nNode - 1;
        for (int j = 0; j < nNode; j++) {
            path[j] = -1;
        }

        while (current > -1) {
            path[num--] = current;
            current = parent[current];
        }

        printf("\t%d: ", i + 1);
        for (int j = 0; j < nNode; j++) {

            if (path[j] == -1) continue;
            printf("%d", path[j] + 1);
            if (j + 1 != nNode) printf("->");
        }
        printf("\t\t\tDistance: %d\n", distance[i]);
    }

    /* <!--       Travelling Salesman Problem       -->*/

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

    printf("Enter adjacency matrix (10000 to yourself, 10000 if not connected):\n");
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