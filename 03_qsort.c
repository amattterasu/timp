#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int qkSort(int *arr, int l, int r) {

    int x = arr[l + (r - l) / 2], i = l, j = r, tmp, count = 0;

    if (l < r) {

        do {
            while(arr[i] < x) { i++; };
            while(arr[j] > x) { j--; };

            count++;
            if (i <= j) {  
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;

                i++;
                j--;

                count ++;
            }

        } while(i <= j);

        count += qkSort(arr, i, r);
        count += qkSort(arr, l, j);
    }
    
    return count;
}

int main(int argc, char const *argv[]) 
{
	int npoints, i, count;
	int *arr = malloc(sizeof(int) * npoints);

	scanf("%d", &npoints);

    /*srand(time(NULL));
    for (i = 0; i < npoints; i++) {
         arr[i] = 0 + rand() %999;
    }*/
	for(i = 0; i < npoints; i++)
        scanf("%d", &arr[i]);

	count = qkSort(arr, 0, npoints - 1);

	for(i = 0; i < npoints; i++)
		printf("%d ", arr[i]);

	printf("\n");
    printf("%d\n", count);
	free(arr);

	return 0;
}