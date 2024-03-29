// 8.5 외발 뛰기 문제를 해결하는 동적 계획법 알고리즘

/*
이미 dp로 풀 수 있음을 앞에서 깨달았었다.
아는 방식 그대로 적용하면 된다.

단, 주의해야할 점이 비록 부분문제의 해답은 true or false이지만
부분문제의 해답을 저장해두기 위한 배열 cache는 *int형 배열*이어야한다는 점이다.
맨 처음에 -1로 초기화해줘야해서 그렇다.
*/

/*
어떤 문제를 dp로 풀 수 있는지 생각해볼 때 확인해야하는 사항
    - 각 부분 문제들의 참조적 투명성 여부
    - 부분 문제들이 중복되는가 << new!

암만 부분 문제들이 참조적 투명성 성질을 가져도, 중복되지 않는다면 그 해답을 저장하는 의미가 없다.
*/

/*
<부분 문제들이 중복되는지 여부 확인>

완전 탐색이 만드는 케이스의 수는 따로 계산을 해보지 않더라도 매우 많다는 걸 알 수 있다.

근데 위의 재귀호출 함수 jump(x, y)에 들어갈 수 있는 '부분 문제를 정의하는 두 인자 x, y'의 범위가
각각 1~100이다.
즉 부분 문제의 수는 많아도 100 * 100 = 10000개.

이상하지 않은가?? 확인해야하는 케이스(부분 문제들로 이루어진)의 수는 무수히 많은데 부분 문제는 단 10000개라니.
각 케이스들이 갖고 있는 부분 문제가 겹치고 있다는 것을 의미한다.

    부분 문제의 수(인자 범위에 의한 경우의 수)에 비해 확인해야하는 케이스(부분 문제들로 이루어짐)의 수가 많다
        -> 각 케이스들이 갖는 부분 문제가 중복됨.
*/

int cache[maxX][maxY];
int n, board[100][100];

bool jump(int x, int y)
{
    if (x >= n || y >= n)
        return (false);
    if (x == n - 1 && y == n - 1)
        return (true);

    if (cache[x][y] != -1)
        return (cache[x][y]);

    int jumpSize = board[x][y];
    cache[x][y] = jump(x + jumpSize, y) || jump(x, y + jumpSize);
    return (cache[x][y]);
}
