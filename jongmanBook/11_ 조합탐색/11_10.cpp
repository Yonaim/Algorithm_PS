// 11.10 알러지 문제를 해결하는 두 번째 조합 탐색 알고리즘

/*
탐색의 형태를 바꿔 실행 시간 최적화를 꾀한다.
-> 각 음식의 선택 여부로 만들어지는 2^m개의 조합을 전부 확인하는게 아니라, 매 재귀호출마다 아직 먹을 음식이 없는 친구를
찾고 이 친구를 위해 어떤 음식을 만들 것인지를 결정한다.

기존 탐색은 모든 음식의 조합을 다 확인해야했고 그래서 음식의 개수가 m일때, 2^m개의 경우의 수였다.

그렇지만 사실 모든 음식의 조합을 다 확인할 필요는 없다. 문제의 특성을 생각해볼때, 반드시 볼 필요가 없는 조합들이
존재한다. 이를테면...어떤 조합에서 음식 a, b, c를 만들기로 결정했다고 할 때, 음식 a, b, c가 먹여살릴 수 있는(?) 친구들
이하의 친구들만을 포함하는 음식 d는 만들 필요가 없다.

무튼 이렇게 탐색을 하면 매우 빨라지는데, 그 이유는...

- '마지막 조각까지 결정한 뒤에도 배고픈 친구가 남지 않도록'(=항상 모든 친구가 먹을 음식이 있는 조합만을) 탐색하게 된다.
- 탐색의 깊이가 m 이하이게 된다. 모든 친구가 먹을 수 있는 상태면 더 깊이 들어가지 않고 탐색은 종료되니깐~
- 꼭 필요한 음식만 만들고, 필요없는 음식이 포함된 조합은 제외된다.
*/

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int n, m;

vector<int> canEat[50], eaters[50];
int best;

void search(vector<int> &edible, int chosen)
{
    // 간단한 가지치기
    if (chosen >= best)
        return;

    // 아직 먹을 음식이 없는 첫 번째 친구를 찾는다
    int first = 0;
    while (first < n && edible[first] > 0)
        first++;

    // 모든 친구가 먹을 음식이 있는 경우 종료한다
    if (first == n)
    {
        best = chosen;
        return;
    }

    // 이 친구가 먹을 수 있는 음식을 하나 만든다
    for (int i = 0; i < canEat[first].size(); i++)
    {
        int food = canEat[first][i];
        for (int j = 0; j < eaters[food].size(); j++)
            edible[eaters[food][j]]++;
        search(edible, chosen + 1);
        for (int j = 0; j < eaters[food].size(); j++)
            edible[eaters[food][j]]--;
    }
}