// 6.6 게임판 덮기 문제를 해결하는 재귀 호출 알고리즘

/*
모든 경우의 수를 확인한다.
중복으로 세는 것을 방지하기 위해 왼쪽 위에 있는 칸을 우선적으로 채운다.

한 칸을 채우기 위해 퍼즐 조각을 배치할 수 있는 방법은 4가지이다. 이를 미리 const로 저장해둔다

블록을 세팅하는 함수를 따로 만들어둔다. DFS를 하기 위해 위 4가지 타입 중 원하는 형태로 블록을 놓고, 
'정상적으로 블록이 놓여졌다면' 재귀 호출 한 후 블록을 제거해야한다.
'특정 칸을 기준으로 원하는 형태로 블록을 어떻게 한다'가 공통적이므로 블록 놓기/제거하기를 한 함수에서 하도록 할 수 있다. (코드절약)
이때 원하는 형태로 블록을 놓는데 실패할 수도 있다(이미 블록이 그 위치에 있거나, 판을 벗어나거나 등의 이유)
만약 블록을 놓던 중 그걸 깨달았다면 놓았던 블록은 다시 제거해야할 것이다
그걸 포함해서 세팅 함수를 작성할 수도 있지만... 안 그래도 두 가지 역할을 동시에 하는 판에 코드가 복잡해진다.
-> 원하는 형태로 블록을 놓는데 실패해야하는 상황이라고하더라도 그냥 일단 놓고, 재귀 호출은 하지 않고 제거한다.
이렇게 하면 적은 코드량으로 원하는 바를 달성할 수 있다...

base case: 모든 칸을 전부 채운 경우 -> 1

*/

#include <stdbool.h>
#include <vector>

using namespace std;

// 주어진 한 칸을 덮을 수 있는 4가지 방법
const int coverType[4][3][2] = {
	{{0, 0}, {1, 0}, {0, -1}},
	{{0, 0}, {1, 0}, {1, -1}},
	{{0, 0}, {0, -1}, {1, -1}},
	{{0, 0}, {-1, -1}, {0, -1}},
};

// vector<vector<int> > 는 2차원 벡터이다.

// board의 (x, y)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다
// delta = 1이면 덮고, delta = -1이면 덮었던 블록을 없앤다
// 만약 블록이 제대로 덮이지 않은 경우 false 반환
bool set(vector<vector<int> >& board, int x, int y, int type, int delta)
{
	bool ok = true;
	// 해당하는 type에서 i번째 칸을 세팅한다
	for (int i = 0; i < 3; i++)
	{
		const int nx = x + coverType[type][i][0];
		const int ny = y + coverType[type][i][1];
		// 블록을 세팅하려고 했던 칸이 유효하지 않은 경우 아무것도 하지 않는다 
		if (!(0 <= nx && nx <= board.size()) || !(0 <= ny && ny <= board.size()))
			ok = false;
		// 이 칸이 유효하다면 일단 놓는다.
		// 다만 이미 블록이 놓아져있었던 경우는 세팅을 할 수가 없었던 것이므로 false를 반환한다(다음 블록을 놓는 것은 계속 된다)
		else
		{
			board[ny][nx] += delta;
			if (board[ny][nx] > 1)
				ok = false;
		}
	}
	return (ok);
}

// board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환하는 함수
	// board[i][j] = 0인 경우 빈 칸이다.
int cover(vector<vector<int> >& board)
{
	// 아직 덮이지 않은 칸 중 가장 왼쪽 위에 있는 것을 찾는다.
	int x = -1;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
			if (board[i][j] == 0)
			{
				x = j; y = i;
				break ;
			}
		if (x != -1) break ;
		// 이미 찾았으면 더 확인할 필요가 없다. 이중반복문이므로 한번 더 break
	}

	if (x == -1)
		return (1);

	int ret = 0;
	for (int type = 0; i < 4; i++)
	{
		if (set(board, x, y, type, 1) == true)
			ret += cover(board);
		set(board, x, y, type, -1);
	}
	return (ret);
}
