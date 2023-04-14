// 8.8 삼각형 위의 최대 경로 문제를 푸는 동적 계획법 알고리즘

/*
사실 dp문제를 꽤 풀었기 때문에 문제 슥 보고 바로 뒤쪽에서 소개되는 '입력이 걸러진' 적절한 풀이방법을 찾을 수 있었다.
*/


#include <string>
#include <vector>

using namespace std;

#define max(a,b)  (((a) > (b)) ? (a) : (b))

// 무식하게 메모이제이션 적용

int n, triangle[100][100];
int cache1[100][100][MAX_NUMBER * 100];

int path2(int y, int x, int sum)
{
	if (y == n - 1)
		return (sum + triangle[y][x]);
	
	int &ret = cache1[y][x];
	if (ret != -1)
		return (ret);
	return (ret = max(path1(y+1, x, sum), path1(y+1, x+1, sum)));
}

// 필요없는 입력을 거른 후
	// (부분문제를 정의하는 정보 중 '앞으로 풀어야 할 문제들에 대해' 필요없는 것 버리기)

int n, triangle[100][100];
int cache2[100][100];

int path2(int y, int x)
{
	if (y == n - 1)
		return (triangle[y][x]);
	
	int &ret = cache2[y][x];
	if (ret != -1)
		return (ret);
	return (ret = max(path2(y+1, x), path2(y+1, x+1) + triangle[y][x]));
}