// 6.7 여행하는 외판원 문제를 해결하는 재귀 호출 알고리즘

/*
여행하는 외판원 문제는 첫번째 여행지로 다시 돌아올 수 있는 경로 중 가장 비용이 적은 경로를 찾는 문제이다.
즉 최적의 해(가장 좋은 답)를 찾는 문제이다.이런 문제를 최적화 문제(Optimization problem)이라고 부른다.

최적화 문제의 해답을 구하는 가장 기초적인 방법이 '완전 탐색'이다.
(동적 계획법, 조합 탐색, 최적화 문제를 결정 문제로 바꿔서 해결하는 등의
좀더 빠른 방법들이 존재하나, 여기서는 가장 기초적이고 직관적인 완전 탐색으로 해결한다.)
완전 탐색은 말 그대로 완전하게 탐색하여 가능한 답들을 모두 생성해보고 그 중 가장 좋은 것을 택하면 된다.
*/

/*
가장 무식한 방법이기 때문에 시간, 공간적 제한 내에 답을 찾을 수 있는지 확인해야 한다.

탐색해야하는 케이스는 총 몇개가 될까? (문제에 따라서는 '가능한 답'의 개수가 아닐 수도 있으니 주의)
N개의 도시가 있다고 해보자. 모든 도시들이 서로 연결되어있다고 가정한다면,
처음에 N-1개의 도시 중 하나를 택하고, 그 다음은 N-2개의 도시 중 하나, 그 다음은 N-3...최종적으로는 하나만 남을 것이다.
그리고 처음 출발지로 다시 돌아간다.
(*첫번째 여행지로 다시 돌아와야하므로 어디서 출발하든 상관이 없다. 0번에서 출발한다고 가정)

그러면 탐색해야하는 케이스는 (N-1)!(=(N-1)*(N-2)...*2*1)개가 된다.
N은 최대 10이므로 컴퓨터가 1초 내에 계산할 수 있는 양이다.
*/

/*
한번의 재귀호출에서 도시 하나를 선택한다.
남은 도시의 개수 = 0이 될때까지 진행.

현재 시점에서 가능한 도시들 중 하나를 선택 -> shortestPath + (현재 선택한 도시까지의 cost)

선택 가능한 도시들에 대해 모두 시도해보고 그 중 가장 최적인 해를 return한다.
*/

#include <stdbool.h>
#include <limits.h>
#include <vector>
#define min(a,b)  (((a) < (b)) ? (a) : (b))

int n;
const int MAXn = 10;
double dist[MAXn][MAXn];

using namespace std;


double shortestPath(vector<int>& path, vector<bool>& visited, double curLength)
{
	// base case: 모든 도시를 다 돌았을 때
	if (path.size() == n)
		return (curLength + dist[path.back()][path[0]]);
	
	double ret = INT_MAX;
	// 현 시점에서 방문 가능한 도시를 전부 시도해보고 최적의 해를 찾는다
	for (int i = 0; i < n; i++)
	{
		if (visited[i] == true)
			continue ;
		visited[i] = true;
		path.push_back(i);
		
		double cand = shortestPath(path, visited, curLength + dist[path.back()][i]);
		ret = min(ret, cand);
		
		visited[i] = false;
		path.pop_back();
	}
	return (ret);
}
