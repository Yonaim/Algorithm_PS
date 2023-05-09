// 여행하는 외판원 문제 (TSP)

/*
휴리스틱(heuristic)이란 '경험에 의거한' 문제 풀이 기법으로, 사람이 어림짐작으로 문제를 푸는 과정과 비슷하다고 보면 된다.
사전에서 찾아봐도 "proceeding to a solution by trial and error
or by rules that are only loosely defined"라고...loosely라는 단어가 있다.
*/

const double INF = 1e200;
const int MAX = 30;
int n;
double dist[MAX][MAX];
double best;

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

// 11.2 단순한 휴리스틱을 이용한 가지치기의 구현

double minEdge[MAX]; // 각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아둔 배열

// 아직 방문하지 않은 각 도시들에 인접한 간선 중 가장 짧은 것을 전부 더해 반환
double simpleHeuristric(vector<bool> &visited)
{
    double ret = minEdge[0]; // 시작점으로 돌아갈 때의 간선
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
            ret += minEdge[i];
    }
    return (ret);
}

void search(vector<int> &path, vector<bool> &visited, double currentLength)
{
    // 앞으로 더 방문해야하는 도시들에 도달하기 위한 최소 거리를 더해 지금까지 찾은 최적의 해와 대소비교를 함으로써
    // 가지치기 앞으로의 탐색 중 최소한의 값을 고려하기 때문에 위의 '아주 간단하게 가지치기'보다 성능이 좋다
    if (currentLength + simpleHeuristric(visited) >= best)
        return;

    // ...
}

/*
답의 남은 부분을 어림짐작해서 가지치기를 하고 있으니 이를 휴리스틱이라고 할 수 있다.
근데 내 처음 생각과는 달리... 값을 엄밀히 계산해 짐작하기보다는,

'남은 부분의 해가 적어도 이 값의 이상(이하)임을 보장함',
"따라서 앞으로의 탐색은 답이 될 수 있(없)다"

...와 같은 말 그대로 '어림짐작'이었다.
(최적해를 찾는 건 어렵지만 이렇게 어림짐작하는 건 비교적 쉽고, 비용이 적다.)

이렇게 '답의 남은 부분'을 어림짐작해 가지를 쳐내버리면
'지금까지 찾은 답의 값'으로 가지를 쳐낼때보다 더 일찍 쳐낼 수 있고, 높은 효율로 이어진다.
*/

// 11.3 가까운 정점부터 방문하는 최적화의 구현

vector<int> nearest[MAX]; // 각 도시마다 가까운 도시를 순서대로 int형 벡터에 정렬해서 미리 저장해둔 배열

/*
각 도시마다 가까운 도시를 순서대로 정렬해 둔 배열을 이용해 더 가까운 것부터 우선적으로 방문함으로써,
최적해가 될 가능성이 큰 답(좋은 답)을 우선적으로 찾는다.
좋은 답을 좀더 일찍 발견할 확률이 올라가므로, 가지치기를 많이 할 수 있게 된다.
=> 효율이 좋아진다
*/

void search(vector<int> &path, vector<bool> &visited, double currentLength)
{
    if (currentLength >= best)
        return;

    // 가까운 도시부터 우선적으로 방문한다
    int here = path.back();
    for (int i = 0; i < nearest[here].size(); i++)
    {
        int next = nearest[here][i];
        // here에서 출발해서 도착할 수 있는 도시들 중, 가장 가까운 순서대로 정렬했을 때 i번째인 도시를 다음에 방문한다

        // ...
    }
}

// 11.4 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현

/*
이번에는 앞에서와는 반대로 '지금까지 지나온(만든) 경로'를 이용해서 가지치기한다.
지금까지 만든 경로가 '시작 상태에서 현재 상태까지 도달하는 최적의 해'가 아닌 경우,
이 경로는 최적해가 될 수 없다. (각 부분 문제는 독립적이기 때문에...)
*/

// path의 마지막 네 개의 도시 중 가운데 두 도시의 순서를 바꿨을 때 총 경로가 더 짧아지는지 여부를 반환
// 한 도시를 추가할 때마다 실행한다
// 마지막 세 도시가 x,y,z였을 경우, x,y,z와 y,x,z 중 짧은 경로를 택하게 됨
// 결과적으로 한번의 비교를 통해 탐색 공간의 크기를 절반 이하로 줄일 수 있다.
bool pathSwapPruning(const vector<int> &path)
{
    if (path.size() < 4)
        return (false);

    // 네 개의 도시를 순서대로 p, a, b, q로 둠
    int p = path[path.size() - 4];
    int a = path[path.size() - 3];
    int b = path[path.size() - 2];
    int q = path[path.size() - 1];
    // (p~a + b~q) 그리고 (p~b + a~q)를 비교
    return (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q]);
}

/*
위 가지치기를 좀더 일반화할 수 있다.

어떤 경로가 존재한다고 했을 때, 위 방법을 그대로 사용하여
'현재까지의 경로에서 시작 도시와 마지막 도시를 제외한 경로를 완전히 뒤집었을 때'의
경로 길이의 합과 비교할 수 있다.

(왜냐하면 a,b,c,d,e라는 경로가 있을 때 그 사이 경로만을 완전히 뒤집은 a,d,c,b,e 경로와의 차이는
1번째 도시-2번째 도시 그리고 마지막 전 도시-마지막도시 뿐이기 때문이다.
처음과 마지막 도시 사이에 있는 도시들끼리의 거리 합은 같다~)
*/

/*
처음과 마지막 도시 사이 중간 도시들끼리 뒤집었을 때 총 경로의 합이 더 커지는 경우?
어떤 상황에서 이리 되는지 기하학적으로는 413p 하단을 보면 알 수 있다.
이미 지나온 경로를 교차하게 되는 경우이다.
*/

bool pathReversePruning(const vector<int> &path)
{
    if (path.size() < 4)
        return (false);
    int b = path[path.size() - 2];
    int q = path[path.size() - 1];
    // 부분 경로를 뒤집어 나온 경로들 중 더 짧은 것이 발견된다면 참 반환
    for (int i = 0; i + 3 < path.size(); i++)
    {
        // 뒤집을 부분경로의 시작위치 결정
        int p = path[i];
        int a = path[i + 1];
        // 경로 p,a...b,q와 p,b,...a,q의 거리를 비교해본다
        if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
            return (true);
    }
    return (false);
}
