/*

*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxN = 10000;
int stack[MaxN];
int elemCnt = 0;
char op[6];

void push(int put)
{
	stack[elemCnt] = put;
	elemCnt++;
}

void pop()
{
	int out;

	if (elemCnt == 0)
		out = -1;
	else
	{
		out = stack[elemCnt - 1];
		elemCnt--;
	}
	printf("%d\n", out);
}

void size()
{
	printf("%d\n", elemCnt);
}

void empty()
{
	printf("%d\n", (elemCnt == 0));
}

void top()
{
	if (elemCnt == 0)
		printf("-1\n");
	else
		printf("%d\n", stack[elemCnt - 1]);
}

int main()
{
	int N;
	
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", op);
		if (strcmp("push", op) == 0)
		{
			int put;
			scanf("%d", &put);
			push(put);
		}
		else if (strcmp("pop", op) == 0)
			pop();
		else if (strcmp("size", op) == 0)
			size();
		else if (strcmp("empty", op) == 0)
			empty();
		else if (strcmp("top", op) == 0)
			top();
	}
}