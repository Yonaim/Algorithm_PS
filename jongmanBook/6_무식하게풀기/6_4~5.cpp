// 6.5 소풍 문제를 해결하는 재귀 호출 코드

/*
문제: 남은 학생들에 대해서 친구끼리 짝을 지어준다
문제 조각: 남은 학생들 중 한 쌍 짝을 지어준다 

base case:
	- 남은 학생이 0명 (success)

찾아야하는 것은 조합이다. 중복으로 세는 것을 방지하기 위해 오름차순으로 순서를 고정한다
*/

int n;
bool areFriends[10][10];

// 짝을 이미 찾은 학생들에 대해 taken[i] = true로 저장해둔다. 찾지 못한 학생은 false
int countPairings(bool taken[10])
{
	// 순서 고정을 위해 짝이 지어지지 않은 학생들 중 가장 작은 번호를 갖는 학생을 찾는다
	int firstFree = -1;
	for (int i = 0; i < 10; i++)
		if (taken[i] == false) {
			firstFree = i;
			break ;
		}
	if (firstFree == -1)
		return (1);

	int count = 0;
	for (int i = firstFree; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
		// 이번엔 기저 사례가 아니라 반복문 돌면서 더 깊이 들어가도 되는지 여부를 판별했음
			if (areFriends[i][j] == true) {
				taken[i] = taken[j] = true;
				count += countPairings(taken);
				taken[i] = taken[j] = false;
			}
		}	
	}
	return (count);
}