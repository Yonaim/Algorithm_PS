/*
	100 99 1000000000

	999999900일이 지나면 999999900만큼 올라가있다.
	여기서 하루만 지나면 100이 더해져서 딱 채워짐

	하루에 1만큼 올라간다고 볼 수 있다.
	1000000000 - 100 에서 1을 나눠 기본적으로 깔리는 day를 구할 것 

*/

#include <stdio.h>

// 하루에 A - B미터 만큼 올라감
// 하루에 5미터 올라간다고 하고 12미터가 목적이라고 할때,
// 12 / 5 = 2일만큼 추가되고 2미터가 남는다

int main()
{
	int A, B, V;
	int day = 0;

	scanf("%d %d %d", &A, &B, &V);
	day += (V - A) / (A - B);
	V -= day * (A - B);
	if (V > 0)
	{
		while (1)
		{
			day++;
			V -= A;
			if (V <= 0)
				break ;
			V += B;
		}
	}
	printf("%d\n", day);
}