#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

const int MaxN = 100000;
const int MaxNameLen = 100;

typedef struct member_ {
	int age;
	char name[MaxNameLen + 1];
} member;

int N;
member members[MaxN];

// 오름차순으로 정렬
int	compare(const void *cmp1, const void *cmp2)
{
	member *mem1 = (member *)cmp1;
	member *mem2 = (member *)cmp2;

	if (mem1->age > mem2->age)
		return (1);
	else if (mem1->age < mem2->age)
		return (-1);
	else
		return (0);
}

int main()
{
	scanf("%d", &N);
	int idx = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %s", &members[i].age, members[i].name);
	}

	qsort(members, N, sizeof(member), compare);

	for (int i = 0; i < N; i++)
	{
		printf("%d %s\n", members[i].age, members[i].name);
	}
}