/*
점들이 주어졌을 때 가능한 모든 벡터 매칭에 대해 그 합과 길이를 확인하여 최솟값을 얻어야 함
-> 완전탐색 (용어 이거 맞나?)

점의 개수 N개일때 가능한 벡터의 수는 N * (N - 1)...

벡터 매칭 결정 - 사용하지 않은 점의 개수가 0이 될때까지 재귀를 타고 들어간다.
만약 사용하지 않은 점의 개수 = 0이 된다면, 벡터 매칭이 결정되었다는 뜻이므로, 
길이를 구해 기존에 저장되어있던 최솟값과 값을 비교해본다.

base condition: 사용하지 않은 점의 개수 = 0 (벡터 매칭이 결정된 상태)

*/

#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct point_ {
	int x;
	int y;
} point;

typedef struct vector_ {
	int start_p;
	int end_p;
} vector;

#define MAX_POINT_CNT 20

const int maxPointCnt = 20;
int		N;
point	P[MAX_POINT_CNT]; // 모든 점을 저장
vector	vec_arr[MAX_POINT_CNT * (MAX_POINT_CNT - 1)]; // 모든 벡터를 저장
int		M[MAX_POINT_CNT / 2] = {0, };	// 매칭된 벡터들의 인덱스 배열
double	minimum;

double	get_length_of_matched_vectors_sum(void)
{
	long long sum_x;
	long long sum_y;

	sum_x = 0;
	sum_y = 0;
	for (int i = 0; i < N / 2; i++)
	{
		sum_x += P[vec_arr[M[i]].end_p].x - P[vec_arr[M[i]].start_p].x;
		sum_y += P[vec_arr[M[i]].end_p].y - P[vec_arr[M[i]].start_p].y;
	}
	return ((double)(sum_x * sum_x) + (sum_y * sum_y));
}

int	is_duplicated_point_exist(vector new, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		if (vec_arr[M[i]].start_p == new.start_p \
			|| vec_arr[M[i]].start_p == new.end_p
			|| vec_arr[M[i]].end_p == new.start_p
			|| vec_arr[M[i]].end_p == new.end_p)
			return (1);
	}
	return (0);
}

void	recursive_match_vector(int depth)
{
	if (depth == N / 2)
	{
		double sum_len = get_length_of_matched_vectors_sum();
		if (sum_len < minimum)
			minimum = sum_len;
		return ;
	}

	int min_vec_idx;
	if (depth == 0)
		min_vec_idx = 0;
	else
		min_vec_idx = M[depth - 1];

	for (int i = min_vec_idx; i < (N * (N - 1)); i++)
	{
		if (is_duplicated_point_exist(vec_arr[i], depth) == 1)
			continue ;
		M[depth] = i;
		recursive_match_vector(depth + 1);
	}
}

void fill_vec_arr()
{
	int	idx;

	idx = 0;
	for (int start_p = 0; start_p < N; start_p++)
	{
		for (int end_p = 0; end_p < N; end_p++)
		{
			if (start_p == end_p)
				continue ;
			vec_arr[idx].start_p = start_p;
			vec_arr[idx].end_p = end_p;
			idx++;
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		minimum = LONG_MAX;
		scanf("%d", &N);
		if (N % 2 == 1)
			return (1);
		for (int j = 0; j < N; j++)
			scanf("%d %d", &P[j].x, &P[j].y);
		fill_vec_arr();
		recursive_match_vector(0);
		printf("%f", sqrt(minimum));
	}
}

/*
시간초과가 났다...

왜 시간초과가 날까? 생각해보니 쓸데없이 중복으로 확인하고 있다.
예를 들어 10개의 점이 있어 벡터가 90개라고 할때, 
v1, v3, v11, v24, v80 이렇게 다섯 개가 하나의 벡터매칭이 된다고 해보자.
지금 코드는 이 한 조합에 대해서 순서를 달리해 전부 확인하고 있다. 
즉 벡터 5개로 이루어진 하나의 조합에 대해 5 * 4 * 3 * 2 * 1 = 120번이나 확인하고 있다...
시간초과가 날 수밖에 없다.

이를 방지하려면 순서를 강제하는 수밖에 없다. 예를 들어 위의 예시의 경우, (1, 3, 11, 24, 80)이라는
조합에 대해 무조건 오름차순을 강제하여 (1, 3, 11, 24, 80) 하나만 사용하는 식이다.

1. 모든 벡터를 구해 배열에 저장해둔다
2. 오름차순을 강제하여 벡터 매칭 안에 N개의 벡터를 채워간다
	- 물론 이때 지금까지 채운 벡터 매칭 안의 벡터들 중 겹치는 점(포인트)가 없는지 확인해야한다.
3. 하나의 벡터 매칭이 완성되었으면 해당 벡터들의 총합의 길이 값을 구한다
*/
