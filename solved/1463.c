
#include <stdio.h>
#include <math.h>
#include <limits.h>
 

#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define MAX_N 1000000
int dp[MAX_N + 1] = {0, };

// Top-Down

// int to_one(int n)
// {
// 	if (n == 1)
// 		return (0);
// 	if (dp[n] != 0)
// 		return (dp[n]);

// 	int tmp = to_one(n - 1) + 1;
// 	if (n % 3 == 0)
// 		tmp = min(to_one(n / 3) + 1, tmp);
// 	if (n % 2 == 0)
// 		tmp = min(to_one(n / 2) + 1, tmp);
// 	dp[n] = tmp;
// 	return (dp[n]);
// }

// Bottom-Up

int to_one(int n)
{
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + 1;
		if (i % 3 == 0)
			dp[i] = min(dp[i / 3] + 1, dp[i]);
		if (i % 2 == 0)
			dp[i] = min(dp[i / 2] + 1, dp[i]);
	}
	return (dp[n]);
}

int main()
{
    int N;
    scanf("%d", &N);
    printf("%d\n", to_one(N));
}

/*
to_one(n - 1) + 1 그리고 to_one(n - 2) + 2를 비교해야하지 않나 싶었다.
근데 to_one(n - 1) + 1에서 이미 to_one(n - 2) + 2를 구하고 있었다. 
(n - 1을 인자로 넣어 호출 할때, 해당 호출시의 to_one(n - 1) + 1이 결국 원래 호출의 to_one(n - 2) + 2이다.
*/