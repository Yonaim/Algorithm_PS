#include <stdio.h>
#include <algorithm>

const int MaxN = 1000000;
int N;
int num[MaxN];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);

	std::sort(num, &num[N]);

	printf("%d\n", num[0]);
	for (int i = 1; i < N; i++)
	{
		if (num[i] != num[i - 1])
			printf("%d\n", num[i]);
	}
}