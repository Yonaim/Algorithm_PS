/*
모든 '조합'을 확인하는 수밖에 없음. 브루트포스
순서를 강제하여 모든 조합을 확인하자
*/

#include <stdio.h>

const int MaxN = 100000;
int N;
int M;
int card[MaxN];
int answer;

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &card[i]);

	int sum;
	for (int i = 0; i < N - 2; i++)
	{
		for (int j = i + 1; j < N - 1; j++)
		{
			for (int k = j + 1; k < N; k++)
			{
				sum = card[i] + card[j] + card[k];
				if (answer < sum && sum <= M)
					answer = sum;
			}
		}
	}
	printf("%d\n", answer);
}