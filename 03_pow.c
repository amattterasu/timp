#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
	int x, y;

	scanf("%d%d", &x, &y);

	if(pow(x, y) > INT_MAX || pow(x, y) < INT_MIN) {

		printf("%s\n", "Out of range!");

	} else printf("%f\n", pow(x, y));

	return 0;
}