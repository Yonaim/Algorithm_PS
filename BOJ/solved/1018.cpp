/*
	브루트포스.
	순서대로 돌면서 x + 8 < N && y + 8 < M
	조건 만족할 시 두 경우(흰색부터 시작 or 검은색부터 시작)에 대해
	칠해야하는 개수 구하기. 
	(x좌표값 0 <= N - 8, y좌표값 0 <= M - 8)
*/

#include <stdio.h>

const int SIZE = 8;
const int MAX_SIDE = 50;
char board[MAX_SIDE][MAX_SIDE];
int minimum = 10000;

/*
y 짝수 -> x 짝수시 start_color와 동일.
		x 홀수시 start_color와 다름
y 홀수 -> x 짝수시 start_color와 다름.
		x 홀수시 start_color와 동일
*/

void count_Repainting(int startX, int startY, char startColor)
{
	int cnt = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i % 2 == j % 2)
			{
				if (board[startY + i][startX + j] != startColor) cnt++;
			}
			else
			{
				if (board[startY + i][startX + j] == startColor) cnt++;
			}
		}
	}
	if (cnt < minimum)
		minimum = cnt;
}

int main()
{
	int N, M;

	scanf("%d %d", &N, &M);
	for (int y = 0; y < N; y++)
		scanf("%s", board[y]);
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (y + SIZE <= N && x + SIZE <= M)
			{
				count_Repainting(x, y, 'W');
				count_Repainting(x, y, 'B');
			}
		}
	}
	printf("%d", minimum);
}