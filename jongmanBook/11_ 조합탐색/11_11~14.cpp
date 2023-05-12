// 카쿠로 문제

/*
이렇게 특정한 제약에 해당하는 답을 찾는 문제를 제약 충족 문제(Constraint Satisfaction Problem)라고 부른다.

이 문제는 답이 하나 뿐인 문제라 '더 좋은 답'과 '더 나쁜 답'의 개념이 없으므로 앞서 최적화 문제들을 푸는 데 썼던 많은
기법들은 사용할 수 없다.

1. 제약 전파
답의 일부를 임의로든 뭐 어떻게 잘 생성하면 문제의 조건에 의해 나머지 답에 대해서 알게 되는 것을 제약 전파(constraint
propagation)이라고 부른다. 제약 전파를 이용하면 탐색해야 할 탐색 공간의 수가 크게 줄어든다.

2. 채울 순서 정하기
- 어느 빈칸부터 먼저 채워나갈 것인가 (variable ordering, 변수 순서 정하기)
- 이 빈칸에 어떤 숫자부터 채워나갈 것인가 (value ordering, 값 순서 정하기)

예를 들어 빈칸 2개가 있는 라인과 5개가 있는 라인이 있을 때 당연히 전자를 먼저 푸는게 유리할 것이다.
이렇게 순서를 잘 정하면 제약 전파를 더 용이하게 하고, 답을 더 빨리 찾을 수 있다.

variable ordering, 변수 순서 정하기 -> 해당

*/

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int getSize(int mask); // mask에 속한 원소들의 개수 반환
int getSum(int mask);  // mask에 속한 원소들의 합을 반환

/*

*/

// 하나의 라인에서 연속된 len칸의 합이 sum이고 이 칸들에 이미 쓰인 수의 집합이 known일 때, 나머지 칸에 들어갈 수 있는
// 숫자의 집합을 반환 예를 들어 15 = ? + ? + ? + 3인 경우 합이 12가 되는 3개의 숫자의 '집합'을 반환하면 된다. 이
// 함수에서 반환된 집합(candidates)의 교집합을 통해 칸에 들어갈 수를 알 수 있다
int getCandidates(int len, int sum, int known)
{
    // 비트마스크를 이용해 정수의 집합을 표현 (i번째 숫자가 들어있다면 i번째 비트가 켜있음, i의 범위는 1~9)
    // allSets를 10진수로 해석했을 때 1024 미만의 짝수와 {1,2 ... 9} 부분집합 간 1:1 대응이 성립하게 된다!
    int allSets = 0;

    // 0 ~ 1024 범위의 짝수가 {1,2 ... 9} 부분집합과 1:1 대응되고 있으므로
    // 아래 반복문으로 모든 부분집합을 생성해볼 수 있다.
    for (int set = 0; set < 1024; set += 2)
        // known을 포함하고, 크기가 len이며, 합이 sum인 집합을 모두 찾는다
        if ((set & known) == known && getSize(set) == len && getSum(set) == sum)
            allSets |= set;
    // known에 속한 숫자들은 제외하고 리턴
    return (allSets & ~known);
}

// 11.2 카쿠로에서 후보의 수를 미리 계산하는 알고리즘

int candidates[10][46][1024];
// candidates[len][sum][known] = getCandidates(int len, int sum, int known)

void generateCandidates()
{
    memset(candidates, 0, sizeof(candidates));
    for (int set = 0; set < 1024; set += 2)
    {
        // 집합의 크기와 원소의 합 계산
        int l = getSize(set);
        int s = getSum(set);

        // set의 모든 부분집합에 대해 candidates[][][]를 갱신
        int subset = set;

        while (true)
        {
            // 숫자 하나의 합이 s이고, 이미 subset 숫자가 쓰여 있을 때 전체 숫자의 집합이 set이 되도록 나머지 숫자를
            // 채워넣을 수 있다.
            candidates[l][s][subset] |= (set & ~subset);
            if (subset == 0)
                break;
            subset = (subset - 1) & set;
        }
    }
}

// 11.14 카쿠로 문제를 해결하는 조합 탐색 알고리즘

bool search()
{
    int y = -1, x = -1, minCands = 1023;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; i < n; j++)
        {
            if (color[i][j] == WHITE && value[i][j] == 0)
            {
                int cands = getCandCoord(i, j);
                if (getSize(minCands) > getSize(cands))
                {
                    minCands = cands;
                    y = i;
                    x = j;
                }
            }
        }
    }
    if (minCands == 0)
        return (false);
    // ...
}