// 11.6 부분적으로 메모이제이션을 사용하는 최적화의 구현

const double INF = 1e200;
const int MAX = 30;
int n;
double dist[MAX][MAX];
double best;

#include <map>
#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

/*
말 그대로 '부분적으로' 메모이제이션을 한다.
메모리의 한계로 인해 모든 부분문제에 대해 메모이제이션을 할 수는 없으므로,
남은 문제조각의 수가 미리 정해둔 상수 k 이하일 경우에만 메모이제이션을 하도록 한다.
*/

/*
근데...
메모이제이션을 위해서는 함수의 반환 값이 현재 상태에만 영향을 받아야하는데,
가지치기를 적용할 경우 현재 상태까지 오기 위한 경로에 따라 반환 값이 달라질 수 있기 때문에
가지치기를 사용하는 경우 메모이제이션을 적용하기는 좀 까다롭다.
경로까지 메모이제이션의 키로 사용하면 쉽게 메모이제이션 할 수는 있겠지만...사실상 하는 의미가 없잖아;;

따라서, 이렇게 가지치기를 사용하는 상황에서 부분적으로 메모이제이션을 하기 위해서는
가지치기를 사용하지 않는 동적 계획법 함수를 별도로 작성하고,
탐색을 하다가 마침내 끝에서 k단계에 도달하면 이 함수를 사용하도록 해야한다.
*/

// 남은 도시의 수가 5 이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH = 5;

map<int, double> cache[MAX][CACHED_DEPTH + 1];

// 코드 어렵다... 418~419p 다시 읽어볼 것

double dp(int here, int visited)
{
	// 더이상 방문할 도시가 없는 경우 시작점으로 돌아가는 최단 경로 길이 반환
    if (visited == (1 << n) - 1)
        return dist[here][0];
    
	int remaining = n - __builtin_popcount(visited);
    double &ret = cache[here][remaining][visited];
    if (ret > 0)
        return (ret);
    ret = INF;
    for (int next = 0; next < n; next++)
    {
        if (visited & (1 << next))
            continue;
        ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
    }
    return (ret);
}

void search(vector<int> &path, int visited, double currentLength)
{
    // base case: 남은 도시의 수가 CACHED_DEPTH 이하이면 동적 계획법 함수를 호출한다
    if (path.size() + CACHED_DEPTH >= n)
    {
        best = min(best, currentLength + dp(path.back(), visited));
        return;
    }
}