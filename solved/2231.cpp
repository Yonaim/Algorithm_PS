
#include <stdio.h>

int main()
{
	int N;
	int sum, tmp;

	scanf("%d", &N);
	for (int i = 1; i < N; i++)
	{
		sum = i;
		tmp = i;
		while (tmp > 0)
		{
			sum += tmp % 10;
			tmp /= 10;
		}
		if (sum == N)
		{
			printf("%d\n", i);
			return (0);
		}
	}
	printf("0\n");
}