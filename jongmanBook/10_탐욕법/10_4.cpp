// 10.4 문자열 합치기 문제를 해결하는 탐욕적 알고리즘

/*
이 문제에서는, 문자열이 합해지는 순서는 관계가 없고 그냥 합치기만 하면 된다.
그리고 한번 합칠 때의 비용은 '(s1의 길이) + (s2의 길이)'이다.
그래서 단순하게 생각해보기에, s1과 s2의 값을 최소화하면서 합치면 될 것 같으므로 가장 길이가 적은 문자열들부터
합쳐나가는게 좋아보인다.
*/

/*
[정당성 증명]

문자열 길이를 비교했을 때 a, b가 가장 작은 두 문자열이고, 이 둘보다 길이가 긴 어떤 문자열 x, y가 존재한다.
a와 x를 먼저 합쳤을 때 최적해라고 가정한다. 예상대로 a와 b를 먼저 합칠때도 최적해일까?

순서 상관없이 a, b, x, y (+그 외 문자열들)를 전부 합친 어떤 문자열을 S라고 하겠다.
S가 완성되어있으면, 이후 S가 총 비용에 미치는 영향은 재귀적으로 반복되므로 S를 합치는 비용을 최소화하는데만 집중하면
된다.

트리를 그려서 각 깊이(?)단계의 비용을 계산해 그 합으로 총 비용을 계산해보면,
가장 깊은 곳에 작은 문자열이 있는게 총 비용이 낮거나 같다. 즉 최소한 비용이 더 늘어날 일은 없으므로 이쪽도 확실하게
최적해라는 것을 알 수 있다.
*/

#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
우리의 로직대로라면 문자열들 중 최소 길이인 문자열을 계속 찾는 과정이 반복되고, 합친 문자열은 문자열들 목록에 다시
넣어야한다.
    -> 큐, 큐 중에서도 우선순위 큐가 최선의 자료구조이다.

우선순위 큐를 사용하면 특정 조건의 원소(여기서는 길이가 가장 작은 문자열)를 찾거나 새 원소를 추가하는 작업을 빠르게 할
수 있기 때문이다. 그래서 여기서는 STL의 priority_queue를 사용한다.
*/

int minCostOfconcat(const vector<int> &lengths)
{
    priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < lengths.size(); i++)
		pq.push(lengths[i]);
	
	int total_cost = 0;
	while (pq.size() > 1)
	{
		int min1 = pq.top(); pq.pop();
		int min2 = pq.top(); pq.pop();
		pq.push(min1 + min2);
		total_cost += (min1 + min2);
	}
	return (total_cost);
}