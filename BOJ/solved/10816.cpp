//----------------- 2. 수를 받아 전부 정렬하고 이진 탐색 -------------------------

// 특정한 수가 card 배열에 몇 번 등장하는지 세기 위해,
// 이진 탐색할때 해당 수가 등장하는 처음 위치와 마지막 위치를 구한다

#include <stdio.h>
#include <stdbool.h>
#include <algorithm>

const int MaxN = 500000;
int card[MaxN];
int N;
int M;

int main()
{
	int find;
	int *low_addrs, *up_addrs;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &card[i]);

	std::sort(card, &card[N]);

	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &find);
		low_addrs = std::lower_bound(card, card + N, find);
		up_addrs = std::upper_bound(card, card + N, find);
		if (low_addrs == card + N)
			printf("0 ");
		else
			printf("%ld ", up_addrs - low_addrs);
	}
}

// 음... 일단 맞았긴 했는데 실행시간하고 메모리보니 좋은 방법은 아닌듯
// 좋은 풀이 https://www.acmicpc.net/source/57851656
/*
아아~~~숫자의 범위는 '-1천만 ~ 1천만'이지만 숫자의 개수는 오십만개가 최대이므로
정렬 후 이진 탐색은 메모리를 훨씬 줄일 수 있구나.
근데 이건 알고 있었는데 이해가 안되는 건 왜 실행시간이 이리 차이나냐는 거지...내거의 절반 이하임ㅋㅋㅋ
이진 탐색이 그만큼 빠른건가?... 
*/

//----------------- 1. 2천만 바이트 크기의 배열 선언 -------------------------
/*
거의 비슷한 1920번 문제랑 같이 비교하여 볼 수 있다.

1. MaxN (=2천만 바이트) 크기의 배열을 선언해 소지 개수를 기록한다
2. 수를 받아 정렬하고 이후에 이진 탐색한다

이거는 숫자 범위가 그렇게 크지 않아서 1번 방법도 괜찮을 거 같은데?
그리고 탐색 최대 횟수도 커서...ㅇㅇ
1번으로 ㄱㄱ
*/

// #include <stdio.h>
// #include <stdbool.h>

// const int MaxValue = 10000000;
// const int cardIdxOffset = MaxValue;
// int card[MaxValue * 2 + 1] = {0, };
// int N;
// int M;

// int main()
// {
// 	int cardIdx, n;

// 	scanf("%d", &N);
// 	for (int i = 0; i < N; i++)
// 	{
// 		scanf("%d", &cardIdx);
// 		card[cardIdx + cardIdxOffset]++;
// 	}
// 	scanf("%d", &M);
// 	for (int i = 0; i < M; i++)
// 	{
// 		scanf("%d", &n);
// 		printf("%d ", card[n + cardIdxOffset]);
// 	}
// }