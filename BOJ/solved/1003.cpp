#include <stdio.h>
#include <string.h>

const int MaxN = 40;
int N;
int dp[MaxN + 1][2];

void f(int n)
{
	if (n == 0 || n == 1)
		return ;
	
	if (dp[n - 1][0] == -1)
		f(n - 1);
	if (dp[n - 2][0] == -1)
		f(n - 2);
	dp[n][0] = dp[n - 1][0] + dp[n - 2][0];
	dp[n][1] = dp[n - 1][1] + dp[n - 2][1];
}

int main()
{
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 1;
	dp[0][1] = 0;
	dp[1][0] = 0;
	dp[1][1] = 1;
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &N);
		f(N);
		printf("%d %d\n", dp[N][0], dp[N][1]);
	}
}