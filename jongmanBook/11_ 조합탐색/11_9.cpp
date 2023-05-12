// 11.9 알러지 문제를 해결하는 첫 번째 조합 탐색 알고리즘

/*
지금까지와 같은 완전탐색(BFS) 방식으로 푼다
*/

#include <string>
#include <vector>

using namespace std;

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

int n, m;

vector<int> eaters[50];
// eaters[food]: food를 먹을 수 있는 친구들의 번호 벡터
int best;

// food: 이번에 고려할 음식의 번호
// edible: 지금까지 만들기로 결정한 음식들 중 i번째 친구가 먹을 수 있는 음식의 수
// chosen: 지금까지 만들기로 결정한 음식의 수
void slowSearch(int food, vector<int>& edible, int chosen)
{
	// 아주 간단한 가지치기
	if (chosen >= best) return ;

	// base case: 모든 음식에 대해 만들지 여부를 결정했을 경우,
	// 모든 친구가 음식을 먹을 수 있는지 확인하고 만약 그렇다면 최적해 갱신
	if (food == m)
	{
		// edible 배열의 값 중 0이 하나도 없다면(=모두가 먹을 수 있는 음식이 하나라도 있다면) 해가 될 수 있다.
		if (find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return ;
	}

	// 이번 food를 만들지 않기로 결정한 경우 (BFS)
	slowSearch(food + 1, edible, chosen);

	// 이번 food를 만들기로 결정한 경우 (BFS)
	for (int i = 0; i < eaters[food].size(); i++)
		edible[eaters[food][i]]++;
		// 벡터를 인덱스로 접근하고 있다.
		// i의 범위가 0 ~ eaters[food].size()-1이기 때문에 오류가 발생할 여지는 없다 
	slowSearch(food + 1, edible, chosen + 1);
	for (int i = 0; i < eaters[food].size(); i++)
		edible[eaters[food][i]]--;
}

/*
어떤 음식 선택 조합에 대해, 각자 먹을 수 있는 음식이 '하나라도' 있는지 알면되므로
edible은 bool 배열이어도 될 것 같은데 왜 int형일까?

-> 각 음식의 선택 여부에 따라 각 조합이 결정된다. 
만약 bool 배열이었다고 한다면...
BFS 탐색시 선택한 음식을 다음 코드라인에서 빼버리는 순간,
edible값 갱신을 위해 해당 음식뿐만 아니라 다른 음식들에 대해서도 또 다시 한번 '먹을 수 있는가'를 고려해야하므로 비효율적.
'먹을 수 있는 음식의 수'를 저장하는 int형 배열로 해두면 단순히 빼는 음식에 대해서만 고려하면 되므로 깊이 우선 탐색이 한결 편하다.
*/