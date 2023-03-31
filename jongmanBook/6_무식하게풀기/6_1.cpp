// 6.1 1부터 n까지의 합을 계산하는 반복 함수와 재귀 함수

int sum(int n)
{
	int ret = 0;
	for (int i = 1; i <= n; i++)
		ret += i;
	return (ret);
}

int recursiveSum(int n)
{
	if (n == 1)
		return (1);
	return (recursiveSum(n - 1) + n);
}