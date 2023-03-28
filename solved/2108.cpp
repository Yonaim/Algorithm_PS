#include <stdio.h>
#include <algorithm>
#include <cmath>

const int MaxN = 500000;
const int MaxValue = 4000;
const int valueOffset = MaxValue;
int N;
int arr[MaxN];
long long sum = 0;
int appear[MaxValue * 2 + 1] = {0, };

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	std::sort(arr, &arr[N]);

	for (int i = 0; i < N; i++)
		sum += arr[i];
	float mean = (float)sum / N;
	printf("%d\n", (int)round(mean));

	printf("%d\n", arr[N / 2]);

	for (int i = 0; i < N; i++)
		appear[arr[i] + valueOffset]++;

	int maxAppearCnt = 0;
	int maxAppearValue;
	int nth = 1;
	for (int i = 0; i < (MaxValue * 2 + 1); i++)
	{
		if (appear[i] > maxAppearCnt)
		{
			maxAppearValue = i - valueOffset;
			maxAppearCnt = appear[i];
			nth = 1;
		}
		else if (appear[i] == maxAppearCnt)
		{
			nth++;
			if (nth == 2)
				maxAppearValue = i - valueOffset;
		}
	}
	printf("%d\n", maxAppearValue);

	printf("%d\n", arr[N - 1] - arr[0]);
}