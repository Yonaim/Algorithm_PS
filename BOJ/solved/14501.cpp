#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*
선택지는 두 가지.
이 날 상담을 하거나 or 상담을 하지 않거나. (물론 상담을 했을 경우는 남은 기간이 줄어들게 된다)
모든 경우를 살핀다. 재귀호출.
며칠까지 고려했는지, 현재 남은 날짜에 따른 최대 이익을 저장해두면 재사용할 수 있을까?
	-> 1일이 남았을 때 최대의 이익을 2일이 남았을 때 혹은 3일이 남았을 때...가 재사용할 수 있다.
	-> Top-down dp.

g(n): n일이 남았을 때 최대의 이익

맨 처음 호출 g(N).

base case: n = 0 -> 0

g(n) = 
		g(n - T[n]) + P[n] (n >= T[n] 일때만 가능) 혹은
		g(n - 1)
		둘 중 더 큰값.
*/

const int MaxN = 15;
int N;
int dp[MaxN + 1];
int T[MaxN + 1];
int P[MaxN + 1];

int gProfit(int n)
{
	if (n == 0)
		return (0);
	if (dp[n] != -1)
		return (dp[n]);

	int res;
	res = gProfit(n - 1);
	if (n >= T[N - n + 1])
		res = max(gProfit(n - T[N - n + 1]) + P[N - n + 1], res);
	dp[n] = res;
	return (dp[n]);
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d %d", &T[i], &P[i]);
	memset(dp, -1, sizeof(dp));
	printf("%d\n", gProfit(N));
}