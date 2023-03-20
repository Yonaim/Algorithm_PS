#include <iostream>

const int dx[4] = {-1, -1, 1, 1};
const int dy[4] = {1, -1, 1, -1};

int n;

void	travel(int x, int y){
	for (int dir = 0; dir < 4; dir++){
		int nx = x + dir[dx];
		int ny = y + dir[dy];
		if (nx < 0 || ny < 0 || nx > n || ny > n)

	}
}