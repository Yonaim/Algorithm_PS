// 아무것도 없이 직접 정렬하고 출력하려니 여러 조건들때문에 시간 초과가 나옴
// qsort 함수 사용하여 간단하게 해결.

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

const int MaxLength = 50;
const int MaxN = 20000;
char str[MaxN][MaxLength + 1];
int N;

// 오름차순으로 정렬하기 위해
	// str1 > str2일 경우 1을 반환
	// str1 < str2일 경우 -1 반환
	// str1 = str2일 경우 0 반환
int	compare(const void *cmp1, const void *cmp2)
{
	const char *str1 = (const char *)cmp1;
	const char *str2 = (const char *)cmp2;

	if (strlen(str1) > strlen(str2))
		return (1);
	else if (strlen(str1) == strlen(str2))
	{
		if (strcmp(str1, str2) > 0)
			return (1);
		else if (strcmp(str1, str2) < 0)
			return (-1);
		else
			return (0);
	}
	else
		return (-1);
}

int main()
{
	scanf("%d", &N);
	int idx = 0;
	for (int i = 0; i < N; i++)
		scanf("%s", str[i]);
	
	qsort(str, N, MaxLength + 1, compare);

	printf("%s\n", str[0]);
	for (int i = 1; i < MaxN; i++)
	{
		if (strcmp(str[i], str[i - 1]) != 0)
			printf("%s\n", str[i]);
	}
}