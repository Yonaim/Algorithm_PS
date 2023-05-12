// 11.8 게임판 덮기 2 문제를 해결하는 완전 탐색 알고리즘

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

vector<vector<pair<int, int>>> rotations; // 블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해둘 벡터
int blockSize;                            // 블록의 크기

int boardH, boardW;
vector<string> board;

int covered[10][10];

int best;

// 블록을 놓을 때 이미 놓인 블록이나 검은 칸과 겹치면 거짓을, 아니면 참 반환
bool set(int y, int x, const vector<pair<int, int>> &block, int delta);

// placed: 지금까지 놓은 블록의 수
void search(int placed)
{
    // 아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸 찾기
    int y = -1, x = -1;
    for (int i = 0; i < boardH; i++)
    {
        for (int j = 0; j < boardW; j++)
            if (covered[i][j] == 0)
            {
                y = i;
                x = j;
                break;
            }
        if (y != -1)
            break;
    }

    // base case: 게임판의 모든 칸을 처리한 경우
    if (y == -1)
    {
        best = max(best, placed);
        return;
    }
    for (int i = 0; i < rotations.size(); i++)
    {
        if (set(y, x, rotations[i], 1))
            search(placed + 1);
        set(y, x, rotations[i], -1);
    }
    covered[y][x] = 1;
    search(placed);
    covered[y][x] = 0;
}

int solve()
{
    best = 0;
    for (int i = 0; i < boardH; i++)
    {
        for (int j = 0; j < boardW; j++)
            covered[i][j] = (board[i][j] == '#' ? 1 : 0);
    }
    search(0);
    return (best);
}