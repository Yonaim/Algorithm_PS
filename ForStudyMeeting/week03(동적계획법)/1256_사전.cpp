/*
모든 문자열을 갖고있으면 오래 걸릴까?
문자열의 최대 길이는 200. 
200개 중 100개의 자리를 선택해야하므로...
C(200,100) = 200*199*198...100. 너무 많다 ㅠㅠ
*/

/*
단 두 종류의 문자만 존재하므로 문제는 생각보다 간단할 것 같다.
요컨데 총 N + M자리에서 N자리만 결정하면 되는 것이다.
a가 좌측 정렬(즉 N자리를 좌측 정렬)되는 것을 우선하여 결정하여 그 개수를 세면 된다.

1. 이번 자리에 a가 들어감
2. 이번 자리에 a가 들어가지 않음

s(n, m) = a가 n개, z가 m개 남았을 때 문자열의 개수
	s(n, m) = s(n-1, m) + s(n, m-1)

근데! 우리가 알고싶은건 K번째 문자열이 '뭐냐는'거다.
그래서... 만약 K가 s(n-1, m)보다 작은 값을 가진다면 여기에 속하는 거고, 큰 값을 가진다면 s(n, m-1)에 속한다고 보면 된다.
파라미터값 K를 주어서 남은 문자열의 개수를 표시하면 될 것 같다. K = 0이 되면 찾은거다.

base case:
	n = 1 && m = 0 -> 1
	n = 0 && m = 1 -> 1
*/

/*
처음에는 한 함수에서 문자열의 개수를 구하는 동시에 구해야하는 문자열 속 문자를 결정하는 작업 또한 같이 하도록 하였다. 
처리가 조금 복잡했다.

- 다음 번에 호출할 때 인자로 남은 k값을 보내야했다.
- 재귀 탐색이 끝난 후(해당 차례부터의 문자열의 개수를 다 센 후) 문자를 결정할 수 있었기 때문에
	같은 함수를 같은 인자로 아래에서 한번 더 호출해야했다.
	물론 문자열에 문자를 기입할지 그 여부를 1 혹은 0으로 알리는 파라미터 하나를 추가해서...

구해야하는 문자열 속 문자를 결정하는 일은 사실 문자열의 개수만 구해져있으면 바로 할 수 있는 작업이다.
굳이 한 함수에서 할 필요가 없었다.
그래서...카운팅(가능한 문자열의 개수 세기) 작업과, 문자를 넣는 작업을 분리했다.
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 100;
const int MaxM = 100;
const int MaxK = 1000000000;
int N, M;
long long K;
long long dp[MaxN + 5][MaxN + 5];
char answer[MaxN + MaxM + 5];

/*
카운팅(가능한 문자열의 개수 세기) 작업과, 문자를 넣는 작업을 분리한다.
카운팅을 성공적으로 끝마치고 나면 dp 배열 안에 데이터가 모두 다 들어가있을테고,
그 데이터를 이용해 문자를 선택하여 넣는다.
*/
int strCnt(int n, int m)
{
	if (n == 0 || m == 0)
		return (1);
	if (dp[n][m] != -1)
		return (dp[n][m]);

	long long sc1, sc2;
	sc1 = strCnt(n - 1, m);
	sc2 = strCnt(n, m - 1);
	dp[n][m] = min(MaxK + 1, sc1 + sc2);
	return (dp[n][m]);
}

void makeString(int n, int m, int depth, long long remain)
{
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

	int cnt = strCnt(N, M);

	makeString(N, M, 0, K);
	answer[N + M] = '\0';

	if (K <= cnt)
		printf("%s\n", answer);
	else
		printf("-1\n");
}