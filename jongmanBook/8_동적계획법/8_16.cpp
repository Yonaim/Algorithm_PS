// 8.16 타일링의 수를 세는 동적 계획법 알고리즘

/*
지금까지 처럼 최적의 해를 찾는 문제가 아니라 '경우의 수'를 세는 문제이다.

사실 경우의 수가 그리 많지 않다면 굳이 dp를 쓸 것도 없이 단순하게 완전 탐색하여 모든 경우를 다 구하면된다.
dp를 꼭 써야하는 경우는 경우의 수가 매우매우 많은 경우, 대게 입력값에 지수적으로 경우의 수가 증가하는 경우이다.
	(32비트로 나타낼 수 없어 모듈러 연산을 해서 답을 출력하라고 한다)
*/

/*
252p에 나오는 두 그림은 맨 왼쪽 세로줄을 덮을 수 있는 2가지 방법이다.
이 2가지 방법은
	- 할 수 있는 모든 타일링 방법이다. 2가지 외에 다른 방법이 존재하지 않는다 
	- 각 방법은 서로가 겹칠 일이 없다
...따라서 맨 왼쪽 세로줄을 덮을 때 이 2가지 방법 중 하나를 택해 덮고 나머지에 대해 재귀호출하면
모든 경우를 탐색할 수 있다.
*/

const int MOD = 1000000007;
int cache[101];

int tiling(int width)
{
	// base case:
		// 남은 타일의 너비가 1 -> 세워서 넣는 수밖에 없다
		// 남은 타일의 너비가 0 -> 아무것도 안 넣는 수밖에 없다
	if (width <= 1)
	// width가 -1 이하인 경우로 들어올리는 없다
		return (1);

	int& ret = cache[width];
	if (ret != -1) return (ret);
	return (ret = (tiling(width - 2) + tiling(width - 1)) % MOD);
												// 늘 MOD로 나눠준다
}