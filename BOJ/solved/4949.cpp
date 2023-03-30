
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int MaxLength = 100;
char str[MaxLength + 10];
char stack[MaxLength + 10] = {0, };
int count;

/*
스택을 사용한다. 문자열을 처음부터 끝까지 탐색하는데,

1. 왼쪽 괄호 발견
	-> 스택에 push
2. 오른쪽 괄호 발견
	-> 스택에서 pop하여 매칭되는 괄호인지 확인

무사히 '.'까지 도달했으며 스택에 남은 괄호가 없다면 균형잡힌 문자열이다.
*/

int isMachingBracketStr()
{
	int i = 0;

	while (str[i] != '.')
	{
		if (str[i] == '(' || str[i] == '[')
		{
			stack[count] = str[i];
			count++;
		}
		else if (str[i] == ')' || str[i] == ']')
		{
			if (count == 0)
				return (false);
			if (str[i] == ')' && stack[count - 1] == '(' 
				|| (str[i] == ']' && stack[count - 1] == '['))
				count--;
			else
				return (false);
		}
		i++;
	}
	if (count == 0)
		return (true);
	return (false);
}

// 문자열 입력 관련 이슈.
	// 공백까지 한번에 받기 위해 fgets 함수를 사용했는데 
	// (scanf는 'Hello world'라고 들어오면 Hello만 들어간다),
	// fgets는 두번째 인자로 버퍼의 사이즈를 지정해야한다
	// 근데 개행문자 + 널 터미네이트 문자까지 string 최대 길이 + 2를 지정해야 함.
	// 이거 때문에 시간 날림.........ㅋㅋㅋㅋ
// https://sedangdang.tistory.com/21
int main()
{
	fgets(str, MaxLength + 2, stdin);
	while (1)
	{
		if (strcmp(str, ".\n") == 0)
			break;
		memset(stack, 0, sizeof(stack));
		count = 0;
		if (isMachingBracketStr() == true)
			printf("yes\n");
		else 
			printf("no\n");
		fgets(str, MaxLength + 2, stdin);
	}
}

/*
짝지어지는 괄호 쌍의 범위 안에는 다른 단일 괄호가 걸쳐있으면 안된다.
예를 들어 '[Hello(]'는 짝지어지는 괄호쌍 '[]' 안에 '('가 있으므로 안된다.
'[Hello()]'는 가능하다. '[Hello(])'는 불가능하다.

문자열을 탐색하여 괄호를 찾는다 (처음 호출시 탐색 범위: 처음~끝)
	- 탐색 범위 = 0일시 성공으로 취급 (base condition)
	- 탐색 범위의 처음부터 끝까지 좌->우 방향으로 문자를 확인해나간다.
	1. 왼쪽 괄호 발견
		: 그에 알맞는 우측 괄호를 찾는다. (왼쪽 괄호 인덱스부터 탐색 범위 끝까지)
			- 짝지을 우측 괄호 발견: 해당 범위(짝지어진 괄호) 안에서 또 다시 탐색한다 (재귀적으로)
			- 짝지을 우측 괄호 못찾음: 실패.
	2. 우측 괄호 발견
		: 실패
	3. 아무런 괄호도 발견되지 않음
		: 성공
*/

// find: 찾는 우측 괄호
// int	matchBracketInRange(char find, int start, int end)
// {
// 	int cur = start;

// 	if (start == end)
// 		return (0);
// 	while (cur <= end)
// 	{
// 		if (str[cur] == '(' || str[cur] == '[')
// 		{
// 			if (str[cur] == '(')
// 				if (matchBracketInRange(')', cur + 1, end) == 1)
// 					return (1);
// 			else 
// 				if (matchBracketInRange(']', cur + 1, end) == 1)
// 					return (1);
// 		}
// 		else if (str[cur] == find)
// 			return (matchBracketInRange(-1, start, cur));
// 		else if (str[cur] == ')' || str[cur] == ']')
// 			return (1);
// 		cur++;
// 	}
// 	if (find == -1)
// 		return (0);
// 	else
// 		return (1);
// }