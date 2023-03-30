#include <stdio.h>

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define MAX_N 50
int		N;
char 	board[MAX_N + 1][MAX_N + 1] = {0, };
int		maximum = 0;

void swap(int x1, int y1, int x2, int y2)
{
	char	tmp;

	tmp = board[y1][x1];
	board[y1][x1] = board[y2][x2];
	board[y2][x2] = tmp;
}

void count_row(int y)
{
	int cnt;
	int	i = 0;

	while (i < N)
	{
		cnt = 1;
		while (i < N && board[y][i] == board[y][i + 1])
		{
			i++;
			cnt++;
		}
		if (cnt > maximum)
			maximum = cnt;
		i++;
	}
}

void count_col(int x)
{
	int cnt;
	int	i = 0;

	while (i < N)
	{
		cnt = 1;
		while (i < N && board[i][x] == board[i + 1][x])
		{
			i++;
			cnt++;
		}
		if (cnt > maximum)
			maximum = cnt;
		i++;
	}
}

void count(int x1, int y1, int x2, int y2)
{
	count_col(x1);
	count_col(x2);
	count_row(y1);
	count_row(y2);
}

void	bomboni(void)
{
	int cnt;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (x < N - 1)
			{
				swap(x, y, x + 1, y);
				count(x, y, x + 1, y);
				swap(x, y, x + 1, y);
			}
			if (y < N - 1)
			{
				swap(x, y, x, y + 1);
				count(x, y, x, y + 1);
				swap(x, y, x, y + 1);
			}
		}
	}
}

int main()
{
	char *line;

	scanf("%d", &N);
	maximum = 0;
	for (int i = 0; i < N; i++)
		scanf("%s", board[i]);
	bomboni();
	printf("%d", maximum);
	return (0);
}
