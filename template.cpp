#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*

*/

const int MaxN = 100000;
int N;

int main()
{
	scanf("%d", &N);
	printf("%d", f(N));
}