/*
손님번호 N = 13일때
13 / 6 = 2(x값 3), 13 % 6 = 1 (y값 1)
	-> 103 (y * 100 + x)
*/

#include <stdio.h>
#include <math.h>
#include <limits.h>

int main()
{
	int T;
	int H, W, N;
	int x, y;

	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d %d %d", &H, &W, &N);

		if (N % H == 0) x = N / H;
		else x = N / H + 1;

		if (N % H == 0) y = H;
		else y = N % H;

		printf("%d\n", (y * 100) + x);
	}
}
