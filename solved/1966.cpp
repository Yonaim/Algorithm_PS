
#include <stdio.h>
#include <queue>

int N, M;
std::queue<std::pair<int, int> > Q; // first: order, second: importance

int getQueueValue(int nth)
{
	int value;

	for (int i = 0; i < Q.size(); i++)
	{
		if (i == nth)
			value = Q.front().second;
		Q.push(Q.front());
		Q.pop();
	}
	return (value);
}

bool isThereMoreImportant()
{
	for (int i = 1; i < Q.size(); i++)
	{
		if (getQueueValue(i) > Q.front().second)
			return (true);
	}
	return (false);
}

void print()
{
	int curious;
	int tmp;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp);
		Q.push(std::make_pair(i, tmp));
	}

	int printCnt = 0;
	while (1)
	{
		if (isThereMoreImportant() == true)
		{
			Q.push(Q.front());
			Q.pop();
		}
		else
		{
			printCnt++;
			if (Q.front().first == M)
				break ;
			Q.pop();
		}
	}
	printf("%d\n", printCnt);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		print();
		while (Q.empty() == false)
			Q.pop();
	}
}