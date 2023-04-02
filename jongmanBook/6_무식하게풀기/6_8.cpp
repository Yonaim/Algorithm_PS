// 6.8 시계 맞추기 문제를 해결하는 완전 탐색 알고리즘

/*
문제 분석

- 어떤 스위치를 특정 횟수만큼 누르는 조합이 있을 때 누르는 순서는 관계없이 결과가 같다.
- 한 스위치마다 누르는 횟수는 최소 0번, 최대 3번이다. (4번 누르면 어차피 원래대로 돌아간다)

=> 모든 스위치에 대해 0~3번 누르는 경우를 전부 확인한다.
한 개의 스위치당 4개의 케이스가 있고 스위치는 총 10개이므로,
확인할 케이스의 개수는 4^10개가 된다. 이는 컴퓨터가 충분히 빠르게 연산할 수 있는 양이다.
*/

#include <stdbool.h>
#include <limits.h>

#define min(a,b)  (((a) < (b)) ? (a) : (b))

// const int MaxSwitch = 10;
// const int MaxClock = 16;
int move[10][16];
int answer = INT_MAX; // 만약 하나도 답이 없는 경우에는 answer가 그대로 INT_MAX값을 가질 것이다. 즉 answer = INT_MAX라면 답이 없는 상황으로 간주한다

/*
base case:
	- 더 이상 조작할 스위치가 없는 경우

최적의 해를 찾아야하므로 할 수 있는 최적화(나의 생각):
	원하는 상황이 된 경우 더 이상 깊숙히 들어가지 않는다(그 다음 버튼들을 누를 생각을 않는다).
	왜냐하면 어차피 더 버튼을 누르기만 할 뿐이기 때문에, 더 깊숙히 들어가봤자 지금 나온 이 해를 넘는 최적의 해가 존재하지 않기 때문이다.
*/
void adjustClock(int curSwitch, int clockStat[16], int pushCnt)
{
	// base case
	if (isWantedStat(clockStat) == true)
	{
		answer = min(answer, pushCnt);
		return ;	
	}
	if (curSwitch == 10)
		return ;

	// 현재 스위치에 대해서 0~3번 누른다
	for (int i = 0; i < 4; i++)
	{
		// setSwitch(clockStat, move[curSwitch], +3);
		// adjustClock(curSwitch + 1, clockStat, pushCnt + i);
		// setSwitch(clockStat, move[curSwitch], -3);

	// 아~~나는 위처럼 스위치 눌러주고, 재귀 탐색, 원상복귀를 하였는데,
	// 이 문제에서는 현 상황에서 선택할 수 있는 경우의 수(버튼을 누를 수 있는 횟수)에 따른 각 경우가
	// 완전히 동떨어져있는 것이 아니므로 아래와 같이 처리도 가능하다.
		// 즉 3번 누르는 상황 = 2번 누른 상황에서 1번 더 누른거랑 동일
	// 그리고 4번 누르면 어차피 원상복귀 된다. clockStat 정보를 계속 건드리고 있음에도 다시 원래대로 돌려둘 필요가 없다
		adjustClock(curSwitch + 1, clockStat, pushCnt + i);
		pushSwitch(clockStat, move[curSwitch]);
	}
}

//------------------------------------------------------------------------------

/*
책 클론코딩. 

해를 저장하기 위한 전역변수를 사용하지 않는다는 점이 특징.
그래서 반환값이 곧 해가 되는 형태이다.


*/

#include <vector>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

// 현재 시계들의 상태와 이번에 누를 스위치의 번호를 넘겨 받고,
	// 남은 스위치들을 눌러 clocks의 상태를 원하는 상태로 맞출 수 있는 최소 횟수를 반환
	// 만약 불가능하다면 return값은 INF(= INFINITE = IMPOSSIBLE)가 됨
		// INT_MAX로 한다면 이후 해당 값을 더하는 연산을 하면서 오버플로우가 날 수 있으므로
		// 데이터형의 경계값이 아니면서 불가능한 값으로 IMPOSSIBLE값을 결정해둔다
			// 이 문제의 경우 최대로 값이 리턴되어봤자 (3 * 10) + INF이다. (10번째 스위치까지 전부 3번 누르고 불가능하다는 것을 깨달은 경우)
int solve(vector<int>& clocks, int swtch)
{
	if (swtch == SWITCHES)
		return (areAligned(clocks) ? 0 : INF);
	
	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}
	return (ret);
}