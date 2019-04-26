int shellSort(int *arr, int size) {

    int i, j, step, tmp, count = 0;

    for (step = size / 2; step > 0; step = step / 2) { 
        for (i = step; i < size; i++) { 

            tmp = arr[i];

            for (j = i; j >= step; j -= step) {

                if (tmp < arr[j - step]) {
                    count++;
                    arr[j] = arr[j - step];
                } else break;
                count++;
            }
            arr[j] = tmp;
        }
    }
    return count;
}