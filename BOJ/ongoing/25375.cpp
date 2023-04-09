#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*
a, b가 주어진다.

x, y의 최대공약수가 a이고
x + y = b인
자연수 쌍 x, y가 존재하는지 확인할 것.

a,b: 0~10^18
*/

/*
x, y의 순서는 바뀌어도 상관없으므로 x < y로 고정하고 값을 탐색해본다

단서
1. x, y는 둘다 a의 배수이다
2. x, y는 둘다 b보다 작다
3. x와 y값을 합치면 b가 된다

*/

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);

	printf("%d", );
}