/*
이항계수 (binomial coefficient)
	: 이항식을 전개했을 때 계수. 
		C(N, K)는 N차항의 K번째 항을 의미한다

(a + b)^1 = a + b
(a + b)^2 = a^2 + 2ab + b^2
(a + b)^3 = a^3 + 3a^2b + 3ab^2 + b^3
...

보면 알겠지만 파스칼의 삼각형 구조를 따르고 있다.
즉 C(N, K) = C(N - 1, K - 1) + C(N - 1, K)

재귀로 푸면 될 것이다...
base condition:
	K = 0 혹은 K = N일때 1
*/

#include <stdio.h>

int pascalTriangle(int n, int k)
{
	if (k == 0 || k == n)
		return (1);
	return (pascalTriangle(n - 1, k - 1) + pascalTriangle(n - 1, k));
}

int main()
{
	int N, K;

	scanf("%d %d", &N, &K);
	printf("%d", pascalTriangle(N, K));
}