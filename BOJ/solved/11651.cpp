#include <stdio.h>
#include <algorithm>

using namespace std;

const int MaxN = 100000;
pair<int, int> P[MaxN];

// p1이 좌측, p2가 우측에 있는 것이 옳다면 true
// 그렇지 않다면 false 반환
bool compare(pair<int, int> p1, pair<int, int> p2)
{
	if (p1.second < p2.second)
		return (true);
	else if (p1.second > p2.second)
		return (false);
	else
	{
		if (p1.first < p2.first)
			return (true);
		else
			return (false);
	}
}

int main()
{
	int N;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &P[i].first, &P[i].second);

	sort(P, P + N, compare);

	for (int i = 0; i < N; i++)
		printf("%d %d\n", P[i].first, P[i].second);
}