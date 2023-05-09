// 여행하는 외판원 문제 (TSP)

// 11.1 TSP를 해결하는 완전 탐색의 구현
// 아주 간단하게 가지치기

const double INF = 1e200;
const int MAX = 30;
int n;
double dist[MAX][MAX];
double best;

#include <string>
#include <vector>

using namespace std;

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

void search(vector<int>& path, vector<bool>& visited, double currentLength)
{
	// 아주 간단하게 가지치기: 지금까지 찾은 가장 좋은 답 이상일 경우 이 이후로는 탐색을 중단
	if (currentLength >= best)
		return ;

	int here = path.back();
	// base case: 모든 도시를 다 방문했을 경우 0번 도시로 돌아가고 종료
	if (path.size() == n)
	{
		best = min(best, currentLength + dist[here][0]);
		return ;
	}

	// 다음에 방문할 도시를 선택
	for (int next = 0; next < n; next++)
	{
		if (visited[next] == true)
			continue ;
		path.push_back(next);
	}
}
