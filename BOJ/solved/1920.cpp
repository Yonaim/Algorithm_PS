/*
무식하게 들어온 숫자 N개를 중복 유무 상관없이 다 넣고 찾을 수에 대해서 N개를 다 확인하면 시간초과 됨
그렇지만 들어올 수 있는 숫자 N의 범위가 4억개가 넘으므로 해당 크기의 배열을 선언해서 유무를 저장할 수도 없음
즉 들어온 숫자를 그대로 저장하긴 해야함.
그러나
	1. 중복 없이 저장 <- 필수는 아니지만 하면 좋음
	2. 탐색하기 쉽게 저장

그럼 문제 풀이의 순서는,
1. 숫자 N개를 전부 받는다
2. 받은 숫자들에 대해 정렬한다
3. 이후 탐색할 때는 이진탐색하여 빠르게 찾아낸다
*/

#include <stdio.h>
#include <stdbool.h>
#include <algorithm>

const int MaxN = 100000;
int A[MaxN];
int N;
int M;

int main()
{
	int tmp;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);

	std::sort(A, &A[N]);

	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &tmp);
		printf("%d\n", std::binary_search(A, &A[N], tmp));
	}
}