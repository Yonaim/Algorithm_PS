/*
키와 몸무게 '둘다' 커야 더 덩치가 큰 것으로 판단한다.
두 변수에 대해 상하관계가 존재하지 않으므로 pair로 묶어 특별하게 취급하지 않아도 된다.
*/

#include <stdio.h>

const int MaxN = 50;
int W[MaxN];
int H[MaxN];

int main()
{
	int N, rank;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &H[i], &W[i]);
	for (int i = 0; i < N; i++)
	{
		rank = 1;
		for (int cmp = 0; cmp < N; cmp++)
		{
			if (i != cmp && \
				W[i] < W[cmp] && H[i] < H[cmp])
				rank++;
		}
		if (i == N - 1)
			printf("%d", rank);
		else
			printf("%d ", rank);
	}
}