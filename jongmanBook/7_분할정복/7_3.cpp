// 7.3 두 큰 수를 곱하는 O(n^2) 알고리즘

/*
초등학교 산수 시간에 배운 방법을 그대로 사용한다.

각 자릿수에 대해 곱셈의 합을 누적해두고, 두 자리 수 이상이 되는 값들에 대해 올림 처리(normalize)한다.
이때 i번째 자리에 대해서 10^i를 곱해 실질적인 수를 나타낼 수 있는 것이 편리하므로, 벡터에 저장해둘때 순서를 반대로 저장해둔다.
예를 들어 숫자 '123'는 [3, 2, 1]이 된다.
*/

#include <stdio.h>
#include <vector>

using namespace std;

// 자릿수 올림을 처리하는 함수
void normalize(vector<int>& num)
{
	// num.push_back(0);
		// ?? 이거 없어도 되는거 아닌가

	for (int i = 0; i < num.size() - 1; i++)
	{
		num[i+1] += num[i] / 10;
		num[i] %= 10;
	}

	// 필요없는 0 제거
	while (num.size() > 1 && num.back() == 0)
		num.pop_back();
	// 처음에 벡터의 크기를 (a.size() + b.size() + 1)로 꽤나 넉넉하게 할당 했기 때문에 비는 0이 있을 수 있음.
		// 예를 들어 123 * 456과 같은 예시의 경우 결과 벡터 안 수를 순서대로 수를 나열하면 8806500가 됨.
		// 맨 뒤쪽의 0 두 개가 필요없는 0이 됨.
		// 뒤쪽에서부터 봤을 때 0이 아닌 수가 가장 큰 자릿 수의 수가 되므로, 뒤쪽에서 봤을 때 0이 아닐때까지 pop_back 해버리면 됨.
}

// 두 수 a, b를 곱하는 함수
// 123 * 456 = multiply([3,2,1],[6,5,4]) = [8,8,0,6,5] = 56088
vector<int> multiply(vector<int>& a, vector<int>& b)
{
	vector<int> ret(a.size() + b.size() + 1, 0);
		// a.size() + b.size() + 1개의 원소(기본값 0)를 가지는 벡터 선언
	
	// 모든 자리의 수 쌍을 곱해 더함으로써 각 자릿수에 해당 하는 총합을 구한다 
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			ret[i + j] += a[i] * b[j];
	normalize(ret);
	return (ret);
}

// int main()
// {
// 	vector<int> a;
// 	vector<int> b;

// 	a.push_back(3);
// 	a.push_back(2);
// 	a.push_back(1);

// 	b.push_back(6);
// 	b.push_back(5);
// 	b.push_back(4);

// 	vector<int> c = multiply(a, b);
// 	for (int i = c.size() - 1; i >= 0; i--)
// 		printf("%d", c[i]);
// }