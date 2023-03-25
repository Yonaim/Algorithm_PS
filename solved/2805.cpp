/*
가장 길이가 긴 나무의 길이값 - 1부터 시작하여 자른 합이 M미터가 될때까지 반복하면 될 것이다.
시간제한에 걸릴까? 이것도 랜선 자르기 문제(1654번)처럼 상한값을 구해서 이진탐색 해야할까?
*/

/*
역시 시간 초과 나는군....
	하한값: 가장 작은 나무의 높이
	상한값: 가장 높은 나무의 높이
*/

#include <stdio.h>

const int MaxN = 1000000;
int N;
long long M;
long long tree[MaxN];

long long cut(long long H)
{
	long long sum = 0;

	for (int i = 0; i < N; i++)
	{
		if (tree[i] > H)
			sum += tree[i] - H;
	}
	return (sum);
}

int main()
{
	long long sum;
	long long mid, high, low;
	long long answer;
	
	scanf("%d %lld", &N, &M);
	scanf("%lld", &tree[0]);
	high = tree[0];
	low = tree[0];
	for (int i = 1; i < N; i++)
	{
		scanf("%lld", &tree[i]);
		if (tree[i] > high)
			high = tree[i];
		if (tree[i] < low)
			low = tree[i];
	}

// 가장 작은 나무의 높이보다 낮게 설정해야하는 경우도 있음.
// 가장 작은 나무의 높이로 절단했을 때 그 합이 M을 넘는지부터 확인
	sum = cut(low);
	if (sum < M)
	{
		high = low;
		low = 0;
	}

// 이진 탐색
	while (low <= high)
	{
		mid = (high + low) / 2;
		sum = cut(mid);
		if (sum >= M) // 최대값을 구해야하므로, 값이 같은 경우에도 하한값(low)를 높여 범위를 올려준다
		{
			low = mid + 1;
			answer = mid;
		}
		else 
			high = mid - 1;
	}
	printf("%lld\n", answer);
}