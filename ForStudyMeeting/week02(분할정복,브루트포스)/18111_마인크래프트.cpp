/*
재귀 함수로 하면 될 것 같다.
	종료 조건:
		1. 모든 땅이 고른 경우 (시간과 높이 저장)
		2. 땅의 높이가 이상한 블럭이 있는 경우 (0 ~ 256 외의 값)

인벤토리에 블럭이 있는 경우, 블럭을 모든 곳에 차례대로 쌓아본다 (재귀 호출)
없는 경우, 차례대로 블럭을 제거해본다 (재귀호출)
*/

/*
전부 다 재귀 탐색하려니 아이템 개수가 10개 정도만 되어도 시간이 오래 걸린다.
현재 구하는 케이스의 시간이 이미 구해진 answerTime보다 더 많다면 더 재귀를 타지 않도록 
조건문을 넣어준다.
*/

/*
음 이래도 스택 오버플로우 문제 발생한다.ㅠ(재귀를 너무 많이 타서...)
생각을 좀 바꿔야할 것 같다.

블럭 개수의 총합 평균을 구해 그 값으로 층을 맞춰주는 건 어떨까 (물론 인벤토리도 포함...)

	블럭 개수의 총합 평균(mean) <- 될 수 있는 가장 큰 높이
	0 <- 될 수 있는 가장 작은 높이

mean에서부터 1씩 값을 낮춰가며 시간을 구한다.
근데 구한 해당 높이의 시간 값이 앞서 구한 시간보다 더 오래 걸린다면 더 이상 연산을 그만둔다.
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

const int MaxH = 500;
const int MaxW = 500;
int H, W, I;
int arr[MaxH][MaxW];
int land[MaxH][MaxW];

int minecraft(int h)
{
	int time = 0;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (land[i][j] > h)
				time += 2 * (land[i][j] - h);
			else if (land[i][j] < h)
				time += 1 * (h - land[i][j]);
		}
	}
	return (time);
}

int main()
{
	int time = 0;
	int answerTime = INT_MAX;
	int answerHeight = 0;
	int mean = 0;
	
	scanf("%d %d %d", &H, &W, &I);
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			scanf("%d", &arr[i][j]);
			mean += arr[i][j];
		}
	mean += I;
	mean /= (H * W);

	for (int h = mean; h >= 0; h--)
	{
		memcpy(land, arr, sizeof(land));
		time = minecraft(h);
		if (time < answerTime)
		{
			answerTime = time;
			answerHeight = h;
		}
		else
			break ;
	}
	printf("%d %d\n", answerTime, answerHeight);
}