// 6.2 n개의 원소 중 m개를 고르는 모든 조합을 찾는 알고리즘

/*
'조합'을 찾는 것이므로, 중복으로 찾는 것을 방지하기 위해 오름차순으로 순서를 강제한다.
즉 모든 수열에서 어떠한 특정 자리값은 무조건 이전 자리들 숫자보다 값이 크다.
*/

#include <vector>

// n: 전체 원소의 수
// picked: 지금까지 고른 원소들의 번호
// toPick: 더 고를 원소의 수
// 앞으로 toPick개의 원소를 고르는 모든 방법을 출력한다.
void pick(int n, vector<int>& picked, int toPick)
{
	if (toPick == 0)
	{
		printPicked(picked);
		return ;
	}

	int smallest;
	if (picked.empty() == true)
		smallest = 0;
	else
		smallest = picked.back() + 1;

	for (int i = smallest; i < n; i++)
	{
		picked.push_back(i);
		pick(n, picked, toPick - 1);
		picked.pop_back(i);
	}
}