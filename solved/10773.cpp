/*
단순하게 생각했는데, 0이 한번이 아니라 연속으로 여러 개 올 수 있다는 점을 생각하지 못했다.
이걸 깨달은 뒤 곧바로
	'배열 안에다가 다 받아두고, 후에 배열을 순회하면서 0이 나올때 바로 앞선 것을 지우자'
라고 생각했는데 배열이 아니라 스택을 써서 0이 나왔을 때 가장 최근에 집어 넣은 것을 빼는 것이 더 낫다는 생각이 들었다.
자료구조를 잘 사용해서 논리를 간단히 하자!
*/

#include <stdio.h>
#include <stack>

std::stack<int> stack;

int main()
{
	int K, n;
	unsigned int sum = 0;

	scanf("%d", &K);
	for (int i = 0; i < K; i++)
	{
		scanf("%d", &n);
		if (n == 0)
			stack.pop();
		else
			stack.push(n);
	}
	while (stack.empty() == false)
	{
		sum += stack.top();
		stack.pop();
	}
	printf("%u", sum);
}