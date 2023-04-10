// 7.9 팬미팅 문제

/*
모든 멤버가 포옹하는 조건

	1. 모든 멤버가 팬과 접촉
	2. 접촉하는 모든 (멤버, 팬)의 쌍들은 적어도 한 명의 여성을 포함

<1번 경우의 수>

	멤버가 m, 팬이 f명 있다고 할 때, 1번 경우의 수는?
	접촉하지 못하는 팬의 수를 좌, 우로 나눌 수 있는 경우의 수가 된다.
	가령 m=6, f=4인 경우 모든 멤버들이 접촉하는 상황에서 접촉하지 못하는 팬의 수는 6-4=2명이 되고,
	이를 좌우로 나누는 경우의 수는 (2, 0) (1, 1) (0, 2) 총 3가지이다.
	...사실은 0~2 -> 3가지라고도 쉽게 경우의 수를 알 수 있다. 왜냐하면 좌와 우, 단 두 종류로만 나누기 때문에 한쪽 값을 선택하면 나머지는 자동으로 골라짐.

	무튼 간에. 1번 경우의 수를 수식으로 나타내면
	(f - m + 1)가지이고, 가장 많은 경우의 수를 갖는 케이스는 m = 1, f = 200000에서 200000가지이다.

여기까지 구하고 나서 들은 생각. 음? 이거 걍 무식하게 풀면 되지 않나?...

<2번을 확인하기 위해 드는 시간>

	접촉중인 (멤버,팬)의 쌍은 m쌍이다. 모든 쌍의 성별을 확인하는데 2m의 시간이 든다.

<최종적인 시간복잡도(?)>

	(f-m+1)가지 경우의 수가 있고 각 경우를 확인하는데 드는 시간은 2m.
	둘을 곱하면 될 것이다.
	f의 범위는 m~200000이다.
	m이 고정일 때 f값이 클수록 (f-m+1)는 커진다. 2m은 f의 값과 상관이 없으므로 가장 오랜 시간이 걸릴 케이스의 연산 횟수를 계산하기 위해 f를 최대의 값으로 두면, 

->	(200000 - m + 1) * 2m
		= 400000m - 2m^2 + 2m 
			(m의 범위는 1~200000)

흠 이게 무슨 괴랄한 식이람....ㅋㅋㅋㅋㅋ
이런 식은 시간복잡도를 어떻게 나타내야하지??? O(n-n^2)?? 이상하다......ㅋㅋㅋㅋㅋ

엌...그래프 그리는 사이트에서 그려서 보니까 m = 100000일때 값이
대략 2×10^10....?ㅋㅋㅋㅋㅋㅋ100억번ㅋㅋㅋㅋㅋㅋ
확실히 안되는 것을 알겠다....
*/

// 무식하게 푸는게 안된다는 건 알겠는데...그리고 이걸 분할정복으로 풀어야한다는 것도 이미 알고 있는데 왜 분할정복인지 잘 모르겠다...ㅜㅜ

// 카라츠바 그건 잘 모르겠고...남성끼리만 있는 (멤버, 팬)의 쌍을 미리 구해서 전체 경우의 수에서 그걸 고려해 빼면 안되나 싶긴하다.

/*
와 미친...방금 답안 이해하고 왔는데. 진짜 개쩐다. 어떻게 이런 생각을 하지????
카라츠바(두 수의 곱셈을 빨리하는 알고리즘)는 제쳐두고,...어떻게 이 문제를 보고

- 두 수 a,b를 곱셈할 때, 그 결과값의 한 자리수를 구하기 위한 연산의 형태가
	두 수 a와 b 각각의 한 자릿수를 엮은 한 쌍의 곱이라는 점
- 오직 남성끼리만 있는 쌍을 판별하기 위해
	남성을 1, 여성을 0으로 나타내고 그 곱이 1일 때 남성끼리만 있는 조합임이라고 간주하는 아이디어

를 생각하지??????.....
띠용.....
무식한 방법말고는 떠오르지 않아서 일단 풀이보고 이해는 했는데, 시간을 아무리 많이 줬어도 솔직히 이걸 떠올릴 수는 없었을 것 같다.
*/

// 결국 이게 분할정복 문제인 이유는 두 수의 곱셈을 계산할 때 카라츠바를 사용하기 때문이었던 것인가?
// 흐음.......


#include <string>
#include <vector>

using namespace std;

// 카라츠바의 빠른 곱셈을 이용해 팬미팅 문제를 해결하는 함수
int hugs(const string& members, const string& fans)
{
	int N = members.size();
	int M = fans.size();

	// 성별을 판단하여 남자는 1, 여자는 0으로 넣어 수로 저장한다
	vector<int> A(N);
	vector<int> B(N);
	for (int i = 0; i < N; i++)
		A[i] = (members[i] == 'M');
	for (int i = 0; i < M; i++)
		B[i] = (fans[i] == 'M');

	// 각 자리수값을 구할 때 해당 자리수를 위한 곱들만을 합한다. (즉 작은 자리에서 올림처리 같은 건 하지 않는다)
	// 그래서 약간은 변형된 카라츠바
	vector<int> C = karatsuba(A, B);
	int allHugsCnt = 0;
	for (int i = N-1; i < M; i++)
		if (C[i] == 0)
			allHugsCnt++;
	return (allHugsCnt);
}