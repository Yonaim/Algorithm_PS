#include <stdio.h>
#include <stdbool.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

bool isRightTriangle(int diago, int n1, int n2)
{
	return (diago * diago == (n1 * n1) + (n2 * n2));
}

int main()
{
	int a, b, c, answer;

	scanf("%d %d %d", &a, &b, &c);
	while (1)
	{
		if (a == 0 && b == 0 && c == 0)
			break ;
		
		if (max(max(a, b), c) == a)
			answer = isRightTriangle(a, b, c);
		else if (max(max(a, b), c) == b)
			answer = isRightTriangle(b, a, c);
		else
			answer = isRightTriangle(c, a, b);
		
		if (answer == true)
			printf("right\n");
		else
			printf("wrong\n");

		scanf("%d %d %d", &a, &b, &c);
	}
}