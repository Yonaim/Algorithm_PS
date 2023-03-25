/*
aazz
azaz
azza
zaaz
zaza
zzaa

모든 문자열을 갖고있으면 오래 걸릴까?
문자열의 최대 길이는 200. 
200개 중 100개의 자리를 선택해야하므로...
C(200,100) = 200*199*198...100. 너무 많다 ㅠㅠ
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 100;
const int MaxM = 100;
int N, M, K;
int dp[MaxN + MaxM][MaxN];

/*
단 두 종류의 문자만 존재하므로 문제는 생각보다 간단할 것 같다.
요컨데 총 N + M자리에서 N자리만 결정하면 되는 것이다.
a가 좌측 정렬(즉 N자리를 좌측 정렬)되는 것을 우선하여 결정하여 그 개수를 세면 된다.

1. 이번 자리에 a가 들어감
2. 이번 자리에 a가 들어가지 않음 (남은 자리의 개수 < N일때만 가능)

base case:
	- 남은 자리의 개수 
	- 남은 a의 개수 = 0

f(d, a): d자리만큼 남았고 a개 만큼 a를 사용하였을 때 문자열의 개수
	(현재까지 a 혹은 z로 결정한 자리수, 사용한 a 개수)

*/

int stringCnt(int d, int a)
{
	if (a == N)
		return (1);
	
	dp[d - 1][a + 1] = stringCnt(d - 1, a + 1);
	if (d < N)
		dp[d - 1][a] = stringCnt(d - 1, a);
	else
		dp[d - 1][a] = 0;
	return (dp[d - 1][a] + dp[d - 1][a + 1]);
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	memset(dp, -1, sizeof(dp));
	printf("%d\n", stringCnt(N + M, 0));
}