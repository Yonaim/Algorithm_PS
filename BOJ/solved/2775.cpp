/*
k층 n호에 사는 거주민의 수를 p(k, n)이라고 했을 때,
	p(k, n) = p(k, n-1) + p(k-1, n)	이다.

base condition:
	n = 1일 경우, 1
	k = 1일 경우, n

여러 개의 테스트 케이스가 들어올 수 있으므로 미리 저장해두는 것이 빠를 것이다.
즉 dp.

어....근데 k값의 상한선이 존재하지 않는다;;;
dp는 어려울 듯...

아 아니구나 값 제한 있네!
1 ≤ k, n ≤ 14 
쉼표가 'k, n' 이렇게 묶고 있는 거였다...ㅋㅋ

*/

#include <stdio.h>
#include <string.h>

const int Maxk = 14;
const int Maxn = 14;
int dp[Maxk + 1][Maxn + 1];

int person(int floor, int id)
{
	if (id == 1)
		return (1);
	else if (floor == 0)
		return (id);
	
	if (dp[floor][id] != -1)
		return (dp[floor][id]);

	dp[floor][id] = person(floor, id - 1) + person(floor - 1, id);
	return (dp[floor][id]);
}

int main()
{
	int T;
	int k, n;

	scanf("%d", &T);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < T; i++)
	{
		scanf("%d %d", &k, &n);
		printf("%d\n", person(k, n));
	}
}