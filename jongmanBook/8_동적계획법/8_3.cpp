// 8.3 메모이제이션의 사용 예

/*
base case를 가장 먼저 처리하는 이유 :
	base case에 도달했다는 건,
		가장 기초가 되는 부분 문제에 도달했거나
		불가능한 맥락의 부분 문제(가령 a나 b가 음수)
	를 풀려고 시도했을 경우이다.
	cache 배열에 부분 문제의 해답을 저장하고 있으므로 후자가 문제가 된다.
	불가능한 맥락의 부분 문제는 base case 처리로 바로 컷해줘서 cache 배열에 접근조차 못하게 막기~
*/

// 값을 모두 -1로 초기화 (부분문제의 해답이 음수가 나올 수 없는 경우만 가능할 것이다)
int cache[2500][2500];

int someObscureFunction(int a, int b)
{
	// *** base case는 항상 처음에 처리한다 ***
	if (...)
		return ...;

// 참조형을 사용하면 조금 더 간결하게 코드를 작성할 수 있다
	int& ret = cache[a][b];
	// 이전에 (a, b) 부분문제의 답을 구한 적이 있으면 곧장 반환
	if (ret != -1)
		return (ret);

	// (새로운 부분문제에 대한 답을 계산)
	...
	return (ret);
}

int main()
{
	memset(cache, -1, sizeof(cache));
}