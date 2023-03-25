#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 300;
const int IMPOSSIBLE = -100000000;
int N;
int step[MaxN + 10];
int dp[MaxN + 10][3]; // n번째 계단부터의 최대합

/*
모든 가능한 조합을 확인해야한다.
근데 백트래킹을 사용한다고해도 조합의 수가 상당히 많다. 계단 개수가 최대 300개...
-> dp 사용.

어떠한 특정 계단에 도달하였을 때, 뒤쪽 계단 점수의 최대합은 정해져있다.
이걸 저장하면 된다.

base case:
	마지막 계단 도달 -> 0점

1. 한 계단 오른다 (만약 연속된 계단 = 2인 경우 불가)
2. 두 계단 오른다

둘 중 더 큰 값을 리턴한다.
*/

/*
아!!! 같은 계단이어도 현재까지 연속된 계단의 수(conti)는 다를 수 있으므로
dp로 저장할 때 conti도 변수로 취급하여 저장해야한다.
아...dp 재귀 함수의 파라미터 값은 상황 정보에 해당하므로 전부 dp에 넣어야하는구나.
*/
/*
각 변수가 어떤 값을 저장하는지를 확실히 하자...하나의 계단이라도 밟으면 conti = 1이다
*/
int stepScore(int n, int conti)
{
	if (n == N)
		return (0);
	else if (n > N)
		return (IMPOSSIBLE);
	if (dp[n][conti] != -1)
		return (dp[n][conti]);
	
	int res = stepScore(n + 2, 1) + step[n + 2];
	if (conti < 2)
		res = max(res, stepScore(n + 1, conti + 1) + step[n + 1]);
	dp[n][conti] = res;
	return (res);
}

/*
굳이 따로 구하게 두기에는 이상한 값(주로 초반부 값)들은
초기값을 미리 채워두는게 좋음.
*/
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &step[i]);
	
	memset(dp, -1, sizeof(dp));
	// dp[1][0] = step[1];
	// dp[2][0] = step[2];
	printf("%d", stepScore(0, 0));
}