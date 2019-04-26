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