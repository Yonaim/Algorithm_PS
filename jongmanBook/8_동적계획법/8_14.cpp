// 8.14 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘

/*
외우는 난이도를 판별하는 부분만 좀 까다로워서 별도의 함수로 따로 빼는데, 특별히 어려운 문제는 아니다.
어떤 수의 특정 위치에서부터 최소 난이도의 합은 그 이전까지의 수들과는 관계가 없으므로, dp를 사용할 수 있다.
(그 이전까지의 수들과는 관계가 없다=최적 부분 구조가 성립)
*/

#include <string>

using namespace std;

const int INF = 987654321; // ㅋㅋㅋㅋ악...
string N;

// N[a...b] 구간의 난이도를 반환한다
// 반환값은 1 혹은 2 혹은 4 혹은 5 혹은 10
int classify(int a, int b);
// 알고리즘 로직에서 핵심적인 부분도 아니고, 어려운 부분도 아니다.

int cache[10002];

// 수열 N[begin...]의 난이도 최소 합을 반환
int memorize(int begin)
{
    if (begin == N.size())
        return (0);

    int &ret = cache[begin];
    if (ret != -1)
        return (ret);

    ret = INF;
	// 현재 위치에서부터 길이 3~5의 문자열을 작은 문제 조작으로 떼고
	// 그 문자열이 끝난 직후부터의 최소 난이도의 합을 더해 총 난이도의 합을 구한다
    for (int L = 3; L <= 5; L++)
        if (begin + L <= N.size())
            ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
	return (ret);
}