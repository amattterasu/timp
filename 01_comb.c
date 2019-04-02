#include <stdio.h>
#include <stdlib.h>

int combSort(int *array, int size) {
    if (array && size) {
        int step = size;
        int swapped = 1;
        int count, i;

        while (step > 1 || swapped) {
            if (step > 1)
                step /= 1.24733;
            swapped = 0;

            for (i = 0; i + step < size; ++i) {
                if (array[i + step] < array[i]) {
                    int tmp;
                    tmp = array[i];
                    array[i] = array[i + step];
                    array[i + step] = tmp;
                    swapped = 1;
             
                    count++;
                }
            }
        }
        return count;
    }
}

int main(int argc, char const *argv[])
{
    int npoints, i, count; //count - количество перестановок, их функция возвращает
    scanf("%d", &npoints);

    int *arr = (int*)malloc(sizeof(int)*npoints);
    
    for (i = 0; i < npoints; i++) {
        scanf("%d", &arr[i]);
    }

    count = combSort(arr, npoints);

    for (i = 0; i < npoints; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    free(arr);

    return 0;
}