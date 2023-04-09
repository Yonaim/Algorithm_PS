// 7.8 울타리 잘라내기 문제를 해결하는 분할 정복 알고리즘

/*
우리의 과제: 가장 큰 직사각형의 넓이 구하기.

이를 분할 정복으로 풀기 위해 문제를 절반으로 나눈다. 
단 절반으로 나눠서 '왼쪽 부분 문제'와 '오른쪽 부분 문제'로 나눴을 때 고려해야하는 답이 있다.
바로 왼쪽 부분 문제와 오른쪽 부분 문제 둘에 가장 큰 직사각형이 걸쳐있을 경우이다.

	1. 가장 큰 직사각형은 왼쪽 부분 문제에 있다
	2. 가장 큰 직사각형은 오른쪽 부분 문제에 있다
	3. 가장 큰 직사각형은 왼쪽, 오른쪽 부분 문제 모두에 걸쳐 있다

3가지 중 가장 큰 값을 리턴하면 될 것이다.
생각을 해보면, 부분 문제의 base case는 판자의 개수가 단 하나만 남았을 때이므로
일반적인 상황이라면(해답 직사각형을 이루는 판자의 개수가 2개 이상이라면) 결국에 왼쪽 부분 문제와 오른쪽 부분 문제 둘에 답이 걸쳐있는 케이스가 선정될 것이다

base case:
	판자의 개수 = 1

1, 2는 재귀 호출하면 되고 3은 주어진 상황에서 직접 구해야한다.
(사실 재귀 호출된 1, 2도 결국에 내부적으로 3의 상황을 구하게 될 것이다.
앞서 언급한대로 일반적인 상황이라면 3이 리턴되어버리겠지...결국 3이 이 문제의 핵심이다)
*/

/*
그래서  '3. 가장 큰 직사각형은 왼쪽, 오른쪽 부분 문제 모두에 걸쳐 있다'
이때의 가장 큰 직사각형 넓이는 어떻게 구할 수 있을까?

일단 왼쪽, 오른쪽 부분 문제 모두에 걸쳐있으므로, 왼쪽 오른쪽 부분 문제의 경계를 기준으로 좌, 우 판자는 무조건 포함한다.
(즉 왼쪽 부분 문제의 가장 오른쪽 판자 + 오른쪽 부분 문제의 가장 왼쪽 판자)

이 두 개의 판자부터 시작해서 좌측 판자를 선택할지 우측 판자를 선택할지 결정을 맨끝(맨 좌측 혹은 맨 우측)에 도달할 때까지 반복하고,
매 선택 결과의 넓이를 지금까지 결정했던 결과 값과 비교하여 큰 값을 살려(?)두어야 한다.

(판자를 확장할 때마다 높이는 아무리 잘해도 그대로 유지되거나 작아질 수밖에 없으므로, 난 처음에 맨 끝까지 도달하지 않아도 된다고 생각했다.
근데 직사각형의 넓이를 결정하는 요인은 높이만 있는 것이 아니라 너비도 있다. 판자를 확장할 때마다 너비는 1씩 증가한다는 사실을 간과한 것이다!!...
무튼 높이는 낮은데 너비가 매우 길어서 넓이 값이 큰 경우가 있을 수 있으므로 무조건 맨 끝까지 도달할 때까지의 케이스들의 값을 모두 구해봐야한다.)
*/

#include <string>
#include <vector>

using namespace std;

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))