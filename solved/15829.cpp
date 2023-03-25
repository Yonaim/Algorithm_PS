
/*
50번째 항의 가중치 값 50^r(= 50^31)은 long long의 최댓값을 넘어버린다.
pow 함수를 호출하지 않고 직접 연산해야한다.

사칙연산과 모듈러의 관계에 따르면,
	(a + b) % m = ((a % m) + (b % m)) % m
	(a * b) % m = ((a % m) * (b % m)) % m

https://sedangdang.tistory.com/4

반복문을 돌며 자연스럽게 해당 차수에 해당되는 제곱수의 모듈러 값을 얻게 된다는 것이 핵심이다.

*/

#include <stdio.h>
#include <math.h>

const int MaxL = 50;
const int r = 31;
const int M = 1234567891;
int L;
char str[MaxL + 1];
long long hash = 0;
long long R = 1; // i번째 차수에 해당되는 항의 제곱수

int main()
{
	
	scanf("%d", &L);
	scanf("%s", str);
	for (int i = 0; i < L; i++)
	{
		hash = (hash + ((str[i] - 'a' + 1) * R)) % M;
		R = (R * 31) % M;
	}
	printf("%lld\n", hash);
}