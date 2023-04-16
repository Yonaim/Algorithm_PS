// 예제: 최대 증가 부분 수열 (LIS)

#include <string>
#include <vector>
using namespace std;
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

// 8.10 최대 증가 부분 수열 문제를 해결하는 완전 탐색 알고리즘

// A의 모든 증가부분수열을 만든 뒤 가장 긴 것의 길이를 반환
int lis(const vector<int>& A)
{
	if (A.empty())
		return (0);
	
	int ret = 0;
	// 증가부분수열의 시작 지점 잡기
	for (int i = 0; i < A.size(); i++)
	{
		// 시작지점 i부터 끝까지 돌아 A[i]보다 큰 수만 넣어둔 배열 B 만들기
		vector<int> B;
		for (int j = 1 + 1; j < A.size(); j++)
		{
			if (A[i] < A[j])
				B.push_back(A[j]);
			ret = max(ret, 1 + lis(B));
			// A[i]는 고정한 후, B의 LIS 길이를 구해서 더한다
		}
	}
	return (ret);
}

// 입력 손보기

/*
이전에 선택한 수들을 알 필요가 없다.
앞으로 선택할 수가 이전에 선택된 수들보다 크기만 하면 되는데 만족하는 경우만 더 깊게 들어가면 이를 보장할 수 있다.

그리고 구하게 되는 부분수열은 결국에 처음 주어진 수열의 일부이기 때문에,
인덱스를 통해 원하는 부분수열을 식별할 수 있다
*/

// 8.10 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘
int n;
int cache[100], S[100];

int lis2(int start)
{
	int& ret = cache[start];
	if (ret != -1)
		return (ret);
	
	ret = 1; // S[start]는 꼭 있으므로 적어도 길이 1을 가진다
	for (int next = start + 1; next < n; next++)
		if (S[start] < S[next])
		// 더 깊숙히 탐색하는 조건: 현재 수보다 더 큰 수인 경우에만 해당 수부터의 LIS를 구해본다
			// 인자로 넘겨서 확인할 수도 있긴 하겠지만 여기서는 재귀호출 전에 하네...
			ret = max(ret, lis2(next) + 1);
	return (ret);
}

/*
이 코드(8.10)를 그대로 사용하려면 맨 처음 반복문으로

lis2(0) ~ lis2(부분수열의 길이 - 1)

를 전부 호출해나가야한다.
보통 main문에 넣게 될텐데 위 함수 안에 이를 포함시키도록 작성할 수도 있다.
어떻게 하냐면...
*/

int n;
int cache[101], S[100];

int lis3(int start)
{
	int& ret = cache[start + 1];
	if (ret != -1)
		return (ret);
	
	ret = 1;
	for (int next = start + 1; next < n; next++)
		if (start == -1 || S[start] < S[next])
		
			ret = max(ret, lis2(next) + 1);
	return (ret);
}

/*
맨 처음에 lis3(-1)를 호출하면 된다. 
깊숙히 탐색하는 조건을 보면, 'start == -1'가 추가되어있다.
맨 처음에는 무조건 탐색하도록 설정한 것이다.

다만 주의할 점
	- 무조건 1부터 리턴값이 시작하기 때문에 실제 답은 'lis3(-1) - 1'이다.
	- start값이 처음에 -1로 주어지기 때문에 이를 감안해 배열 dp에서 인덱스값을 +1하여 접근
		(이러면 start = -1이어도 접근 오류가 안 날 것이다)
*/