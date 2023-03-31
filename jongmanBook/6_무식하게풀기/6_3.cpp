// 6.3 보글 게임판에서 단어를 찾는 재귀 호출 알고리즘

/*
게임판의 특정 위치에서 가능한 모든 순열을 살펴야한다. (완전 탐색)
그렇지만 한 자라도 단어의 일부에 해당하지 않으면 바로 뒤로 돌아갈 것이므로 깊이가 끝까지 깊어질 일은 많이 없을 것이다.

하나의 문제를, 한 조각 그리고 같은 형태의 subproblem으로 나눈다.
	한 조각 -> 이번 칸이 단어의 첫번째 문자가 맞는지 확인하기
*/

/*
깔끔한 재귀 코드 작성을 위해 예외상황도 기저사례(base case)로 간주하고 처리한다.
base case:
	- 현재 칸이 게임판에서 유효한 칸이 아님 (fail)
	- 현재 칸이 단어의 첫째 문자가 아님 (fail)
	- 단어가 끝남 (success)
*/

#include <string>

// 한 칸에서 이동을 하는 경우는 총 8가지이다. 위 아래 왼쪽 오른쪽, 대각선 4방향. (좌상 우상 좌하 우하)
const int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1};
const int dy[8] = {1, -1, 0, 0, 1, 1, -1, -1};

int xSize;
int ySize;
char board[xSize][ySize];

// 게임판의 (x, y)에서 시작하는 단어 word의 존재 여부를 반환
bool isHasWord(int x, int y, string &word)
{
	if (x >= xSize || y >= ySize)
		return (false);
	else if (board[x][y] != word[0])
		return (false);
	else if (word.length == 0)
		return (true);

	for (int i = 0; i < 8; i++)
	{
		// 현재 위치에서 남은 word의 부분이 전부 찾아지는가 확인
		if (isHasWord(x + dx[i], y + dy[i], word.substr(1)) == true)
			return (true);
	}
	// 현재 칸은 단어의 일부가 맞았지만 현재 칸의 주변 8칸은 모두 단어의 일부가 아니었을 경우
	return (false);
}

int main()
{
	char *str1 = "PRETTY";

	for (int i = 0; i < xSize; i++)
		for (int j = 0; j < ySize; j++)
			if (isHasWord(i, j, str1) == true)
				printf("The word '%s' is exist. started (%d , %d)\n", str1, i, j);
}