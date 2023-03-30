#include <stdio.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

const int MaxN = 100;
const int MaxK = 100000;
int N, K;
int W[MaxN];
int V[MaxN];
int dp[MaxN + 1][MaxK + 1];

/*
모든 가능한 케이스들을 확인하는데, 가능한 모든 조합에서 겹치는 경우가 상당수있다.
예를 들어 
	물건 A, B, C를 담는 경우와
	물건 A, B, D를 담는 경우는
물건 A + B의 총 합이 겹친다. (무게, 가치 모두)
-> dp로 저장해서 재사용한다.

p(n, k): 'n번째 물건부터'만 사용하였을 때 무게 k 이내의 물건의 가치 총합

최종적으로 구할 것: p(0, K)

base case:
	n = N인 경우, 0

1. 현재 번호인 n번 물건을 선택한 경우 (k >= W[n]인 경우만 가능)
	-> p(n + 1, k - W[n]) + V[n]
2. 현재 번호인 n번 물건을 선택하지 않은 경우
	-> p(n + 1, k)

둘 중 더 큰 값을 리턴한다.
*/
int packedValue(int n, int k)
{
	if (n == N)
		return (0);

	if (dp[n][k] != -1)
		return dp[n][k];

	int res;
	if (k >= W[n])
		res = max(packedValue(n + 1, k - W[n]) + V[n], packedValue(n + 1, k));
	else
		res = packedValue(n + 1, k);
	dp[n][k] = res;
	return (res);
}

int main()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &W[i], &V[i]);
	memset(dp, -1, sizeof(dp));
	printf("%d", packedValue(0, K));
}
