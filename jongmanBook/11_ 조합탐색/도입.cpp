// 도입

/*
조합 탐색(combinatorial search)는 
'유한한 크기의 탐색 공간을 뒤지면서 답을 찾아내는 알고리즘'을 의미한다. 
물론 완전 탐색도 조합 탐색에 포함된다.

...가 조합 탐색의 정의이긴한데, 내용을 읽어보니 이 장에서는
이런 조합 탐색(주로 완전탐색)을 최적화하여 답을 찾아내는 방법을 안내하고 있다.
*/

/*
여행하는 외판원 문제를 예시로 드는데, 내가 책의 초반부에서 이 문제를 풀었을 때
'이렇게 하면 더 빠르게 답을 찾을 수 있지 않을까?'하는 생각으로
정확히 이 장에서 소개하는 가지치기(pruning) 기법을 사용하였기 때문에
'이것도 하나의 최적화 기법으로 인정이 되는구나'싶어서 굉장히 신기했다.
(물론 문제를 풀 당시에는 이게 가지치기 기법이라고 불리는지도 몰랐다.)
(그 당시에는 백트래킹(backtracking)이라고만 생각했는데,
백트래킹은 앞으로 더 깊숙히 들어가면 나올 답이 '불가능한 답'의 경우에 뒤로 가는 반면
가지치기는 '가능한 답이지만, 이미 찾은 답보다 덜 최적인 경우' 뒤로 간다는 차이가 있는 것 같다.
가지치기가 백트래킹의 범주에 들어간다고 생각할 수 있을 듯? 근데 뭐...이 둘을 구분하는게 중요한 건 아니니까.)
*/

/*
완전 탐색의 수행 시간은 부분 문제를 포함한 구해야하는 답들의 개수, 즉 탐색 공간(search space)의 크기에 비례한다.
그리고 완전 탐색의 탐색 공간은 문제의 규모에 기하급수적으로 증가한다.
그래서 문제의 규모가 조금이라도 커지면 완전 탐색을 사용하기는 사실 힘들다.
그렇기 때문에......탐색 공간에서 실제로 찾아야 하는 답의 개수를 조금이라도 줄이기 위한 여러 최적화 기법을 사용하게 된다.

문제마다 특성이 다르므로 최적화 기법은 꽤나 다양하게 존재하고 특별히 정답이 없다.
그래서 지금도 활발히 연구되고 있는 분야라고 한다.
*/