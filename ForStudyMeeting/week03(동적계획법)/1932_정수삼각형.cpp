
#include <stdio.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

const int MaxN = 500;
int N;
int num[MaxN + 1][MaxN + 1];
int dp[MaxN + 1][MaxN + 1];

/*
특정 층에서 어떠한 수를 선택했을 때 그 아래 숫자들의 최대 조합은 이미 정해져있다.

sum(f, n): f층에서 n번째 수를 선택했을 때 그 아래층들의 숫자의 최대의 합
		(f는 층수, n은 해당 층에서 숫자의 순서)

f층에서 n번째 수를 선택했을 때, f-1층에서는 n번째 혹은 n+1번째를 선택할 수 있다.

1. sum(f-1, n) + num[f-1][n]
2. sum(f-1, n+1) + num[f-1][n+1]

둘 중 더 큰 값을 반환한다.

base case:
	f = 0 (존재하지 않는 0층에 도달) -> 0 반환
*/

int maxSum(int f, int n)
{
	if (f == 0)
		return (0);

	if (dp[f][n] != -1)
		return (dp[f][n]);
	
	dp[f][n] = max(maxSum(f - 1, n + 1) + num[f - 1][n + 1], \
					maxSum(f - 1, n) + num[f - 1][n]);
	return (dp[f][n]);
}

int main()
{
	scanf("%d", &N);
	for (int floor = N; floor > 0; floor--)
	{
		for (int i = 0; i < N - floor + 1; i++)
			scanf("%d", &num[floor][i + 1]);
	}
	memset(dp, -1, sizeof(dp));
	printf("%d", maxSum(N, 1) + num[N][1]);
	// printf("%d", num[1][3]);
}