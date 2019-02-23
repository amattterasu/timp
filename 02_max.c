#include <stdio.h>

int main(int argc, char const *argv[])
{
	int N, x, max = 0;
	scanf("%d", &N);

	for(int i = 0; i < N; i++) {

		scanf("%d", &x);

		if (x > max) max = x;
	}

	printf("%d\n", max);

	return 0;
}