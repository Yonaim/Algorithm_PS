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

/*
단 두 종류의 문자만 존재하므로 문제는 생각보다 간단할 것 같다.
요컨데 총 N + M자리에서 N자리만 결정하면 되는 것이다.
a가 좌측 정렬(즉 N자리를 좌측 정렬)되는 것을 우선하여 결정하여 그 개수를 세면 된다.

1. 이번 자리에 a가 들어감
2. 이번 자리에 a가 들어가지 않음 (남은 자리의 개수 < N일때만 가능)

N = 2, M = 3일때...
- 첫 글자가 a인 경우 (N=1, M=3)
	- 두번째 글자가 a (N=0, M=3)
	- 두번째 글자가 z (N=1, M=2)
- 첫 글자가 z인 경우
	...

f(n, m) = a가 n개, z가 m개 남았을 때 문자열의 개수
	f(n, m) = f(n-1, m) + f(n, m-1)

근데!!!! 우리가 알고싶은건 K번째 문자열이 '뭐냐는'거다.
그래서... 만약 K가 f(n-1, m)보다 작은 값을 가진다면 여기에 속하는 거고, 큰 값을 가진다면 f(n, m-1)에 속한다고 보면 된다.
파라미터값 K를 주어서 남은 문자열의 개수를 표시하면 될 것 같다. K = 0이 되면 찾은거다.

base case:
	n = 1 && m = 0 -> 1
	n = 0 && m = 1 -> 1

맨 처음 호출... f(N + M, N, 0)

*/

/*
aazz
azaz
azza
zaaz
zaza
zzaa

aaazz
aazaz
aazza
azaaz
azaza
azzaa
zaaaz
zaaza
zazaa
zzaaa

10

f(2, 2)
f(2, 2)

여기서 2번째 문자열을 찾으려면?
a로 시작하는게 3개이므로, 첫번째 문자는 a로 시작.
a로 시작하는 것 중 a로 시작하는게 1개이므로, 두번째 문자는 z로 시작.
a로 시작하는 것 중 a로 시작하는 것 중 z로 시작하는게 1개이므로, 세번째 문자는 a로 시작.

*/

const int MaxN = 100;
const int MaxM = 100;
const int MaxK = 1000000000;
int N, M;
long long K;
long long dp[MaxN + 5][MaxN + 5];
char answer[MaxN + MaxM + 5];


/*
카운팅 작업과 문자를 넣는 작업을 분리한다.
카운팅을 성공적으로 끝마치고 나면 dp 배열 안에 데이터가 모두 다 들어가있을테고,
그 데이터를 이용해 문자를 선택하여 넣는다.
*/

int strCnt(int n, int m, long long remain)
{
	if (n == 0 || m == 0)
		return (1);
	if (dp[n][m] != -1)
		return (dp[n][m]);

	long long sc1, sc2;
	sc1 = strCnt(n - 1, m, remain);
	sc2 = strCnt(n, m - 1, remain - sc1);
	dp[n][m] = min(MaxK + 1, sc1 + sc2);
		// 오버플로우 방지...
		// 어차피 dp[n][m]은 문자 결정하는 역할 밖에 안함
// printf("dp[%d][%d]: %lld\n", n,m, dp[n][m]);
	return (dp[n][m]);
}

void makeString(int n, int m, int depth, long long remain)
{
// printf("%d %d %d %d\n", n, m, depth, remain);
	if (n == 0 || m == 0)
	{
		if (n > 0)
			for (int i = 0; i < n; i++)
				answer[depth + i] = 'a';
		else
			for (int i = 0; i < m; i++)
				answer[depth + i] = 'z';
		return ;
	}

	long long sc1;
	sc1 = dp[n - 1][m];
// printf("dp[%d][%d]: %d\n", n-1, m, sc1);
	if (remain <= sc1)
	{
		answer[depth] = 'a';
		makeString(n - 1, m, depth + 1, remain);
	}
	else
	{
		answer[depth] = 'z';
		makeString(n, m - 1, depth + 1, remain - sc1);
	}
}

int main()
{
	scanf("%d %d %lld", &N, &M, &K);
	memset(dp, -1, sizeof(dp));
	
	for (int i = 1; i <= N; i++)
		dp[i][0] = 1;
	for (int i = 1; i <= M; i++)
		dp[0][i] = 1;

	int cnt = strCnt(N, M, K);

	makeString(N, M, 0, K);
	answer[N + M] = '\0';

	if (K <= cnt)
		printf("%s\n", answer);
	else
		printf("-1\n");
	// printf("count: %d\n", cnt);
}