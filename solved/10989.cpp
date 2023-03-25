#include <stdio.h>

const int MaxNum = 10000;
int rec[MaxNum + 1] = {0, };

int main()
{
	int N;
	int tmp;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp);
		rec[tmp]++;
	}
	for (int i = 0; i <= MaxNum; i++)
		for (int j = 0; j < rec[i]; j++)
			printf("%d\n", i);
}