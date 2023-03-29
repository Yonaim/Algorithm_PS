/*

s(n, m): n번째 수부터 보았을 때 가장 큰 증가하는 수열의 합 
		(이때, 이 수열에서 가장 큰 수는 m이다)

최종적으로 구할 값: s(0, 0)

base case:
	n = N -> 0

1. 이번 수를 증가하는 수열 안에 넣는다
2. 넣지 않는다

s(n, m) = s(n + 1, A[n]) + A[n]
		혹은
		s(n + 1, m)
		둘 중 더 큰 값을 가진다.
*/

/*
음? 다른 사람 풀이를 보니 dp에 n만 있어도 되는 것 같네...
*/

#include <stdio.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

const int MaxN = 1000;
const int MaxAi = 1000;
int N;
int A[MaxN + 1];
int dp[MaxN + 1];

int gSum(int n, int m)
{
	if (n == N)
		return (0);

	if (dp[n] != -1)
		return (dp[n]);

	int res;
	res = gSum(n + 1, m);
	if (A[n] > m)
		res = max(gSum(n + 1, A[n]) + A[n], res);
	dp[n] = res;
	return (dp[n]);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	memset(dp, -1, sizeof(dp));
	printf("%d", gSum(0, 0));
}