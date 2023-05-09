// 여행하는 외판원 문제 (TSP)

// 11.5 MST 휴리스틱의 구현

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

/*
앞의 간단한 휴리스틱들도 그럴듯한 답을 내지만 이보다 더 실제 최적해에 가까운 답을 계산하는 휴리스틱을 사용하면 더 좋을 것이다.
*/

/*
최소 스패닝 트리(Minimun Spanning Tree, 최소 신장 트리, MST)
: 모든 정점을 잇지만 사이클이 없는 부분 그래프를 '신장 트리'라고 부르는데,
이 중 간선의 가중치 합이 최소가 되는 것을 '최소 신장 트리'라고 한다.

[최소 신장 트리의 조건]
- 반드시 (n-1)개의 간선만 사용해야 한다.
- 사이클을 포함해서는 안된다.
- 간선 가중치 합이 최소이어야 한다.


스패닝 트리는 딱 이 TSP 문제에 적절한 자료구조라고 할 수 있다.
MST를 구하는 여러 알고리즘이 있는데, 여기서는 대표적인 크루스칼(Kruskal) 알고리즘을 사용.

MST: https://gamedevlog.tistory.com/17
크루스칼 알고리즘: https://gamedevlog.tistory.com/34
	- 각 단계에서 최소 비용 간선을 선택
	- Cycle 여부 확인 (union-find 연산을 통해 확인) (https://blog.naver.com/ndb796/221230967614)
*/

/*
현재 위치에서 시작해서 아직 방문하지 않은 정점들을 모두 방문하고 시작점으로 돌아오는 최단 경로는 이 정점들을 모두 연결하는 스패닝 트리이다.
현재 위치를 기준으로 남은 정점들에 대한 최소 스패닝 트리의 가중치의 합은 항상 최단 경로보다 작다 (맨 처음에는 같을 것)
이를 이용하면 현실에 가까운 답으로 가지치기를 할 수 있다....

크루스칼의 스패닝 트리 알고리즘을 이용해 MST를 구하고, 간선 가중치의 합으로부터 탐색의 하한 값을 예상한다.
*/

// disjoint set(서로소 집합) 자료 구조
// Union-find를 위해 사용
// C++에서는 구조체에 함수 넣을 수 있음
struct DisjointSet
{
	DisjointSet(int n); // n개의 원소로 구성된 서로소 집합 생성 (생성자)
	int find(int here); // here가 포함된 집합의 대표 반환
	bool merge(int a, int b); // a가 포함된 집합 그리고 b가 포함된 집합을 합침
};

vector<pair<double,pair<int,int> > > edges; // 모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둠

/*
그래프의 모든 간선을 가중치에 따라 오름차순으로 정렬
가중치가 가장 작은 간선 e를 뽑는다
e를 트리에 넣을 경우 사이클이 생기면 삽입하지 않고 2번으로 이동한다.
사이클이 생기지 않으면 트리에 삽입한다.
트리의 간선 n-1개가 될 때까지 2번 과정을 반복한다. (간선이 n-1개가 되면 최소 신장 트리가 된다)
*/
// here, 아직 방문하지 않은 도시들, 시작점을 모두 연결하는 MST의 가중치 합 반환 (크루스칼(Kruskal) 알고리즘)
double mstHeuristic(int here, const vector<bool>& visited)
{
	DisjointSet sets(n);
	double taken = 0;
	// 사이클을 만들지 않는 경우 해당 간선을 MST에 포함시킨다
	// 모든 간선에 대해 해당 작업을 함으로써 최종적으로는 반드시 올바른 MST를 얻을 수 있게 된다
	// (좀 그리디 속성인데,,,, 어떻게 이게 가능한지는 kruskal 알고리즘 증명에 대해 알아볼 것)  
	for (int i = 0; i < edges.size(); i++)
	{
		int a = edges[i].second.first; // 남은 간선들 중 가장 가중치가 작은 간선의 시작 도시
		int b = edges[i].second.second; // 남은 간선들 중 가장 가중치가 작은 간선의 도착 도시
		if (a != 0 && a != here && visited[a]) continue ;
		if (b != 0 && b != here && visited[b]) continue ;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
	return (taken);
}

double solve()
{
	edges.clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());
	// 현 상황에서의 MST의 가중치의 합을 구해 하한 값을 예상해보고, 그를 토대로 간선들을 선택해나가는 작업을 반복한다
	// 이하 생략....
}
