#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int shellSort(int *arr, int size) {

    int i, j, step, tmp, count = 0;

    for (step = size / 2; step > 0; step = step / 2) { 
        for (i = step; i < size; i++) { 

            tmp = arr[i];

            for (j = i; j >= step; j -= step) {
                
                count++;
                if (tmp < arr[j - step]) {
                    count++;
                    arr[j] = arr[j - step];
                } else break;
            }
            arr[j] = tmp;
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int npoints, i, count = 0;
    scanf("%d", &npoints);

    int *arr = (int *)malloc(sizeof(int) * npoints);
    
    /*srand(time(NULL));
    for (i = 0; i < npoints; i++) {
         arr[i] = 0 + rand() %999;
    }*/
    
    for (i = 0; i < npoints; i++) {
        scanf("%d", &arr[i]);
    }

    count = shellSort(arr, npoints);

    for (i = 0; i < npoints; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    printf("%d\n", count);
    free(arr);

    return 0;
}