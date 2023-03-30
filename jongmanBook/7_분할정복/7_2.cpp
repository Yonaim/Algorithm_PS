// 7.2 행렬의 거듭제곱을 구하는 분할 정복 알고리즘

/*
이것도 7.1이랑 다를 바가 없다. 
n번 제곱을 하고 싶으면, n/2 제곱된 행렬을 한번 구해서 그 행렬을 제곱하면 된다.
다만 행렬끼리 곱을 해야하므로 단순한 사칙연산으로는 안 끝나고 행렬의 곱셈 연산이 구현되어 있어야한다.
만약 이미 구현되어 있다고 가정한다면, 분할정복 논리 자체는 7.1과 똑같으므로 매우 단순한 코드로 끝낼 수 있다.

pow(M, n): 행렬 M을 n번 제곱하여 나온 행렬

base case:
	n = 0 -> 행렬 M과 같은 사이즈를 갖는 단위행렬(identity matrix)
*/

// n * n 행렬을 나타내는 클래스가 있다고 친다.
	// 이 클래스는 * 연산자 오버라이딩이 되어있고, size() 메서드로 행렬의 크기를 구할 수 있다.
class SquareMatrix;

// n * n 크기의 단위행렬을 반환하는 함수
SquareMatrix identity(int n);

// M^n을 반환하는 함수
SquareMatrix pow(SquareMatrix &M, int n)
{
	if (n == 0)
		return (identity(M.size()));
	
	if (n % 2 == 1)
		return (pow(M, n) * M);
	// dp를 사용하지 않기 때문에, 비슷한 크기의 문제로 나누는 것보다는
	// 한 조각과 나머지로 나누는 편이 더 연산량이 적다
	SquareMatrix half = pow(M, n / 2);
	return (half * half);
}
