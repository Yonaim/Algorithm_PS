// 8.1 재귀 호출을 이용한 이항 계수의 계산

/*
점화식 nCr = n-1Cr + n-1Cr-1

base case:
	r = 0일때, 1
	n == r일때, 1
*/

// 오직 재귀호출만을 사용하여 값을 구한다.
// n, r이 커짐에 따라 중복되는 부분문제가 기하급수적으로 증가한다
int bino(int n, int r)
{
	if (r == 0 || n == r)
		return (1);
	return (bino(n-1, r) + bino(n-1, r-1));
}


// 8.2 메모이제이션을 이용한 이항 계수의 계산

const int maxN = 100;
const int maxR = 100;
int cache[maxN + 1][maxR + 1];

int bino(int n, int r)
{
	if (r == 0 || n == r)
		return (1);
	if (cache[n][r] != -1)
		return (cache[n][r]);
	return (cache[n][r] = bino(n-1, r) + bino(n-1, r-1));
}