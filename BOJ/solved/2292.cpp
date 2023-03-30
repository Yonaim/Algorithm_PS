/*
중앙의 방 1부터 시작하여 돌아가는 육각형 모양의 방 둘레(?)를 층이라고 한다면,

0층: 1 (~1)
1층: 1 + 6 (~7)
2층: 1 + 6 + 12 (~19)
3층: 1 + 6 + 12 + 18 (~37)
...

즉 6의 배수를 더해가면서 N이 이 숫자보다 같거나 작은지 체크하면 된다.
*/

#include <stdio.h>

int main()
{
	int N;
	int floor, floorMaxId;

	scanf("%d", &N);
	floor = 0;
	floorMaxId = 1;
	while (N > floorMaxId)
	{
		floor++;
		floorMaxId += floor * 6;
	}
	printf("%d\n", floor + 1);
}