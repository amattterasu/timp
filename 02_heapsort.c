#include <stdio.h>
#include <stdlib.h>

void swap (int *array, int a, int b) {
    int temp = *(array + a);
    *(array + a) = *(array + b);
    *(array + b) = temp; 
}

void Heapify(int *array, int index, int heapSize) {

    while (1) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int max = *(array + index);
        int maxPosition = index;

        if (left < heapSize && *(array + left) > max) {
            max = *(array + left);
            maxPosition = left;
        }
        if (right<heapSize && *(array + right)>max) {
            max = *(array + right);
            maxPosition = right;
        }

        if (maxPosition != index) {
            swap(array, index, maxPosition);
            index = maxPosition;
        }
        else break;
    }
}

int heapSort(int *array, int size) {
    
    /*   Создание кучи   */
    int p = size / 2 - 1, i;

    for (int i = p; i >= 0; i--)
        Heapify(array, i, size);
    /*                    */

    for (int i = size - 1; i > 0; i--) {
        swap(array, 0, i);
        Heapify(array, 0, i);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int npoints, i, count;
    int *arr = malloc(sizeof(int) * npoints);

    scanf("%d", &npoints);

    for (i = 0; i < npoints; i++)
        scanf("%d", &arr[i]);

     count = heapSort(arr, npoints);

    for (i = 0; i < npoints; i++)
        printf("%d ", arr[i]);

    printf("\n");
    free(arr);

    return 0;
}
