
#include <stdio.h>

#define MAX_N 90
long long dp[MAX_N + 1] = {0, };

long long fibonacci(int n)
{
	if (n == 0)
		return (0);
	else if (n == 1)
		return (1);
	if (dp[n] != 0)
		return (dp[n]);
	dp[n] = fibonacci(n - 1) + fibonacci(n - 2);
	return (dp[n]);
}


int main()
{
    int N;
    scanf("%d", &N);
    printf("%lld\n", fibonacci(N));
}
