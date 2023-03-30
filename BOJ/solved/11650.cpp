
// https://github.com/kks227/BOJ/blob/master/11600/11650.cpp

/*
두 개체를 단일 개체로 처리하는 기능을 제공하는 구조체인 pair
(서로 다른 종류의 데이터를 묶을 수도 있으나 여기서는 같은 int타입끼리 묶음),
그리고 sort() 함수를 이용하여 손쉽게 구현한다.

pair 구조체는 first와 second 멤버로 구성되어있다.
pair 구조체를 sort에 넘기면 알아서 first 기준으로 먼저 정렬되고 second 기준으로 그 다음에 정렬된다
*/

#include <stdio.h>
#include <algorithm>

const int MaxN = 100000;
std::pair<int, int> P[MaxN];
int N;

int main()
{
	int x, y;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &x, &y);
		P[i].first = x;
		P[i].second = y;
	}	
	std::sort(P, &P[N]);
	for (int i = 0; i < N; i++)
		printf("%d %d\n", P[i].first, P[i].second);
}