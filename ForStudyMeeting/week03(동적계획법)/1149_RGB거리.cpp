/*
각 집을 특정 색으로 칠하는 비용은 각기 다르다.
한 집에 대해 3가지의 선택지가 존재 (단, 옆의 집과 색이 겹치면 안됨)

순서대로 집을 칠한다고 했을 때 첫번째 집에는 3가지 선택지, 나머지 집들은 2가지 선택지가 있다.
N은 최대 1000이므로 3 * 2^999...전부 다 확인하기에는 케이스가 너무 많다.
	-> 평범한 DFS로는 시간제한 걸림

DP를 사용해 연산을 최소화하여 탐색해야할 것이다.
어떻게 값을 재사용할 수 있을까? 아래 두 케이스를 생각해보자.
	1. 1번 집을 R로 칠하고 2번 집을 G로 칠했다.
	2. 1번 집을 B로 칠하고 2번 집을 G로 칠했다.
위 두 케이스에서 2 ~ 5번 집을 같은 색으로 칠한다고 가정한다면, 1번 집 비용을 제외한 값은 똑같다.
근데 우리는 최소 비용만 알면 된다.
2 ~ 5번에 대한 최소비용을 저장하고 있으면 재사용할 수 있다는 뜻이다.

로직의 핵심:
	한 집의 컬러는 바로 맞닿은 집의 컬러를 정하는 데만 영향을 미치고, 그 이후의 집들과는 관계가 없다.
	(=현재 집과 맞닿지 않은 집들의 컬러는 현재 집의 컬러와 관계가 없다)
	그렇기 때문에, 현재 집의 우측 집의 컬러를 결정한다면 그 뒷집들의 최소 비용은 고정되어있다.
	이 논리는 모든 집들에 대해 적용된다.
*/

/*
재귀함수에 필요한 인자:
	- 바로 그 직전 집의 색상
	- 남은 집의 개수

cost(n, p): 끝에서 n번 집까지 색깔을 결정하였고, 직전 집의 컬러가 p였을때 최소 비용.

최종적으로 구하고 싶은 값:
		cost(1, Non-color)

base case:
	n = (N + 1) -> 0

현재 집의 컬러를 구하기 위해 아래 세 값 중 '가능한' 값들을 비교하고, 가장 작은 값을 리턴한다.
	1. cost(n, R) = min(cost(n - 1, G), cost(n - 1, B)) + R(n)
	2. cost(n, G) = min(cost(n - 1, R), cost(n - 1, B)) + G(n)
	3. cost(n, B) = min(cost(n - 1, R), cost(n - 1, G)) + B(n)

예를 들어, 현재 호출 인자가 p = R이었을 경우 2번 혹은 3번 케이스만 가능하다.
2, 3의 값을 비교해봤을 때 2번 값이 더 작았을 경우, 반환값은 cost(n, G)이다.
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 1000;
int N;
int cost[MaxN + 1][3];
int dp[MaxN + 1][3];

int paintCost(int n, int prevColor)
{
	if (n == N + 1)
		return (0);

	if (dp[n][prevColor] != -1)
		return (dp[n][prevColor]);
	
	int res = INT_MAX;
	for (int color = 0; color < 3; color++)
	{
		if (color != prevColor)
			res = min(paintCost(n + 1, color) + cost[n][color], res);
	}
	dp[n][prevColor] = res;
	return (dp[n][prevColor]);
}

int main()
{
	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++)
		scanf("%d %d %d", &cost[i][0], &cost[i][1], &cost[i][2]);
	printf("%d\n", paintCost(1, -1));
}
