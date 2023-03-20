#include <stdio.h>

#define max(a, b)  (((a) > (b)) ? (a) : (b))
const int MAX_N = 50;
int		N;
char 	board[MAX_N][MAX_N];
int		maximum = 0;

void	change_value(int x1, int y1, int x2, int y2)
{
	char	tmp;

	tmp = board[x1][y1];
	board[x1][y1] = board[x2][y2];
	board[x2][y2] = tmp;
}

int	get_count_of_longest_row(int y)
{
	int cnt;
	int max = 0;
	int	i = 0;

	while (i < N)
	{
		cnt = 1;
		while (i < N && board[i][y] == board[i + 1][y])
		{
			i++;
			cnt++;
		}
		if (cnt > max)
			max = cnt;
	}
	return (max);
}

int	get_count_of_longest_col(int x)
{
	int cnt;
	int max = 0;
	int	i = 0;

	while (i < N)
	{
		cnt = 1;
		while (i < N && board[x][i] == board[x][i + 1])
		{
			i++;
			cnt++;
		}
		if (cnt > max)
			max = cnt;
	}
	return (max);
}

int	get_count_of_longest(int x1, int y1, int x2, int y2)
{
	return (max(\
			max(get_count_of_longest_col(x1), get_count_of_longest_col(x2)), \
			max(get_count_of_longest_col(y1), get_count_of_longest_col(y2))));
}

void	bomboni(void)
{
	int cnt;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j < N - 1 && board[i][j] != board[i][j + 1])
			{
				change_value(j, i, j + 1, i);
				cnt = get_count_of_longest(j, i, j + 1, i);
				if (cnt > maximum)
					maximum = cnt;
				change_value(j, i, j + 1, i);
			}
			if (i < N - 1 && board[i][j] != board[i + 1][j])
			{
				change_value(j, i, j, i + 1);
				cnt = get_count_of_longest(j, i, j, i + 1);
				if (cnt > maximum)
					maximum = cnt;
				change_value(j, i, j, i + 1);
			}
			if (maximum == N)
				return ;
		}
	}

}

int main()
{
	char *line;

	scanf("%d", &N);
	maximum = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%s", line);
		for (int j = 0; j < N; j++)
			board[i][j] = line[j];
	}
	bomboni();
	printf("%d", maximum);
}
