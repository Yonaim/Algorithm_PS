// 8.6 와일드카드 문제를 해결하는 완전탐색 알고리즘

#include <string>
using namespace std;

// 와일드카드 패턴 w가 문자열 s에 대응되는지 여부를 반환한다
bool match(const string &w, const string &s)
{
    int pos = 0;

    // w, s의 문자가 아직 남아있고, 현재 가리키는 곳이 원하는 문자와 일치하는 동안 while문을 돈다
    // 즉 할 수 있는 데까지 w와 s를 대응해서 넘기는 작업
    while (pos < s.size() && pos < w.size() \	
			&& (w[pos] == '?' || w[pos] == s[pos]))
        pos++;

	// 패턴이 전부 소진되었을 때, 남은 문자열이 없다면 일치. 있다면 불일치.
	// 아래 3개의 코드 블럭은 모두 같은 행위를 한다. (저자의 것은 마지막 거)
	// 간결한 코드 작성을 위해 참고할 것

	// if (pos == w.size() && pos == s.size())
		// return (true);
	// if (pos == w.size() && pos != s.size())
		// return (false);

	// if (pos == w.size())
	// 	if (pos == s.size())
	// 		return (true);
	// 	else
	// 		return (false);

	if (pos == w.size())
		return (pos == s.size());

	// 아래에서 패턴이 더 남아있음을 전제하고 w[pos]에 접근하기 때문에,
	// 여기서 패턴이 다 소진되었을 경우를 다 처리해야한다. (안 그러면 접근 오류 날 수 있음)

	// 패턴이 남았지만, *인 경우 해당 * 이후의 패턴, 그리고 지금까지 확인된 곳 이후 가능한 문자열들을 전부 확인해본다
		// 가능한 문자열들을 전부 확인하는 것은 *에 대응하는 문자열의 길이가 어찌될지 알 수 없기 때문이다.
	if (w[pos] == '*')
	{
		for (int skip = 0; pos + skip <= s.size(); skip++)
		{
			if (match(w.substr(pos + 1), s.substr(pos + skip)) == true)
				return (true);
		}
	}

	// 이 외의 경우는 전부 불일치로 간주한다
	return (false);
}

/*
while 반복문을 종료하였을 때

	- s[pos] != w[pos]
						-> 불일치
						
	- w[pos] == *
						-> 문자열 포인터를 하나씩 옮겨가며 패턴 매칭 시도.
							패턴 매칭에 성공하는 것이 있다면 일치

	- s 끝에 도달 (문자열이 모두 소진되었으나 패턴은 남아있음)
						-> 남은 패턴이 전부 *라면 일치, 그렇지 않다면 불일치

	- w 끝에 도달 (패턴이 모두 소진되었으나 문자열은 남아있음)
						-> 패턴이 모두 소진되었다는 것은 패턴에 *이 없었다는 것을 의미한다.
							문자열이 남아있으므로 불일치

	- 패턴이 모두 소진되고 문자열도 전부 소진됨
						-> 일치
*/
