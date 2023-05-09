// 미나스 아노르 문제


/*
??....394p부터 이해가 안 가기 시작함....ㅠ
*/

#include <string>
#include <vector>
#include <cmath>

using namespace std;

// 10.5 미나스 아노르 문제의 원들을 중심각의 구간으로 바꾸기

const double pi = 2.0 * acos(0); // cos(pi/2) = 0이므로, acos(0) = pi/2 
int n;
double y[100], x[100], r[100];
pair<double,double> ranges[100];

void convertToRange()
{
	for (int i = 0; i < n; i++)
	{
		double loc = fmod((2 * pi) + atan2(y[i], x[i]), (2 * pi));
		// mod 연산을 사용해 -pi ~ pi의 값을 0 ~ 2pi 범위로 바꿔준다.
		// 이제 문제를 일직선상(1차원)으로 나타낼 수 있다
		double range = 2 * asin((r[i] / 2) / 8);
		ranges[i] = make_pair(loc - range, loc + range); // start and end
	}
	// 구한 구간들을 시작 지점(first)을 기준으로 오름차순 정렬한다.
	sort(ranges, ranges + n);
}

// 흠 근데...굳이 0 ~ 2pi 범위로 변환해줘야했을까?
// 물론 시작 지점이 좀 편해지지만...그냥 -pi ~ pi해도 될 것 같은데.
