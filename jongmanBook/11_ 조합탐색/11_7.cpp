// 11.7 블록의 회전된 형태를 계산하고 상대좌표의 목록으로 변환하기

/*
블록이 어떤 형태로 들어올지 실행 전까지는 알 수 없으므로 input을 받으면 미리 전처리해둔다
*/

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

vector<vector<pair<int, int>>> rotations; // 블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해둘 벡터
int blockSize;                            // 블록의 크기

// 2차원 배열 arr를 시계방향으로 90도 돌린 결과를 반환
vector<string> rotate(const vector<string> &arr)
{
    vector<string> ret(arr[0].size(), string(arr.size(), ' '));
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++)
            ret[j][arr.size() - i - 1] = arr[i][j];
    return (ret);
}

// block의 네 가지 회전 형태를 만들고 이들을 상대 좌표 목록으로 변환
void generateRotations(vector<string> block)
{
    rotations.clear();
    rotations.resize(4);
    for (int rot = 0; rot < 4; rot++)
    {
        int originY = -1, originX = -1;
        for (int i = 0; i < block.size(); i++)
        {
            for (int j = 0; j < block[i].size(); j++)
            {
                if (block[i][j] == '#')
                {
                    if (originY == -1)
                    {
                        originX = i;
                        originY = i;
                    }
                }
                // 각 칸의 위치를 원점으로부터의 상대좌표로 표현
                rotations[rot].push_back(make_pair(i - originY, j - originX));
            }
        }
        // 블록을 시계 방향으로 90도 ㅚ전
        block = rotate(block);
    }

    // 네 가지 회전 형태 중 중복이 있을 경우 이를 제거한다
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

    // 블록이 몇 칸짜리인지 저장
    blockSize = rotations[0].size();
}