/*
한 문제를 같은 형태의 여러 문제들로 쪼갤 수 있다
-> 분할정복.

N = 3일때 2차원 배열은 N = 2일때 2차원 배열을 2x2로 엮어둔 것이다.
N = 2일때 2차원 배열은 N = 1일때 2차원 배열을 2x2로 엮어둔 것이다.

base problem: N = 1일때 2차원 배열

들어온 r행 c열이 어디에 속하는지 확인한다.
	- 상단 좌측: size - 1로 재호출한다.
	- 상단 우측: (4분의 1 배열 안의 값의 수 * 1) + (size - 1)로 재호출
	- 하단 좌측: (4분의 1 배열 안의 값의 수 * 2) + (size - 1)로 재호출
	- 하단 우측: (4분의 1 배열 안의 값의 수 * 3) + (size - 1)로 재호출
*/

#include <stdio.h>
#include <math.h>

int get_base_visit_order(int r, int c)
{
	if (r == 0 && c == 0)
		return (0);
	else if (r == 0 && c == 1)
		return (1);
	else if (r == 1 && c == 0)
		return (2);
	else
		return (3);
}

int get_visit_order(int N, int r, int c)
{
	const int	side_len = pow(2, N);
	const int	side_len_half = side_len / 2;
	int			quarter_square_elems_cnt;

	if (N == 1)
		return (get_base_visit_order(r, c));

	if (r < side_len_half && c < side_len_half)
		return (get_visit_order(N - 1, r, c));

	quarter_square_elems_cnt = pow((side_len_half), 2);

	if (r < side_len_half && c >= side_len_half)
		return (quarter_square_elems_cnt \
				+ get_visit_order(N - 1, r, c - side_len_half));
	else if (r >= side_len_half && c < side_len_half)
		return (quarter_square_elems_cnt * 2 \
				+ get_visit_order(N - 1, r - side_len_half, c));
	else
		return (quarter_square_elems_cnt * 3 \
				+ get_visit_order(N - 1, r - side_len_half, c - side_len_half));
}

int main()
{
	int N;
	int r;
	int c;

	scanf("%d %d %d", &N, &r, &c);
	printf("%d", get_visit_order(N, r, c));
}