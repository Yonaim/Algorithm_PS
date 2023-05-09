// 8.13 합친 LIS 문제를 해결하는 동적 계획법 알고리즘

/*
바로 직전 문제에서 풀었을 때 이용한 재귀 함수 lis3()을 떠올려본다.

lis3(start): S[start]에서 시작하는 증가 부분 수열의 최대 길이

이 문제도 같은 방식으로 풀 수 있을 것이다.
대신 수열이 2개가 되었으므로 부분 문제를 정의할 때 두 수열의 인덱스를 모두 명시해야 함!

jlis(indexA, indexB): A[indexA] 그리고 B[indexB]에서 시작하는 합친 증가 부분 수열의 최대 길이
*/

/*
현재 증가 부분 수열의 최대값이 M이라 할 때, 할 수 있는 선택

	1. A[indexA + 1]부터의 값들 중 M보다 큰 값을 선택한다
	2. B[indexB + 1]부터의 값들 중 M보다 큰 값을 선택한다

두 경우에 대해 재귀 호출하고, 둘 중 더 큰 값을 리턴하면 된다.
*/

#include <string>
#include <vector>

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
// 입력값은 32비트 부호있는 정수이므로, 불가능한 값인 인위적인 최소치는 64비트로 설정
int n, m, A[100], B[100];
int cache[101][101];

// 수열 A, B의 특정 인덱스부터 합친 증가 부분 수열의 최대 길이를 반환
int jlis(int indexA, int indexB)
{
    int &ret = cache[indexA + 1][indexB + 1];
    if (ret != -1)
        return (ret);

    ret = 2;
	// index값이 -1일때는 처음에 시작할 때이다 (이때는 무조건 첫번째 원소를 선택하게 될 것이다)
    long long a = (indexA == -1 ? NEGINF : A[indexA]);
    long long b = (indexB == -1 ? NEGINF : B[indexB]);
    long long maxElem = max(a, b);
	// 다음 원소 찾기
    for (int nextA = indexA + 1; nextA < n; nextA++)
		if (maxElem < A[nextA])
			ret = max(ret, jlis(nextA, indexB) + 1);
	for (int nextB = indexB + 1; nextB < m; nextB++)
		if (maxElem < B[nextB])
			ret = max(ret, jlis(indexA, nextB) + 1);
	return (ret);
}