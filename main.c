#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./sort/combSort.h"
#include "./sort/shellSort.h"
#include "./sort/qkSort.h"
#include "./sort/heapSort.h"

#define AMOUNT_ARR 1000
#define LENGTHS_ARR 15
#define ELEM 100

double getTime(int(*callback)(int *, int), int *array, int size) {
	double t1 = clock();
	callback(array, size);
	double t2 = clock();
	double t3 = (t2 - t1) / CLOCKS_PER_SEC;

	return t3;
}

double getTimeQS(int(*callback)(int *, int, int), int *array, int size) {
	double t1 = clock();
	callback(array, 0, size - 1);
	double t2 = clock();
	double t3 = (t2 - t1) / CLOCKS_PER_SEC;

	return t3;
}

int getAmountOperations(int (*callback)(int *, int), int *array, int size) {

	return callback(array, size);
}

int getAmountOperationsQS(int (*callback)(int *, int, int), int *array, int size) {

	return callback(array, 0, size - 1);
}

void getRusults(int (*callback)(int *, int), const char *nameSort, int access,
				int (*callbackQS)(int *, int, int)) {
    int i, j, k;

    double t = 0;
    unsigned long long count = 0;

    double boxArrayTime[LENGTHS_ARR];
    unsigned long long boxCountOperations[LENGTHS_ARR];

    double boxArrayTime1[LENGTHS_ARR];
    unsigned long long boxCountOperations1[LENGTHS_ARR];

    int lengthsArrays [LENGTHS_ARR] = { 1, 2, 3, 4, 5,
                            10, 15, 20, 25, 30, 50, 75,
                            100, 250, 500 };

    double boxBestArr[LENGTHS_ARR], boxWorstArr[LENGTHS_ARR];


    for (i = 0; i < LENGTHS_ARR; i++) {

        t = count = 0;

        for (j = 0; j < AMOUNT_ARR; j++) {

            int *arr = (int *)malloc(sizeof(int) * lengthsArrays[i]);
            int *copyArr = (int *)malloc(sizeof(int) * lengthsArrays[i]);

            srand(time(NULL));
            for (k = 0; k < lengthsArrays[i]; k++) {
                arr[k] = 0 + rand() %999;
            }
            memcpy(copyArr, arr, lengthsArrays[i] * 4);

            if (access) {
				t += getTime(callback, arr, lengthsArrays[i]);
				count += getAmountOperations(callback, copyArr, lengthsArrays[i]);
            } else {
            	t += getTimeQS(callbackQS, arr, lengthsArrays[i]);
    			count += getAmountOperationsQS(callbackQS, copyArr, lengthsArrays[i]);
            }

            free(arr);
            free(copyArr);

        }

/*   Average values   */
        t = t / AMOUNT_ARR;
        count = count / AMOUNT_ARR;

/*  Container for average values  */
        boxArrayTime[i] = t;
        boxCountOperations[i] = count;

        int *bestTime = malloc(sizeof(int) * lengthsArrays[i]);
        int *worstTime = malloc(sizeof(int) * lengthsArrays[i]);

        for (j = 0; j < lengthsArrays[i]; j++){
            bestTime[j] = j;
            worstTime[j] = lengthsArrays[i] - j;
        }

        if (access) {
	        boxBestArr[i] = getTime(callback, bestTime, lengthsArrays[i]);
	        boxWorstArr[i] = getTime(callback, worstTime, lengthsArrays[i]);
        } else {
        	boxBestArr[i] = getTimeQS(callbackQS, bestTime, lengthsArrays[i]);
        	boxWorstArr[i] = getTimeQS(callbackQS, worstTime, lengthsArrays[i]);
        }

        free(bestTime);
        free(worstTime);
    }

    printf("%s %s\n","\t\t\t\t\t", nameSort);

    for (i = 0; i < LENGTHS_ARR; i++) {
    	puts("-------------------------------------"
        	"--------------------------------------"
        	"-------------------------------------"
        	"--------------------------------------");
    	printf("%d -> ", lengthsArrays[i]);
        printf("%s %f %s %llu %s %f %s %f\n", 
        	"\t | \tAverage time = ", boxArrayTime[i], 
        	"\t | \tAverage operations = ", boxCountOperations[i],
        	"\t | \tBest time = ", boxBestArr[i],
        	"\t | \tWorst time = ", boxWorstArr[i]);

    }
	puts("-------------------------------------"
        	"--------------------------------------"
        	"-------------------------------------"
        	"--------------------------------------");

    printf("\n\n");
}

int main(int argc, char const *argv[])
{	
	const char *nameSort[4];
	nameSort[0] = "\t\t<!-- \t COMB SORT \t -->";
	nameSort[1] = "\t\t<!-- \t SHELL SORT \t -->";
	nameSort[2] = "\t\t<!--\t QUICK SORT \t-->";
	nameSort[3] = "\t\t<!--\t HEAP SORT \t-->";
	
	//Crutches
	getRusults(combSort, nameSort[0], 1, qkSort);
	getRusults(shellSort, nameSort[1], 1, qkSort);
	getRusults(combSort, nameSort[2], 0, qkSort);
	getRusults(heapSort, nameSort[3], 1, qkSort);

	return 0;
}