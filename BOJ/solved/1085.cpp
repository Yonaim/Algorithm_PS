#include <stdio.h>

#define min(a,b)  (((a) < (b)) ? (a) : (b))

int main()
{
	int x, y, w, h;
	int minimum_x;
	int minimum_y;

	scanf("%d %d %d %d", &x, &y, &w, &h);
	minimum_x = min(w - x, x);
	minimum_y = min(h - y, y);
	printf("%d", min(minimum_x, minimum_y));
}

/*
11111
11101
11111

x ~ w 혹은 0 ~ x 혹은 y ~ h 혹은 0 ~ h
*/