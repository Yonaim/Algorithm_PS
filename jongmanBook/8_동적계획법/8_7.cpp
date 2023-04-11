// 8.7 와일드카드 문제를 해결하는 동적계획법 알고리즘

/*
앞에서 완전탐색을 위해 부분 문제를 정의하였다. 그 부분 문제의 인자를 생각해보자.

    - 패턴의 검사 시작 위치 (남은 패턴)
    - 문자열의 시작 위치 (남은 문자열)

'*'이 등장할 때마다 남은 s로 가능한 문자열들에 대해 전부 매칭 여부를 확인해주고 있다.
근데 패턴에 '*'이 한번만 등장할리는 없고 이후에도 여러 번 더 등장할 수 있다.
그럴 때마다 남은 s에서 가능한 문자열들에 대해 전부 매칭 여부를 확인해준다???
안쪽의 부분 문제로 들어갈 수록 겹치는 경우가 생길 것이다.
*/

/*
굳이 손으로 써보지 않아도 비둘기 집의 원리로 알 수 있다.
w의 길이가 w.len, s의 길이가 s.len일때 가능한 부분 문제의 수는 (w.len * s.len)가지이다.
근데 '*'을 만날 때마다 재귀적으로 호출하기 때문에, *이 많아지고 남은 s의 길이가 길어질 수록 풀어야하는 부분 문제의
개수가 많아진다. 재귀 호출이기 때문에 분명히 풀게되는 부분 문제의 개수가 부분 문제의 종류의 수를 넘을 것이고, 부분
문제가 겹칠 것임을 알 수 있다.

그리고 참조적 투명성.
남은 패턴과 남은 문자열이 일치하는 두 부분 문제가 있다고 할 때,
다른 외부요인이 끼어들 여지가 전혀 없으므로 두 부분 문제는 사실상 같은 부분 문제라고 볼 수 있다.
*/

#include <string>
using namespace std;

int cache[101][101];
string W, S;

// 와일드카드 패턴 w가 문자열 s에 대응되는지 여부를 반환한다
bool match(int w, int s)
{
    int &ret = cache[w][s];

    if (ret != -1)
        return (ret);
	
	while (s < S.size() && w < W.size() \
		&& (W[w] == '?' || W[w] == S[s]))
	{
		w++; s++;		
	}

	if (w == W.size())
		return (ret = (s == S.size()));

	if (W[w] == '*')
	{
		for (int skip = 0; s + skip <= S.size(); skip++)
		{
			if (match(w + 1, s + skip) == true)
				return (ret = true);
		}
	}
	return (ret = false);
}