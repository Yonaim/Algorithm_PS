/*
숫자를 받는다
num[5]안에 각 숫자를 넣는다. 길이 len도 구한다
num[i], num[len - 1 - i]를 비교하여 판단한다
	(len / 2회만큼만 비교한다)
*/

#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int N)
{
	int len = 0;
	int num[5];

	while (N > 0)
	{
		num[len] = N % 10;
		len++;
		N /= 10;
	}
	for (int i = 0; i < len / 2; i++)
	{
		if (num[i] != num[(len - 1) - i])
			return (false);
	}
	return (true);
}

int main()
{
	int N;

	while (1)
	{
		scanf("%d", &N);
		if (N == 0)
			break ;
		if (is_palindrome(N) == true)
			printf("yes\n");
		else
			printf("no\n");
	}
}