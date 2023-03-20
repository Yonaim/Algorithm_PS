
#include <stdio.h>
#include <math.h>
#include <limits.h>

/*
늘어난 하나의 열에 대해 어떻게 대응할지가 핵심이다.
하나의 열이 늘어났을 때 이를 기존과 같은 형태의 문제로 쪼갤 수 있다.

근데 이 쪼개진 문제들은 계속 겹친다.
예를 들어 N = 10일때와 N = 5일때 모두 N = 3일때 해를 필요로 한다.
-> dp로 풀어야한다. (해를 저장하기)

base problem: 1개의 열일때 1개의 타일로 이를 채울 수 있음
*/

int tilling(int n)
{
	int dp[1001] = {0, };

	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i <= n; i++)
		dp[i] = (dp[i - 2] + dp[i - 1]) % 10007;
	return (dp[n]);
}

int main()
{
	int N;
	scanf("%d", &N);
	printf("%d\n", tilling(N));
}
