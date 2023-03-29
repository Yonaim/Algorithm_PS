/*
ACAYKP
CAPCAK

모든 부분수열을 전부 확인하긴 해야한다.
근데 s1에서 부분수열 구함 -> s2에서 해당 부분수열이 존재하는지 확인
이건 조합 생성하고 해당 조합에 대해 전부 확인까지 하는 n^2 시간복잡도를 가지는 작업이다.

구해야하는 것에 집중한다.
s1을 끝까지 봄 + s2를 끝까지 봄
이 상황에서 부분수열의 길이이다.

s1을 뒤에서 한 글자 덜 봤다고 쳐보자. LCS(5, 6) = ACAYK, CAPCAK -> 4 (ACAK)
s2를 뒤에서 한 글자 덜 봤다고 쳐보자.  LCS(6, 5) = ACAYKP, CAPCA -> 3 (CAP, ACA)

LCS(6, 6)은 LCS(5, 6) 그리고 LCS(6, 5)를 모두 포함하고 있다.
	LCS(5, 6)는 LCS(6, 6)에서 s1[6]을 안 본 것이고
	LCS(6, 5)는 LCS(6, 6)에서 s2[6]을 안 본 것이다.
(*LCS(6, 6)은 길이가 4인 케이스 ACAK와 3인 케이스 CAP, ACA 모두를 포함하지만
LCS의 정의상 가장 긴 것만을 가리킨다.)

고찰1. LCS(6, 6) 구하기

LCS(5, 6)와 LCS(6, 5)의 값은 다르다.
LCS(5, 6)가 1 더 크다. 이가 의미하는 바는?
	- s2[6]가 부분수열에 포함되었다 (그래서 1 올라감)
	- s2[6]와 매칭되는 문자는 s1[5] 혹은 그 이전에 있다

s1[6]이 LCS값에 영향을 이미 준 값이 LCS(5, 6)이므로, 
죽었다 깨어나도 LCS(6, 6)는 LCS(5, 6)과 값이 같을 수밖에 없다.

------------------------------------------------

고찰2. LCS(5, 6) 구하기

LCS(4, 6) = ACAY, CAPCAK -> 3 (ACA)
LCS(5, 5) = ACAYK, CAPCA -> 3 (ACA)

LCS(5, 6)은 LCS(4, 6) 그리고 LCS(5, 5)를 모두 포함하고 있다.
그리고 LCS(4, 6)와 LCS(5, 5)의 값은 같다.
이건 무엇을 의미할까?
	- s1[5]는 LCS(5, 5)의 최장 부분수열에 포함되지 않는다
	- s2[6]도 마찬가지로 LCS(4, 6)의 최장 부분수열에 포함되지 않는다

...따라서 s1[5]과 s2[6]의 일치 여부에 따라 LCS(4, 6) 혹은 LCS(5, 5)에서 1을 더하거나 더하지 않고
LCS(5, 6)을 구할 수 있다.

//
LCS(5, 5)를 기준으로 생각해볼 때 s2에서 하나 더 체크해야한다. 즉 s2[6]을 추가로 체크해야한다.
근데 LCS(4, 6)와 LCS(5, 5)의 값이 같으므로, 죽었다 깨어나도 LCS(5, 5)에서 s1[5]는 카운팅이 안되었음을 알 수 있다.
즉 LCS(5, 6)에서 s1[5]과 s2[6]의 일치여부는 미지수이다...
그래서 확인해보니 s1[5] = s2[6]이다. 
따라서, LCS(5, 6) = LCS(5, 5) + 1
//

*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

const int MaxLen = 1000;
int dp[MaxLen + 10][MaxLen + 10];
char s1[MaxLen + 10];
char s2[MaxLen + 10];
char buf[MaxLen + 10];

/*
LCS(i, j): s1을 i번째 인덱스까지, s2를 j번째 인덱스까지 봤을 때 최장수열의 길이

만약 LCS(i - 1, j) == LCS(i, j - 1)라면,
	LCS(i, j) = LCS(i - 1, j) + (s1[i] == s2[j])

만약 LCS(i - 1, j) != LCS(i, j - 1)라면,
	LCS(i, j) = max(LCS(i - 1, j), LCS(i, j - 1))

base case:
	i = 0 혹은 j = 0일시, 0
*/

int LCS(int i, int j);

bool isThereNeedToCheck(int i, int j)
{
	bool isCounted_i; // LCS(i, j - 1)에서 i 카운팅의 여부
	bool isCounted_j; // LCS(i - 1, j)에서 j 카운팅의 여부

	isCounted_i = (LCS(i, j - 1) != LCS(i - 1, j - 1));
	isCounted_j = (LCS(i - 1, j) != LCS(i - 1, j - 1));

	return (isCounted_i == false && isCounted_j == false);
}

int LCS(int i, int j)
{
	if (i == 0 || j == 0)
		return (0);
	if (dp[i][j] != -1)
		return (dp[i][j]);

	int tmp;
	if (LCS(i - 1, j) == LCS(i, j - 1))
	{
		if (isThereNeedToCheck(i, j) == true)
			tmp = LCS(i - 1, j) + (s1[i] == s2[j]);
		else
			tmp = LCS(i - 1, j);
	}
	else
		tmp = max(LCS(i - 1, j), LCS(i, j - 1));
	dp[i][j] = tmp;
	return (dp[i][j]);
}

int main()
{
// 인덱스를 1로 시작하였던 기존 논리 흐름을 그대로 가져가기 위해, 한 칸씩 뒤로 밀어서 s1과 s2에 넣어야한다
// 원래는 memcpy로 복사해 넣었었는데 dst와 src의 메모리 영역이 겹쳐서 오류가 발생했다...
// 그래서 버퍼 사용하기로 함. 
	
	scanf("%s", buf);
	memcpy(s1 + 1, buf, strlen(buf));
	scanf("%s", buf);
	memcpy(s2 + 1, buf, strlen(buf));

	memset(dp, -1, sizeof(dp));
// dp 초기값을 여기서 넣어줘도 되긴 함.
// 하지만 나는 논리에 집중하기 위해 그건 문제 풀이가 익숙해진 후 나중 단계에서.
	s1[0] = 'a';
	s2[0] = 'a';

	printf("%d\n", LCS(strlen(s1) - 1, strlen(s2) - 1));
}

/*
반례...
ACAA
AAACBA

LCS(4, 6) =
		LCS(3, 6) = 3
		LCS(4, 5) = 3

집중해서 봐야할 것은 s1[4], s2[6]

LCS(3, 6)
	ACA
	AAACBA
	-> ACA
	s1[3], s2[6]이 마지막으로 영향을 미쳤다.

LCS(4, 5)
	ACAA
	AAACB
	-> AAA
	s1[4], s2[3]이 마지막으로 영향을 미쳤다.

... 우연히 주요 대상인 s1[4]와 s2[6]가 각 LCS값에 영향을 미치고 있다
즉 s1[4]과 s2[6]가 같은지 그 유무를 LCS(4, 6)에 포함시키면 안된다.

4 6
LCS(3, 6)값 카운팅에 s2[6]가 포함되었는지는 어떻게 아는가?
LCS(3, 5)값과 LCS(3, 6)를 비교해보면 된다.
둘의 값이 같으면 s2[6]가 LCS(3, 6)에 영향을 미치지 않은 것이다.
둘의 값이 다르면 s2[6]가 LCS(3, 6)에 영향을 미친 것이다.

LCS(4, 5)도 마찬가지 방법으로 확인한다.

*/
