// 8.21 폴리오미노의 수 구하기

/*
세로 단조 폴리오미노라서 생각보다 간단하게 문제를 해결할 수 있음
*/

#include <string>
#include <vector>

using namespace std;

const int MOD = 10 * 1000 * 1000;
int cache[101][101];

int poly(int n, int first)
{
    if (n == first)
        return (1);

    int &ret = cache[n][first];
    if (ret != -1)
        return (ret);
    ret = 0;
    for (int second = 1; second <= n - first; second++)
    {
        int add = second + first - 1;
        add *= poly(n - first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
        // %= 이거는 진짜 안 익숙하다 ㅋㅋㅋㅋ
    }
    return (ret);
}