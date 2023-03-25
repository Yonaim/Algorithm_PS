/*
모든 각 랜선들에 대해 확인하고픈 길이로 나누고 필요한 랜선의 개수 이상이 되는지 확인한다.

미리 다 저장하는 것보다는 하나하나 확인하는게 나을듯
*/

/*
랜선의 길이는 2^31 - 1보다 작거나 같은 자연수.
랜선은 최대 10000개이므로 curLen이 작을 때 오버플로우 발생할 수 있다.
*/

/*
curLen = 1로 두고 splitCnt < N이 될때까지 연산시켰더니 시간초과가 나왔다.
시간초과가 나지 않게 하기 위해서는 이진탐색 해야한다고 한다.
https://www.acmicpc.net/board/view/106778

일단 랜선의 길이를 다 더하고 N으로 나눠준다.
그걸 최대 길이로 간주. (최소 길이는 1)
splitCnt < N이 될때까지 이진 탐색 시킨다.

*/

#include <stdio.h>

const int MaxK = 10000;
int K, N;
unsigned int L[MaxK];
unsigned int answer;

int main()
{
	long long splitCnt;
	long long sum;
	long long mid, low, high; // 이진 탐색을 위함
	
	sum = 0;
	scanf("%d %d", &K, &N);
	for (int i = 0; i < K; i++)
	{
		scanf("%d", &L[i]);
		sum += L[i];
	}
	
	low = 1;
	high = sum / K;
	while (low <= high)
	{
		mid = (low + high) / 2;
		splitCnt = 0;
		for (int i = 0; i < K; i++)
			splitCnt += L[i] / mid;
		if (splitCnt >= N)
		{
			answer = mid;
			low = mid + 1;
		}
		else	
			high = mid - 1;
	}
	printf("%d\n", answer);
}