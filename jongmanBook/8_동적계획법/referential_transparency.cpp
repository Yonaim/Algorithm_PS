// 참조적 투명성(referential transparency)

/*
한 문제를 푸는데 있어서 재귀적으로 타고 들어가 풀게되는 부분 문제들이 여러개 있을 것이다.
그리고 각 부분 문제들에게는 그를 정의하는 맥락 정보들이 있다.
(코드로 따지면 완전 탐색을 위한 재귀 호출 함수의 인자들이라고 할 수 있다)

부분 문제의 해답이 해당 맥락 정보에 의해서만 결정되는 경우, 즉 외부 요인(전역 변수 등)에 의해 그 해답이 바뀔 일이 없는 경우,
해당 부분 문제를 중복해서 풀어야 큰 문제를 풀 수 있는 상황에서 그 부분 문제의 해답을 재사용하지 않을 이유가 없다.

이렇게 같은 input을 넣었을 때 늘 output이 같은지의 여부를 유식한 말로 참조적 투명성(referential transparency)라고 한다.
부분 문제 풀이 해답의 참조적 투명성이 보장되는 경우에 우리는 부분 문제의 해답을 재사용할 수 있다.

참조적 투명 함수의 경우에만 메모이제이션을 적용할 수 있으니,
완전탐색 문제에서 dp로 풀 수 있을지 여부를 알아내려면 우선 '부분 문제들이 참조적 투명성을 가지는지'
(즉, 이전 맥락과 상관없이 오직 해당 부분 문제만 보아 해답을 낼 수 있는지)를 체크하면 될 것이다.

*/