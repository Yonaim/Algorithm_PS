// 8.19 비대칭 타일링 문제를 해결하는 동적 계획법 알고리즘

/*
예제 8.16에서 풀었던 타일링 문제와 거의 동일한데 여기서는
'비대칭' 타일링 방법의 수를 구하라고 한다.

경우의 수를 구하는데, '특정 경우'만 구하라고 한다.

이 문제에서 구해야하는 '특정 경우'는 비대칭인 경우인데, 즉 모든 경우에서 대칭인 경우를 제외한 경우이다.
그런데 타일링이 대칭인 경우의 수는 그 특징을 이용하면 비교적 쉽게 구할 수 있다.
그렇기 때문에, 이 문제를 풀기 위해서 '비대칭' 타일링 방법을 구하는 완전 탐색 코드를 작성하는 것보다는
모든 경우에 대해서 경우의 수를 우선 구하고 대칭인 경우를 제외시키는 편이 낫다.
(예제 8.18에서도 특정 경우의 수를 구해야했지만 그 특정 경우의 정반대 상황 또한 완전탐색 밖에 방법이 없으므로,
이러나 저러나 완전탐색을 해야만 하는 상황이었다)

8.16에서 작성하였던 타일링하는 경우의 수를 세는 함수를 그대로 사용할 수 있다.

*/

/*
width 너비의 사각형을 채우는 '비대칭' 방법의 수를 반환한다
	- width가 홀수
		-> 가운데에 세로로 놓인 블럭 하나를 기준으로 대칭. 전체 경우에서 (width-1)/2인 경우를 뺀다
	- width가 짝수
		-> 가운데에 가로로 놓인 블럭 두개를 기준으로 대칭. 전체 경우에서 (width/2-1)인 경우를 뺀다
			혹은 가운데 금을 기준으로 대칭. 전체 경우에서 (width)/2인 경우를 뺀다
*/
int asymmetric(int width)
{
    int ret = tiling(width);

    if (width % 2 == 1)
   			// width가 홀수이므로 (width/2) = (width-1)/2
        return ((ret - tiling(width / 2) + MOD) % MOD);
    else
    {
        ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
        ret = (ret - tiling(width / 2) + MOD) % MOD;
										// MOD를 더해주는 이유??
    }
	return (ret);
}
/*
<MOD 연산 결과를 뺄 때 MOD를 더해주는 연산을 하는 이유>

tiling 함수의 반환값은 경우의 수이므로 무조건 양수이지만, MOD로 나눈 나머지 값을 반환하므로 그 범위는 1~MOD-1임.
즉 tiling 함수의 반환값끼리 뺄셈하는 연산을 할때, 좌항에 놓인 경우의 수가 더 많더라도 결과가 음수가 나오게 될 수 있음.
이런 경우를 방지하기 위해 MOD를 더함.
*/