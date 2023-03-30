#include <stdio.h>
#include <math.h>

typedef struct matrix_ {
	int	m[5][5];
} matrix;
// c에서는 배열을 복사해 인자로 넘길 수 없으므로 구조체로 만들어둔다

int 		N;
long long	B;
matrix		m_ori = {0, };
const int	MOD = 1000;

matrix	mul_matrix(matrix m2, matrix m1)
{
	matrix m = {0, };

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				m.m[i][j] += m2.m[i][k] * m1.m[k][j];
			}
			m.m[i][j] %= MOD;
		}
	}
	return (m);
}

matrix	square_matrix(matrix m, long long exp)
{
    matrix interm_m;
    
	if (exp == 1)
		return (m);
	else if (exp == 2)
		return (mul_matrix(m, m));
	interm_m = square_matrix(m, exp / 2);
	if (exp % 2 == 1)
        return (mul_matrix(mul_matrix(interm_m, interm_m), m_ori));
	else
        return (mul_matrix(interm_m, interm_m));
}

int main()
{
	matrix m_res;

	scanf("%d %lld", &N, &B);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &m_ori.m[i][j]);
			m_ori.m[i][j] %= MOD;
		}
	}
	m_res = square_matrix(m_ori, B);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", m_res.m[i][j]);
		printf("\n");
	}	
}

// 제곱하다보면 자료형이 담을 수 있는 수의 상한선을 넘어갈텐데 이에 대한 처리?
	// 예를 들어, 4의 제곱수를 100으로 나눈 나머지를 출력한다고 친다
		// 256 (4^4) -> 56
		// 1024 (4^5) -> 24
		// 4096 (4^6) -> 96
		// 16384 (4^7) -> 84
	// 관찰해보면 나누는 수 100 안의 범위 안에(즉 나머지 값이 되는 수) 향을 주는 것은
	// 어차피 두 자리 수(~99)까지뿐이다.
		// 가령, 256(=4^4)에서 56만 떼 4를 곱했을 때 값은 224이고
		// 이를 100으로 나눈 나머지는 4^5를 100으로 나눴을 때 나머지인 24이다.
	// => 곱한 후 1000으로 나누는 작업을 반복하면 된다.

// 이걸 분할정복으로 어떻게?
	// 무식하게 계속 제곱해도 됨
	// 근데 3^8 = 3^4 * 3^4로 생각할 수 있음. 반씩 나눠서~