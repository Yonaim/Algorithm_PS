/*

*/

#include <stdio.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

int main()
{
	int N;

	scanf("%d", &N);
	printf("%d", f(N));
}