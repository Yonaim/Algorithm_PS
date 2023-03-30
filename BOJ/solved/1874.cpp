/*
1~n까지의 수를 스택을 사용해 정렬하기
작은 수부터 차례대로 넣어야하므로 뭐 이견이 없다.
*/

#include <stdio.h>

const int MaxN = 100000;
int N;
int stack[MaxN + 10];
int elemCnt = 0;
int goal[MaxN + 10];
char op[MaxN * 2 + 10];
int opCnt = 0;

void push(int put)
{
	stack[elemCnt] = put;
	elemCnt++;
	op[opCnt++] = '+';
}

int pop()
{
	int out = stack[elemCnt - 1];
	elemCnt--;
	op[opCnt++] = '-';
	return (out);
}

int sort()
{
	int sortCnt = 0;
	int n = 1;

	while (sortCnt < N)
	{
		if (goal[sortCnt] >= n)
		{
			while (n != goal[sortCnt])
				push(n++);
			push(n++);
			pop();
			sortCnt++;
		}
		else if (elemCnt > 0 && stack[elemCnt - 1] == goal[sortCnt])
		{
			pop();
			sortCnt++;
		}
		else
			return (1);
	}
	return (0);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &goal[i]);
	if (sort() == 0)
	{
		for (int i = 0; i < opCnt; i++)
			printf("%c\n", op[i]);		
	}
	else
		printf("NO\n");
}