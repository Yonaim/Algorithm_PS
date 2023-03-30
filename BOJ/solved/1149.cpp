/*
N = 5일때,

1 2 3 4 5

- 1번 집의 색은 2번 집의 색과 같지 않아야 한다.
- 5번 집의 색은 4번 집의 색과 같지 않아야 한다.
- 2~4번 집의 색은 양옆집들의 색과 같지 않아야 한다.

각 집을 특정 색으로 칠하는 비용은 각기 다르다.
한 집에 대해 3가지의 선택지가 존재 (물론 채우면서 불가한 색깔이 존재하게 됨)

순서대로 집을 칠한다고 했을 때 첫번째 집에는 3가지 선택지, 나머지 집들은 2가지 선택지가 있다.
N은 최대 1000이므로 3 * 2^999...너무 값이 크다.

1. 1번 집을 R로 칠하고 2번 집을 G로 칠하기 시작할 때와,
2. 1번 집을 B로 칠하고 2번 집을 G로 칠하기 시작할 때
2~5번 집을 같은 색으로 칠한다고 가정한다면 1번 집 비용을 제외한 값은 똑같다.
2~5번에 대한 총 비용을 저장하고 있으면 재사용할 수 있다는 뜻이다.

현재 집에서는 바로 우측 집의 컬러를 정하는데만 관심 있고 그 뒷 집들은 관심이 없다.
바로 우측 집의 컬러를 정한다면 그 뒷 집들의 최소 비용은 고정되어있다.
(다시 한번 말하지만 현재 집과 바로 우측 집의 뒤쪽에 위치한 뒷집들의 컬러는 관계가 없기 때문이다)
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define R 0
#define G 1
#define B 2

const int MaxN = 1000;
int N;
int cost[MaxN + 1][3];
int dp[MaxN + 1][3];

/*
현재 집의 컬러를 구하기 위해 아래 세 값을 비교한다.

cost(id, R) = min(cost(id - 1, G), cost(id - 1, B)) + R(id)
cost(id, G) = min(cost(id - 1, R), cost(id - 1, B)) + G(id)
cost(id, B) = min(cost(id - 1, R), cost(id - 1, G)) + B(id)

base condition:
	- id = N + 1인 경우 0

재귀함수에 필요한 인자:
	- 바로 그 직전 집의 색상
	- 남은 집의 개수
*/
// id번을 포함한 그 뒷집들의 총 cost
int paintCost(int id, int prevColor)
{
	int totalCost = INT_MAX;
	int tmpCost;

	if (id == N + 1)
		return (0);
	
	if (dp[id][prevColor] != -1)
		return (dp[id][prevColor]);
	
	for (int color = R; color <= B; color++)
	{
		if (color != prevColor)
		{
			tmpCost = paintCost(id + 1, color) + cost[id][color];
			if (tmpCost < totalCost)
				totalCost = tmpCost;
		}
	}
	dp[id][prevColor] = totalCost;
	return (totalCost);
}

int main()
{
	int minCost;

	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++)
		scanf("%d %d %d", &cost[i][R], &cost[i][G], &cost[i][B]);
	minCost = paintCost(1, -1);
	printf("%d\n", minCost);
}
