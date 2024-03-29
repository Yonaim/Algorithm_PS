/*
C1, C2, C3, C4
40, 30, 30, 50

합쳐야하는 횟수는 이미 정해져있고, 최소한의 조합을 뽑아내면 될 거 같은데?
전부 합쳐야하긴하므로 각 파일당 금액이 최소 한번씩은 들어가게 될 것이다.

파일이 4개 있을 경우는 3회 합쳐야한다.

//
첫번째 합칠 때는 4개 중 2개를 뽑아야한다.
두번째 합칠 때는 3개 중 2개를 뽑아야한다. 
마지막으로 합칠 때는 무조건 모든 파일의 비용 합만큼 들게된다.
//

파일들이 나열되어있을 때 최소한의 비용으로 합칠 수 있는 조합은 이미 정해져있다.
파일 개수가 2개가 되는 base case가 될때까지 전부 탐색하면서 확인해간다.

base case:
	남은 파일의 수 = 2일때, 두 파일의 크기 합

착각하면 안되는게 4개가 있을 때 무조건 2개 2개씩 합쳐두는게 답이 아니다.
예를 들어 10, 20, 30, 100과 같이 있을 때는 100을 합치는 걸 최소화 해야하므로,

	10 + 20, 30 + 100, (10 + 20) + (30 + 100)
이게 아니고
	10 + 20, (10 + 20) + 30, ((10 + 20) + 30) + 100
이게 답이다.

어!...식을 세우니 뭔가 보이는 것 같기도 하다...?

마지막에 합치는 과정을 보면...
	((10 + 20) + (30 + 100))
	(((10 + 20) + 30) + 100)
괄호쌍에 주목해보자.
파일이 4개이므로 둘다 괄호쌍은 3쌍이다.

괄호쌍 하나를 벗겨내기 위해서는 
	1. 파일을 두개 선택 (위 식의 10 + 20 혹은 30 + 100에 해당)
	2. 파일을 하나 선택 (아래 식의 100에 해당)
...해야한다.
둘 중 더 값이 낮은 case를 선택하면 될 것이다.

----------------------------
(10 + (20 + 30)) + 100
이런 케이스도 있는데 결국 (((10 + 20) + 30) + 100)에서 (10 + 20 + 30)이 겹친다.
이 부분을 dp로 재사용하면 될 것 같다.
----------------------------

...근데 이렇게 순서가 뒤바뀔 수도 있으므로 머리가 약간 복잡해진다.
((10 + 30) + 20) + 100
순서대로의 조합만 본다고 강제한다면?....

((10 + 30) + 20) + 100
(((10 + 20) + 30) + 100)

앗...결국에 가장 적은 비용이 드는 조합을 우선적으로 만드는 게 핵심이 아닌가 싶다.
각 괄호 안의 값이 각 단계에서 최저가 되야하는 것이다.
큰 비용이 드는 파일들은 나중에 합치는 편이 좋다.

즉
	현재 모든 파일들을 봤을 때 가장 작은 비용이 드는 조합을 찾아 합치고,
	해당 합쳐진 파일을 포함하여 가장 작은 비용이 드는 조합을 또 찾아 합치고,
	...
	남은 파일의 개수가 1이 될때까지 이를 반복한다.

가장 작은 비용이 드는 파일의 조합을 찾는 과정에서 여러 조합들의 비용을 구하게 되는데,
이것이 재사용할 수 있는 부분아닐까 추측해본다.

*/


/*
평범한 배낭 문제가 떠오른다.
거기서도 최적의 조합을 뽑는게 과제였다.
꼭 저장해야하는 subproblem의 맥락은 '남은 무게'였다.
(왜냐하면 '남은 무게'가 해당 케이스에서 더 깊숙히 들어갈 때 케이스들을 제한시켜주는 역할을 하기 때문에.)
근데 남은 무게만으로 어떤 조합을 특정지을 수 없다. 그래서 어떤 물건까지 보았는지를 추가로 저장했다.
*/

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*

1. 파일을 합친다
2. 파일을 합치지 않는다

f(n, m): n개의 파일이 남아있고 합칠지 여부를 확인하지 않은 파일이 m개일 때 총 비용의 최소 합
	-> f(n, m) = 
				f(n - 1, 0) + cost[]

base case:
	n = 0일시 0
	m = 0일시 0

*/

/*
아 미친 아 문제를 잘못이해했다;;;; 연속되어야하는 줄 몰랐음;;;;.......
합칠 파일들은 연속되어야하므로...
파일 i부터 j까지 있을 때 그 중간 지점 m을 구하는 작업이 반복된다. 파일이 하나가 될때까지.

f(i, j): i번째 파일에서 j번째 파일까지의 최소 비용 합
	f(i, j) = f(i, m) + f(m+1, j) + (i~j까지의 합)

base case:
	i == j일때, cost[i] (그냥 초기값으로 넣어도 될 것 같다)

위의 예시의 경우...
(((10 + 20) + 30) + 100)
에서, f(1, 3) =
			f(1, 2) + f(3, 3)
			혹은 f(1, 1) + f(2, 3).

범위가 1~3이라서 m=1 혹은 m=2만 가능했다.

*/

const int MaxK = 500;
int K;
int cost[MaxK + 5];
int dp[MaxK + 5][MaxK + 5];

int minCost(int start, int end)
{
	if (start == end)
		return (0);
	if (dp[start][end] != -1)
		return (dp[start][end]);

	int res = INT_MAX;
	int basicCost = 0;
	for (int i = start; i <= end; i++)
		basicCost += cost[i];
	
	if (end == start + 1)
		res = basicCost;
	else
	{
		for (int i = start; i < end; i++)
			res = min(res, minCost(start, i) + minCost(i + 1, end));
		res += basicCost;
	}
	dp[start][end] = res;
// printf("dp[%d][%d]: %d\n", start, end, dp[start][end]);
	return (dp[start][end]);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &K);
		for (int i = 1; i <= K; i++)
			scanf("%d", &cost[i]);
		memset(dp, -1, sizeof(dp));
		printf("%d\n", minCost(1, K));
	}
}