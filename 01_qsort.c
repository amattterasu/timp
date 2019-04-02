#include <stdio.h>
#include <stdlib.h>

int qkSort(int *arr, int first, int last) {

	int f = first, l = last, m, count;
	m = arr[first];
	double x = arr[(first + last) / 2];

	do {
        while(arr[f] < x) f++;
        while(arr[l] > x) l--;

        if(f < l) {
            if(arr[f] > arr[l])
            
            m = arr[f];
            arr[f] = arr[l];
            arr[l] = m;
        }

        f++;
        l--;
    } while(f < l);

    if (f < last)
    	qkSort(arr, f, last);
    if(first < l)
   		qkSort(arr, first, l);

   	return 0;
}

int main(int argc, char const *argv[]) 
{
	int npoints, i, count;
	int *arr = malloc(sizeof(int) * npoints);

	scanf("%d", &npoints);

	for(i = 0; i < npoints; i++)
        scanf("%d", &arr[i]);

	count = qkSort(arr, 0, npoints - 1);

	for(i = 0; i < npoints; i++)
		printf("%d ", arr[i]);

	printf("\n");
	free(arr);

	return 0;
}