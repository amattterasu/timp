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