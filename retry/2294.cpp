#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 100;
const int MaxK = 10000;
const int IMPOSSIBLE = 100000000;
int coin[MaxN + 1];
int dp[MaxN + 1][MaxK + 1];
int N, K;

/*
minCoin(n, k) = 'n번째 동전부터'만 사용할 때, k원을 나타내는 최소 동전 개수

base case:
	- 불가능한 경우 (-1 리턴)

K = 15
1, 5, 12가 있는 경우...

3번째 동전만 사용할 때 -> 불가 (IMPOSSIBLE)
2, 3번째 동전만 사용할 때 -> 5 * 3
1, 2, 3번째 동전만 사용할 때 -> 1 * 3 + 12, 5 * 3

*/

/*
결국 이것도 모든 케이스를 확인하긴 함
근데 불가능한 케이스에서는 IMPOSSIBLE이 반환되면서 더 이상 깊숙히 들어가지 않음 ㅇㅇ
*/

// n번째 동전부터만 사용하여 k원을 만든다
int minCoin(int n, int k)
{
	if (n == N)
	{
		if (k == 0) return (0);
		else return (IMPOSSIBLE);
	}
	
	if (dp[n][k] != -1)
		return (dp[n][k]);

	if (k >= coin[n])
		dp[n][k] = min(minCoin(n + 1, k), \
					minCoin(n, k - coin[n]) + 1);
	else
		dp[n][k] = minCoin(n + 1, k);
	return (dp[n][k]);
}

int main()
{

	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &coin[i]);
	memset(dp, -1, sizeof(dp));

	int res = minCoin(0, K);
	
	if (res == IMPOSSIBLE)
		printf("-1\n");
	else
		printf("%d\n", res);
}