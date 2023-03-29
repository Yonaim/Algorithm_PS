#include <stdio.h>

int N;
int video[64][64];

// 딱봐도 분할정복 문제.

// 현재 들어온 영상이 전부 같은 값으로 이루어져있는지 확인
// 그렇지 않다면, 전체를 4분할하여 각 영상을 인자로 하여 차례대로 재귀 호출
// base = 현재 영상의 크기가 1x1

// 재귀 함수 사용	
	// '(', 중간 결과(재귀 호출), ')'를 바로바로 출력해버리면 됨.

int is_all_same_value(int start_x, int start_y, int size)
{
	const int v = video[start_x][start_y];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (video[start_x + j][start_y + i] != v)
				return (0);
		}
	}
	return (1);
}

void recursive_compress(int start_x, int start_y, int size)
{
	if (size == 1)
	{
		printf("%d", video[start_x][start_y]);
		return ;
	}

	if (is_all_same_value(start_x, start_y, size) == 1)
		printf("%d", video[start_x][start_y]);
	else
	{
		printf("(");
		recursive_compress(start_x, start_y, size / 2);
		recursive_compress(start_x, start_y + (size / 2), size / 2);
		recursive_compress(start_x + (size / 2), start_y, size / 2);
		recursive_compress(start_x + (size / 2), start_y + (size / 2), size / 2);
		printf(")");
	}
}

int main()
{
	char line[64];

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", line);
		for (int j = 0; j < N; j++)
			video[i][j] = line[j] - '0';
	}
	recursive_compress(0, 0, N);
}
