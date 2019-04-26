#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int combSort(int *array, int size) {
    
    if (array && size) {
        int step = size;
        int count = 0;
        int i;

        while (step > 1) {
            step /= 1.24733;

            for (i = 0; i + step < size; ++i) {
                
                if (array[i + step] < array[i]) {
                    int tmp;
                    tmp = array[i];
                    array[i] = array[i + step];
                    array[i + step] = tmp;
                    count +=2;
                } else count++;
            }
        }
        return count;
    }
}

int main(int argc, char const *argv[])
{
    int npoints, i, count = 0;
    scanf("%d", &npoints);

    int *arr = (int *)malloc(sizeof(int) * npoints);
        
    srand(time(NULL));
    for (i = 0; i < npoints; i++) {
         arr[i] = 0 + rand() %999;
    }

    /*for (i = 0; i < npoints; i++) {
        scanf("%d", &arr[i]);
    }*/

    count = combSort(arr, npoints);
    printf("%d\n", count);

    for (i = 0; i < npoints; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    printf("%d\n", count);
    free(arr);

    return 0;
}