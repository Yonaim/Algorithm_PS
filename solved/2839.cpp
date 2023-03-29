#include <stdio.h>

int N;

int	get_count_of_bags()
{
	int max_5_bags = N / 5;

	for (int i = max_5_bags; i >= 0; i--)
	{
		if ((N - (i * 5)) % 3 == 0)
			return (i + ((N - (i * 5)) / 3));
	}
	return (-1);
}

int main()
{
	scanf("%d", &N);
	printf("%d\n", get_count_of_bags());
}