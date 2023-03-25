
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int MaxLength = 50;
char str[MaxLength + 1];
char stack[MaxLength] = {0, };
int elemCnt;

/*
스택을 사용한다. 문자열을 처음부터 끝까지 탐색하는데,

1. 왼쪽 괄호 발견
	-> 스택에 push
2. 오른쪽 괄호 발견
	-> 스택에서 pop하여 매칭되는 괄호인지 확인

문자열의 끝에 도달했는데 스택에 남은 괄호가 없다면 균형잡힌 문자열이다.
*/

bool isVPS()
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			stack[elemCnt] = str[i];
			elemCnt++;
		}
		else if (str[i] == ')')
		{
			if (elemCnt == 0)
				return (false);
			if (stack[elemCnt - 1] == '(')
				elemCnt--;
			else
				return (false);
		}
		i++;
	}
	if (elemCnt == 0)
		return (true);
	return (false);
}

int main()
{
	int T;

	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%s", str);
		memset(stack, 0, sizeof(stack));
		elemCnt = 0;
		if (isVPS() == true)
			printf("YES\n");
		else 
			printf("NO\n");
	}
}
