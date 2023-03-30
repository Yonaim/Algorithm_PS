// 7.4 카라츠바의 빠른 정수 곱셈 알고리즘

/*
7.3의 목적도 이번 과제와 마찬가지로 큰 두 수끼리 곰셈해서 그 값을 반환하는 함수를 작성하는 것이었다.
그렇지만 이번에는 분할 정복을 사용한다.

두 수 a와 b가 각각 256자리 수라고 하자.
그리고 이 256자리 수들을 첫 128자리와 뒤 128자리의 수로 나눈다.
	a = a1 * 10^128 + a0
	b = b1 * 10^128 + b0

그러면 a * b를 아래처럼 나타낼 수 있다.

a * b	= (a1 * 10^128 + a0) * (b1 * 10^128 + b0)
		= ((a1 * b1) * 10^256) + ((a0 * b1) + (a1 * b0)) * 10^128 + (a0 * b0) 

두 수의 곱셈 a * b를 구하기 위해서 또 다시 두 수의 곱셈인
(a1 * b1), (a0 * b1), (a1 * b0), (a0 * b0) 
의 값이 필요하다. 즉 재귀 호출이 4번 이루어진다.

그리고 이대로 실행하면 전체 수행 시간은 7.3에서 작성했던 코드와 같이 여전히 O(n^2)이고,
분할 정복을 사용하는 의미가 없다...

카라츠바는 위 식을 최적화할 수 있는 방법을 발견했다.
수학적으로
(a0 + a1) * (b0 + b1) = (a0 * b0) + (a0 * b1) + (a1 * b0) + (a1 * b1)
임은 자명하다. 근데 그러면
	z2 = (a1 * b1)
	z1 = (a0 * b1) + (a1 * b0)
	z0 = (a0 * b0)
라고 했을 때,

(a0 + a1) * (b0 + b1)	= (a0 * b0) + ((a0 * b1) + (a1 * b0)) + (a1 * b1)
						= z0 + z1 + z2
이다.
즉, (a0 + a1) * (b0 + b1)과 z0과 z2의 값을 알고 있으면 z1을 구할 수 있다.
기존에는 z1을 구하기 위해 두 번의 재귀 호출 (a0 * b1), (a1 * b0)이 이루어져야 했는데,
이 발견으로 인해 한번의 재귀 호출 (a0 + a1) * (b0 + b1)만 있어도 z1을 구할 수 있게 되었다. 

이제 실행시간은 O(n^2)보다 짧을 것이다.
*/

#include <vector>
#include <stdio.h>

using namespace std;

// 7.3에서 작성한 multiply() 함수를 사용. (단 음수도 처리 가능해야하므로 내 건 안됨...) 
vector<int> multiply(vector<int>& a, vector<int>& b)

// a += b * (10^k)를 하는 함수
void addTo(vector<int>& a, vector<int>& b, int k);

// a -= b를 하는 함수
void subFrom(vector<int>& a, vector<int>& b);

// 두 긴 정수의 곱을 반환하는 함수
/*
base case:
	1. a나 b가 둘중 하나라도 0인 경우
	2. 두 수가 비교적 작은 수인 경우 (자릿수가 50 이하)
*/
vector<int> karatsuba(vector<int>& a, vector<int>& b)
{
	int aLen = a.size();
	int bLen = b.size();

	if (aLen < bLen)
		return (karatsuba(b, a));

	if (aLen == 0 || bLen == 0)
		return vector<int>();
	if (aLen <= 5)
		return multiply(a, b);
	
	int half = aLen / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
							// ?? 왜 min<int>(b.size(), half)지?
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	
	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	
	// a0 += a1
	// b0 += b1
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	
	// z1 = (a0 * b0) - z0 - z2;
	vector<int> z1 = karatsuba((a0 + a1), (b0 + b1));
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return (ret);
}

int main()
{
	vector<int> a;
	vector<int> b;

	a.push_back(3);
	a.push_back(2);
	a.push_back(1);

	b.push_back(6);
	b.push_back(5);
	b.push_back(4);

	vector<int> c = karatsuba(a, b);
	for (int i = c.size() - 1; i >= 0; i--)
		printf("%d", c[i]);
}