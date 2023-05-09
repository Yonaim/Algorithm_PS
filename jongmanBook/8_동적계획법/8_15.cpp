// 8.15 Quantization 문제의 구현

/*
수열의 길이는 1~100이고, 사용할 수 있는 숫자의 수는 1~10개이다.
수열의 모든 수는 1000 이하의 자연수.

음...양자화에 사용하는 숫자값도 자연수이고 오차를 최소화한다는 문제의 특성상 그 범위는 1~1000가 될텐데,
1000 * 1000의 오차 제곱을 미리 다 구해두면 안되나? (1000000 = 100만가지)

그리고 ... 수열을 돌면서 모든 조합을 확인!! 해야하는데 너무 많긴하네......
*/

/*
결국에 평범한 완전탐색으로는 해결이 안되고, 답의 형태를 제한해야하는 문제이다.

- 오차 제곱이 최소일 때, 같은 숫자로 양자화되는 숫자들은 항상 인접해있다 (정렬 후 그 자리에서 묶을 수 있다)

위처럼 답의 형태를 제한하면, 이제 우리는 주어진 수열을 s(사용할 수 있는 숫자의 개수)개의 묶음으로 나누고,
각 묶음에 대해 오차 제곱의 합이 최소인 수를 구하면 된다.

quantize(from, parts): from번째 이후의 숫자들을 parts개의 묶음으로 묶을 때 최소 오류 제곱의 합

*/

/*
아니 미친 뭔 미분이 나와 ㅋㅋㅋㅋ
한 묶음에 대해 대표할 숫자를 정할 때 당연히 해당 묶음 내의 최소값부터 최대값을 전부 다 확인할 줄 알았는데
(왜냐면 어차피 수 범위가 작아서ㅇㅇ....)...

근데 말이 미분이지 그냥 최고차항이 양수인 2차식에서 최솟값을 갖는 점을 구하는거다.
대표 숫자를 m이라고 할때, 하나의 오차 제곱은 (m - n)^2과 같은 형태가 되므로
오차 제곱의 합을 m에 대한 2차식으로 나타낼 수 있다~...

식을 정리해서 확인해보면 m값이 한 묶음에 속한 숫자들의 평균일때 y값이 최솟값인 것을 알 수 있다.
*/

/*
그럼 이제 평균값을 구해야한다는 걸 알았는데...이것도 최적화가 가능하다.
바로 부분합을 미리 구해놓는 것...
매번 한 묶음에 속한 숫자들의 조합이 달라지므로 평균값은 계~속 반복해서 구해야하기 때문에
이렇게 0부터 i번째까지의 부분합을 미리 구해두고 써먹으면 시간을 절약할 수 있다. O(n) -> O(1)!

여기서는 2차식이 등장해서... 그냥 합뿐만 아니라 제곱의 합도 쓰게 된다.

자주 쓰게 되나보다. 17장에서 소개되는 기법이라고 한다~
*/

#include <string>
#include <vector>

using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

const int INF = 987654321;

int n;
int A[101];      // 양자화해야하는 수열(정렬된 상태)
int pSum[101];   // A[]의 부분합(0부터 i번째까지)을 저장한다.
                 // pSum[i] = A[0]+... A[i]
int pSqSum[101]; // A[]^2의 부분합(0부터 i번째까지)을 저장한다.

// 수열 A를 정렬하고, 그 부분합들을 구한다
void preCalculate()
{
    sort(A, A + n);

    pSum[0] = A[0];
    pSqSum[0] = A[0] * A[0];

    for (int i = 0; i < n; i++)
    {
        pSum[i] = pSum[i - 1] + A[i];
        pSqSum[i] = pSqSum[i] + (A[i] * A[i]);
    }
}

// A[l]...A[h] 구간을 양자화했을 때, 오차값 제곱의 합 최소값을 반환
int minSumOfErrorValueSqaure(int l, int h)
{
    // preCalculate에서 미리 구해둔 부분합을 이용해 l...h까지의 부분합을 O(1)의 시간에 구한다
    int sum = pSum[h] - (l == 0 ? 0 : pSum[l - 1]);
    int sqSum = pSqSum[h] - (l == 0 ? 0 : pSqSum[l - 1]);

    // 위에서 구한 sum을 사용해 평균값을 구한다.
    // 반올림을 위해 0.5를 더해줌
    int m = int(0.5 + (double)sum / (h - l + 1));

    // 오차값 제곱의 합을 구한다
    // sum((A[i] - m)^2)을 위에서 구한 sum, sqSum, m을 통해 빠르게 구한다
    int ret = sqSum - (2 * m * sum) + (m * m * (h - l + 1));
    return (ret);
}

int cache[101][11];

// A[from]부터가 남았고, 더 쪼갤 수 있는 조각의 수가 parts일때 최소 오차제곱값의 합
int quantize(int from, int parts)
{
    if (from == n) // 마지막에 도달함
        return (0);
    if (parts == 0) // 더 이상 쪼갤 수 없으므로 불가
        return (INF);

    int &ret = cache[from][parts];
    if (ret != -1)
        return (ret);

    ret = INF;
    for (int partSize = 1; from + partSize <= n; partSize++)
    {
        ret = min(ret,
					minSumOfErrorValueSqaure(from, from + partSize - 1)
					+ quantize(from + partSize, parts - 1));
    }
	return (ret);
}