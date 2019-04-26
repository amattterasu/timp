#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Heapify(int *arr, int root, int bottom) {
    int index, success = 0, count = 0;

    while ((root * 2 <= bottom) && (!success)) {

        if (root * 2 == bottom) 
            index = root * 2;   
        else if (arr[root * 2] > arr[root * 2 + 1])
            index = root * 2;
        else index = root * 2 + 1;

        count++;
        if (arr[root] < arr[index]) {
            int temp = arr[root];
            arr[root] = arr[index];
            arr[index] = temp;
            root = index;
            count++;
        } else success = 1; 
    }

    return count;
}

int heapSort(int *arr, int size) {
    int count = 0;

    for (int i = (size / 2) - 1; i >= 0; i--)
        count += Heapify(arr, i, size - 1);

    for (int i = size - 1; i >= 1; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        count += Heapify(arr, 0, i - 1);
        count++;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int npoints, i, count;
    int *arr = malloc(sizeof(int) * npoints);

    scanf("%d", &npoints);

    srand(time(NULL));
    for (i = 0; i < npoints; i++) {
         arr[i] = 0 + rand() %999;
    }

    /*for (i = 0; i < npoints; i++)
        scanf("%d", &arr[i])*/;

    count = heapSort(arr, npoints);

    for (i = 0; i < npoints; i++)
        printf("%d ", arr[i]);

    printf("\n");
    printf("%d\n", count);
    free(arr);

    return 0;
}
