#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	int N, x, sum = 0;
	scanf("%d", &N);

	for(int i = 0; i < N; i++) {

		scanf("%d", &x);
		sum += pow(x, 2);
	}

	printf("%d\n", sum);

	return 0;
}