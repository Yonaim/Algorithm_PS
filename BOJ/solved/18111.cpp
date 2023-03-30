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
#include <stdbool.h>
#include <limits.h>

const int MaxH = 500;
const int MaxW = 500;
int H, W, I;
int arr[MaxH][MaxW];
int land[MaxH][MaxW];

/*
음? 어차피 가능한 높이만 확인하니까 아이템 개수는 신경 안 써도될거같다.
아이템 증감하는 부분은 빼자.
*/

int minecraft(int h)
{
	int time = 0;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			while (land[i][j] > h)
			{
				land[i][j]--;
				time += 2;
			}
			while (land[i][j] < h)
			{
				land[i][j]++;
				time += 1;
			}
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

// bool isAllSameHeight()
// {
// 	for (int i = 0; i < H; i++)
// 		for (int j = 0; j < W; j++)
// 	{
// 		if (arr[i][j] != arr[0][0])
// 			return (false);
// 	}
// 	return (true);
// }

// bool isOutOfRangeExist()
// {
// 	for (int i = 0; i < H; i++)
// 		for (int j = 0; j < W; j++)
// 	{
// 		if (!(0 <= arr[i][j] && arr[i][j] <= 256))
// 		{
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// void block()
// {
// 	if (isOutOfRangeExist() == true)
// 		return ;
// 	if (isAllSameHeight() == true)
// 	{
// 		if (time <= answerTime)
// 		{
// 			answerTime = time;
// 			if (arr[0][0] > answerHeight)
// 				answerHeight = arr[0][0];
// 		}
// 		return ;
// 	}
// 	if (time + 1 <= answerTime && item > 0)
// 	{
// 		time += 1;
// 		item--;
// 		for (int i = 0; i < H; i++)
// 			for (int j = 0; j < W; j++)
// 			{
// 				arr[i][j]++;
// 				block();
// 				arr[i][j]--;
// 			}
// 		time -= 1;
// 		item++;
// 	}
// 	if (time + 2 <= answerTime)
// 	{
// 		time += 2;
// 		item++;
// 		for (int i = 0; i < H; i++)
// 			for (int j = 0; j < W; j++)
// 			{
// 				arr[i][j]--;
// 				block();
// 				arr[i][j]++;
// 			}
// 	}
// }

// int main()
// {
// 	scanf("%d %d %d", &H, &W, &item);
// 	for (int i = 0; i < H; i++)
// 		for (int j = 0; j < W; j++)
// 		scanf("%d", &arr[i][j]);
// 	block();
// 	printf("%d %d\n", answerTime, answerHeight);
// }