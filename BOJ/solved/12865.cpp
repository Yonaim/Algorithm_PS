#include <stdio.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

const int MaxN = 100;
const int MaxK = 100000;
int N, K;
int W[MaxN];
int V[MaxN];
int dp[MaxN + 1][MaxK + 1];

/*
모든 가능한 케이스들을 확인하되, dp로 저장해서 재사용한다.

p(n, k): 'n번째 물건부터'만 사용하였을 때 무게 k 이내의 물건의 가치 총합

base case:
	n = N인 경우, 0

1. 현재 번호인 n번 물건을 선택한 경우 (k >= W[n]인 경우만 가능)
	-> p(n + 1, k - W[n]) + V[n]
2. 현재 번호인 n번 물건을 선택하지 않은 경우
	-> p(n + 1, k)

둘 중 더 큰 값을 리턴한다.
*/
int packedValue(int n, int k)
{
	if (n == N)
		return (0);

	if (dp[n][k] != -1)
		return dp[n][k];

	int res;
	if (k >= W[n])
		res = max(packedValue(n + 1, k - W[n]) + V[n], packedValue(n + 1, k));
	else
		res = packedValue(n + 1, k);
	dp[n][k] = res;
	return (res);
}

int main()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &W[i], &V[i]);
	memset(dp, -1, sizeof(dp));
	printf("%d", packedValue(0, K));
}

// 이전의 시도.......
/*
가능한 모든 조합을 다 시도해본다.
근데 무게에 제한이 있으므로 불가능한 케이스들은 애초에 시도해보지도 않는다
(더 깊숙하게 들어가지 않도록 컷해버림, 백트래킹)

재귀 종료조건: 
	지금까지 총 무게의 합 > 버틸 수 있는 무게

가능한 조합(=무게를 버틸 수 있는 조합)의 경우 totalValue값을 갱신한다.
*/

/*
역시나 시간 초과가 나왔다. (dp 추천 문제로 푼거니 이렇게 될거라 알고 있었음)
가능한 모든 조합에서 겹치는 경우가 상당수있다.

예를 들어 
	물건 A, B, C를 담는 경우와
	물건 A, B, D를 담는 경우는
물건 A + B의 총 합이 겹친다. (무게, 가치 모두!)
*/

/*
RGB거리랑 비슷하게 생각해보자.
물건 A, B, C, D, E가 있다고 친다.

처음에 선택할 수 있는 물건의 경우는 총 5가지이다. 그리고,
	물건 A를 선택했을 때 가능한 최대의 가치를 내는 조합은 이미 정해져있다.
	물건 B를 선택했을 때 가능한 최대의 가치를 내는 조합은 이미 정해져있다.
	물건 C를 선택했을 때 가능한 최대의 가치를 내는 조합은 이미 정해져있다.
	...

조합이므로, 순서를 강제하기 위해 직전에 선택한 물건의 뒤쪽 물건들만을 선택한다
*/

/*
위에건 선택 순서를 강제함으로써 '조합'만 확인하도록 하는 것이었고
이제는 메모이제이션을 통한 시간 줄이기 테크닉을 사용한다.

음...sumW와 sumV를 사용하는 것만으로는 충분하지 않은 건가?
뭘 더 어떻게 저장해야하는걸까?

일단 sumW와 sumV는 현재까지 쌓인 물건의 무게와 가치의 합을 저장한다.
앞으로 담을 물건들에 대한 정보는 일절 없다.

즉 맨 처음에 A를 선택한 상황에서 C, D를 추가적으로 선택할 때와,
맨 처음에 B를 선택한 상황에서 C, D를 추가적으로 선택할 때
C, D를 추가하는 연산이 중복하여 들어가는 것이다.
*/

/*
같은 dp 문제지만 이 평범한 배낭 문제는 1149(RGB 거리) 문제보다는 약간 까다롭다.
왜냐면 총합 무게라는 것을 고려해야하기 때문이다.

	- RGB 거리 문제에서는 어떤 집의 색상이 정해져있으면, 그 뒤쪽 집들의 비용 총합의 최소 조합이 정해져있었다.
	- 이 문제에서도 어떤 물건의 pick 여부가 정해져있으면 그 뒤쪽 물건들의 가치 최대 조합이 정해져있긴 하다.
		근데 무게상 불가능한 조합들이 있다.
		<- 백트래킹.
*/

/*
공통되는 문제 형태: 앞으로 W를 더 들 수 있을 때 가능한 조합의 최대 가치?
			(중복된 조합을 방지하기 위해 직전에 선택한 물건의 뒤쪽 물건들 중에서 선택해야 함)

물건 1, 2, 3, 4, 5가 있을 때...

물건 2 선택
	-> 물건 3
		-> 물건 4
			-> 물건 5
		-> 물건 5
	-> 물건 4
		-> 물건 5

물건 2를 선택했고 이제 나머지 물건 선택 여부를 정하려고 한다.
	- 만약 앞으로 들 수 있는 무게 W > (물건 3부터 끝까지 봤을 때 최대의 조합 무게의 합)
	이라면 물건 2 + (물건 3부터 끝까지 봤을 때 최대의 조합)을 선택한다.
	- 같은 작업을 물건 4부터에 대해서도 한다.
	- 같은 작업을 물건 5부터에 대해서도 한다.

dp 배열에 저장되는 값은 '물건 n번부터에 대해서 최대의 조합의 무게 그리고 가치'

base condition:
	n = N인 경우, 물건 n의 무게와 가치가 그대로 저장
*/

// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>

// const int MaxN = 100;
// int N, K;
// int W[MaxN];
// int V[MaxN];
// bool is_packed[MaxN];
// int maxValue;

// void packing(int sumW, int sumV)
// {
// 	if (sumW > K)
// 		return ;
// 	if (sumV > maxValue)
// 		maxValue = sumV;
	
// 	for (int i = 0; i < N; i++)
// 	{
		// if (is_packed[i] == false)
		// {
		// 	is_packed[i] = true;
		// 	packing(sumW + W[i], sumV + V[i]);
		// 	is_packed[i] = false;
		// }
// 	}
// }

// int main()
// {
// 	scanf("%d %d", &N, &K);
// 	for (int i = 0; i < N; i++)
// 		scanf("%d %d", &W[i], &V[i]);
// 	memset(is_packed, false, sizeof(is_packed));
// 	packing(0, 0);
// 	printf("%d", maxValue);
// }