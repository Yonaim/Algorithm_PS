// 10.1 회의실 예약 문제를 해결하는 탐욕법 알고리즘

/*
<탐욕 알고리즘 정당성 증명>

	1. 탐욕적 선택 속성(greedy choice propert)
		- 답의 모든 부분을 고려하지 않고 탐욕적으로만 선택하더라도 최적해를 구할 수 있다.
		- 증명해야만 하는 속성

	2. 최적 부분 구조
		- 부분 문제의 최적해로부터 전체 문제의 최적해를 만들 수 있다
		- 대게 증명할 필요는 없는 자명한 속성
*/

#include <string>
#include <vector>

using namespace std;

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*
처음에 특정 조건으로 객체들을 정렬해두고,
선택을 마칠때마다 다음 선택에서는 해당 객체를 제외한 나머지 객체들 중에서 선택하도록 기록을 해둔다.
처음에 정렬을 해두면 나중에 탐색할 때 굳이 더 시간을 들이지 않아도 된다.
*/

int n; // 회의의 수
int begin[100], end[100]; // 각 회의의 시작, 끝시간

int schedule()
{
	// begin, end 페어를 end가 작은 순으로 정렬 (=일찍 끝나는 순으로 정렬)
	vector<pair<int,int> > order;
	for(int i = 0; i < n; i++)
		order.push_back(make_pair(end[i], begin[i]));
		// end 기준으로 우선 정렬하기 위해 first가 end, second가 begin인듯
	sort(order.begin(), order.end());

	int earliest = 0; // 다음 회의가 시작할 수 있는 가장 빠른 시간
	int selected = 0; // 지금까지 선택한 회의 수
	for (int i = 0; i < order.size(); i++)
	{
		int meetingBegin = order[i].second;
		if (meetingBegin >= earliest)
		{
			earliest = order[i].first; // 다음 회의가 시작할 수 있는 가장 빠른 시간을 회의가 끝난 시간으로 교체
			selected++;
		}
	}
	return (selected);
}

/*
<동적 계획법 vs. 탐욕법>

탐욕법으로 최적해를 찾을 수 있는 문제들은 그 중 상당수가 dp로도 풀 수 있다.
왜냐면 '탐욕법으로 최적해를 찾을 수 있음 = 지금 한 단계만을 고려해도 답을 찾을 수 있다'이기 때문.
그러나 탐욕법은 dp에 비해 필요한 메모리, 시간이 현저히 작으므로 둘다 가능하다면 탐욕법을 선택하는게 좋다.
*/