/*
아~ 모든 원소들을 뒤로 한 칸씩 옮길 때 memcpy가 아니라 직접 옮겨야하겠네.
예를 들어
	1 2 3 4 () () -> () 1 2 3 4 ()
과 같이 한 칸씩 옮기려는데 memcpy를 해버리면 앞에서부터 순서대로 메모리 카피가 되어서
나중에 옮길 데이터가 덮어씌워질 수 있다. libft에서 겹침 방지 memcpy 만들었던거 생각나네...

앞으로 옮길 때는 데이터가 덮어씌워져도 어차피 옮긴 데이터니까 괜찮은데 뒤로 옮길때는 안된다.
*/

#include <stdio.h>
#include <string.h>

const int MaxN = 10000;
int deque[MaxN];
int elemCnt = 0;
char op[20];

void push_front(int put)
{
	for (int i = elemCnt - 1; i >= 0; i--)
		deque[i + 1] = deque[i];
	deque[0] = put;
	elemCnt++;
}

void push_back(int put)
{
	deque[elemCnt] = put;
	elemCnt++;
}

void pop_front()
{
	int out;

	if (elemCnt == 0)
		out = -1;
	else
	{
		out = deque[0];
		elemCnt--;
		memcpy(deque, deque + 1, sizeof(int) * elemCnt);
	}
	printf("%d\n", out);
}

void pop_back()
{
	int out;

	if (elemCnt == 0)
		out = -1;
	else
	{
		out = deque[elemCnt - 1];
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

void front()
{
	if (elemCnt == 0)
		printf("-1\n");
	else
		printf("%d\n", deque[0]);
}

void back()
{
	if (elemCnt == 0)
		printf("-1\n");
	else
		printf("%d\n", deque[elemCnt - 1]);
}

// 아 함수 형태가 다 달라서 함수 포인터 배열 못 쓰는구만ㅎ....
int main()
{
	int N, X;
	
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", op);
		if (strcmp("push_front", op) == 0)
		{
			scanf("%d", &X);
			push_front(X);
		}
		else if (strcmp("push_back", op) == 0)
		{
			scanf("%d", &X);
			push_back(X);
		}
		else if (strcmp("pop_front", op) == 0)
			pop_front();
		else if (strcmp("pop_back", op) == 0)
			pop_back();
		else if (strcmp("size", op) == 0)
			size();
		else if (strcmp("empty", op) == 0)
			empty();
		else if (strcmp("front", op) == 0)
			front();
		else if (strcmp("back", op) == 0)
			back();
	}
}
