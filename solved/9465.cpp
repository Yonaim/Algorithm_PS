/*
- 가능한 모든 경우를 확인해 봐야한다. (고득점 초레어 스티커가 있을 경우 그런 건 어떤 상황에 됐든간에 무조건 떼야함)
- 열의 개수가 변수이다.

열의 개수가 맨 우측으로 하나 늘어난다고 했을 때, 선택할 수 있는 스티커는 둘 중 하나이다

열이 5개라고 했을 때, 
1. 5번째 열에서 아래쪽 스티커 선택
	- 4번째 열: 위쪽 스티커 선택 or 스티커 선택 x만 가능
2. 5번째 열에서 위쪽 스티커 선택
	- 4번째 열: 아래쪽 스티커 선택 or 스티커 선택 x만 가능
3. 5번째 열에서 스티커 선택 x
	- 4번째 열: 위쪽 스티커 선택 or 아래쪽 스티커 선택 or 스티커 선택 x 모두 가능

같은 형식의 문제로 계속 쪼개갈 수 있음.
근데 위 세 경우 모두에서 3번째 열이 위쪽 스티커를 선택하는 경우를 포함함. 
즉 겹치는 내부 문제가 있음. dp로 저장해줄 것.

base case: 열이 단 하나도 남지 않음

*/

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <iostream>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MAX_N = 100000;

int dp[3][MAX_N + 1];
int P[2][MAX_N + 1];

// status: c + 1열의 스티커 선택 (0 = 위쪽, 1 = 아래쪽, 2 = 선택안함)
// c: 열 번호. 범위는 0 ~ (N - 1)

// 0 ->1,2
// 1 -.2,
// 2 -> 1
int sticker(int c, int status)
{
	if (c == -1) return (0);	
	if (dp[status][c] != -1) return (dp[status][c]);

	int tmp = sticker(c - 1, 2);
	if (status == 0) // c열에서 아래 or 선택 안함 가능
		tmp = max(sticker(c - 1, 1) + P[1][c], tmp);
	else if (status == 1) // c열에서 위 or 선택 안함 가능
		tmp = max(sticker(c - 1, 0) + P[0][c], tmp);
	else if (status == 2) // c열에서 모든 경우 다 가능
	{
		tmp = max(sticker(c - 1, 0) + P[0][c], tmp);
		tmp = max(sticker(c - 1, 1) + P[1][c], tmp);
	}
	dp[status][c] = tmp;
	return (dp[status][c]);
}
using namespace std;

int main()
{
	int T;
	int N;

	cin.tie(0); ios::sync_with_stdio(0);
	// scanf("%d", &T);
	cin >> T;
	for (int k = 0; k < T; k++){
		// scanf("%d", &N);
		cin >> N;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < N; j++)
				cin >> P[i][j];
				// scanf("%d", &P[i][j]);
		memset(dp, -1, sizeof(dp));
		cout << sticker(N-1, 2);
		printf("%d\n", sticker(N - 1, 2));
	}
	return (0);
}
