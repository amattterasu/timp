#include <stdio.h>
#include <stdlib.h>

int shellSort(int *arr, int size){

    int i, j, z, gap, count;

    for (gap = size / 2; gap > 0; gap = gap / 2) { /*   Размер шага   */
        for (i = 0; i < gap; i++) { 

            /*   Запуск сортировки вставками   */
            for (j = i + gap; j < size; j = j + gap) {
                if (arr[j] < arr[j - gap]) {

                    /*   Сохранение значений   */
                    int tmp = arr[j];

                    for (z = j - gap; z >= 0 && arr[z] > tmp; z = z - gap) {
                        arr[z + gap] = arr[z];
                    }
                    arr[z + gap] = tmp;
                    count++;
                }
            }
            count++;
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int npoints, i, count;
    scanf("%d", &npoints);

    int *arr = (int*)malloc(sizeof(int)*npoints);
    
    for (i = 0; i < npoints; i++) {
        scanf("%d", &arr[i]);
    }

    count = shellSort(arr, npoints);

    for (i = 0; i < npoints; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    free(arr);

    return 0;
}