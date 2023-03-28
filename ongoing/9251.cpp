/*
dp도 모든 가능한 케이스를 다 확인한다. 다만 겹치는 부분은 재계산하지 않을 뿐이다.

ABCDEF
SASBDF

L(i1, i2): i1 그리고 i2까지만 봤을 때 최장 수열의 길이

L(i1, i2) = 


*/

#include <stdio.h>
#include <string.h>

const int MaxLen = 1000;
char str1[MaxLen + 1];
char str2[MaxLen + 1];
int answerLen;
int tmp;

int getLengthOfLCS(int endStr2)
{
	int i1 = 0;
	int i2 = 0;

	while (i2 < endStr2 && str1[i1] != '\0')
	{
		if (str2[i2] == str1[i1])
			i1++;
		i2++;
	}
	return (i1 + 1);
}

int main()
{
	scanf("%s", str1);
	scanf("%s", str2);

	int i = 0;
	while (str2[i])
	{
		tmp = getLengthOfLCS(i);
		if (tmp > answerLen)
			answerLen = tmp;
		i++;
	}
	printf("%d\n", answerLen);
}