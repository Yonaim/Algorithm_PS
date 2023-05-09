// 문제: 두니발 박사의 탈옥

/*
확률 계산이지만 어렵게 생각할 것 없다.
(특정 조건의 경우의 수) / (총 경우의 수)로 나눠서 확률 구해주면 됨~
*/

#include <string>
#include <vector>

using namespace std;

// 8.22 두니발 박사의 탈옥 문제를 해결하는 완전 탐색 알고리즘
int n, d, p, q;

int connected[51][51];
int deg[51];

// 확률을 반환
double search(vector<int> &path)
{
    // base case: d일이 지남
    if (path.size() == d + 1)
    {
        if (path.back() != q) // q에서 끝나지 않았으면 무효
            return (0.0);
        double ret = 1.0;
        for (int i = 0; i + 1 < path.size(); i++)
            ret /= deg[path[i]]; // 유효한 경로가 결정되었으므로 확률 계산
        return (ret);
    }

    // 경로의 다음 위치 결정 (전형적인 BFS)
    double ret = 0;
    for (int there = 0; there < n; there++)
    {
        if (connected[path.back()][there] == true)
        {
            path.push_back(there);
            ret += search(path);
            path.pop_back();
        }
    }
    return (ret);
}

/*
이걸 그대로 dp로 변환하면 되는데...당연히 벡터(경로)를 그대로 갖다 쓸 수는 없고
벡터에서 꺼내 쓰는 정보를 부분문제의 정의로 삼아야한다.
앞에서 한대로, 하나의 부분문제를 식별하기 위해 꼭 필요한 필수적인 것만 갖다쓸 것을 명심할 것!
*/

// 8.23 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘
int n, d, p, q;

double cache[51][101];
int connected[51][51];
int deg[51];

double search2(int here, int days)
{
    // base case: d일이 지남
    if (days == d)
        return (here == q ? 1.0 : 0.0);

    double &ret = cache[here][days];
    if (ret > -0.5)
        return (ret);

    for (int there = 0; there < n; there++)
    {
        if (connected[here][there] == true)
            ret += search2(there, days + 1) / deg[here];
        // 확률을 바로 계산해 넣어버린다
    }
    return (ret);
}