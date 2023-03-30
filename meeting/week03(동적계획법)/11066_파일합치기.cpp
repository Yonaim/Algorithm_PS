#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*
합칠 파일들은 연속되어야하므로...
파일 i부터 j까지 있을 때 그 중간 지점 m을 구하는 작업이 반복된다. 파일이 하나가 될때까지.

5개의 파일을 합치는 방법이 아래와 같이 두 가지 있다고 쳐보자. 
	1. (10 + (50 + (30 + 70))) + 100
	2. (10 + ((50 + 30) + 70)) + 100
나머지는 동일하고 (50 + 30 + 70) 내부에서만 합치는 조합이 다르다. 
그리고 (50 + 30 + 70)만 봤을 때, 최소한의 비용으로 합치는 방법이 존재한다.
그 외의 파일들과 합칠 때는 (50 + 30 + 70)를 최소한의 비용으로 합치는 경우만 생각하고 합치는 방법을 결정한다.
-> dp 사용

f(i, j): i번째 파일에서 j번째 파일까지의 최소 비용 합
	f(i, j) = f(i, m) + f(m + 1, j) + (i~j까지의 합)
	가능한 m값들 중 가장 최소의 값을 찾는다.

base case:
	i == j일때, cost[i] (그냥 초기값으로 넣어도 될 것 같다)

아래 예시의 경우...
(((10 + 20) + 30) + 100) 에서,
f(1, 3) =
		f(1, 2) + f(3, 3)
		혹은
		f(1, 1) + f(2, 3).
범위가 1~3이라서 m=1 혹은 m=2만 가능했다.
*/

const int MaxK = 500;
int K;
int cost[MaxK + 5];
int dp[MaxK + 5][MaxK + 5];

int minCost(int start, int end)
{
	if (start == end)
		return (0);
	if (dp[start][end] != -1)
		return (dp[start][end]);

	int res = INT_MAX;
	int basicCost = 0;
	for (int i = start; i <= end; i++)
		basicCost += cost[i];
	
	if (end == start + 1)
		res = basicCost;
	else
	{
		for (int i = start; i < end; i++)
			res = min(res, minCost(start, i) + minCost(i + 1, end));
		res += basicCost;
	}
	dp[start][end] = res;
	return (dp[start][end]);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &K);
		for (int i = 1; i <= K; i++)
			scanf("%d", &cost[i]);
		memset(dp, -1, sizeof(dp));
		printf("%d\n", minCost(1, K));
	}
}