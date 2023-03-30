/*
뒤쪽부터 보았을 때 가능한 큰 수의 수열이 앞쪽에서 보았을 때 이어지는 수열이 된다.

f(i): i번째부터 보았을 때 가장 긴 부분 수열의 길이

dp[i][0]: i번째부터 보았을 때 가장 긴 부분 수열의 길이
dp[i][1]: i번째부터 보았을 때 가장 긴 부분 수열의 시작값

base case:
	i = N일때 부분 수열의 길이는 1, 시작값은 A[N]
		(그냥 아예 초기값으로 넣어둘까?)

1. i번째 수를 부분수열에 포함시킨다
2. i번째 수를 부분수열에 포함시키지 않는다

*/

// 음...두 값을 둘다 구해보는 걸로는 충분하지 않을 것 같음. 
// 가장 긴 증가하는 부분 수열의 길이는 시작값에 따라 달라지므로
// 적절하지 않은 것 같음

#include <stdio.h>
#include <string.h>
#include <queue>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 1000000;
int N;
int A[MaxN + 1];
int maxLen = 0;
int maxStart = 0;

/*
머리가 복잡해진다...그냥 생각나는대로 풀어보자
*/

void longLen()
{
	int maximum;
	int len;

	for (int start = 1; start <= N; start++)
	{
		maximum = 0;
		len = 0;
		for (int i = start; i <= N; i++)
		{
			if (A[i] > maximum)
			{
				maximum = A[i];
				len++;
			}
		}
		if (len > maxLen)
		{
			maxLen = len;
			maxStart = start;
		}
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	longLen();
	printf("%d\n", maxLen);

	std::queue<int> q;
	int maximum = 0;
	for (int i = maxStart; i <= N; i++)
	{
		if (A[i] > maximum)
		{
			printf("%d ", A[i]);
			maximum = A[i];
		}
	}
}