/*
그냥 전부 다 탐색하면 될듯
불가능한 경우는 더 깊숙히 안 들어가고 돌아가기. (백트래킹)
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

const int MaxN = 100000;
int N, K;
int fastest;
bool alreadyFind[MaxN + 10];

void find(int n, int time)
{
	if (alreadyFind[n] == true)
		return ;
	if (n == K)
	{
		if (time < fastest)
			fastest = time;
		return ;
	}
	if (time + 1 >= fastest)
		return ;

	alreadyFind[n] = true;
	if (n * 2 <= MaxN)
		find(n * 2, time + 1);
	if (n >= 1)
		find(n - 1, time + 1);
	if (n + 1 <= MaxN)
		find(n + 1, time + 1);
}

int main()
{
	scanf("%d %d", &N, &K);
	fastest = abs(K - N);
	memset(alreadyFind, false, sizeof(alreadyFind));
	find(N, 0);
	printf("%d", fastest);
}