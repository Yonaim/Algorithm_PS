#include <stdio.h>
#include <limits.h>

int n;
int	lowest_cost;
int	cost[11][11];
int visited[11] = {0, };

void recursive_travel(int cur_city, int visit_cnt, int total_cost)
{
	if (visit_cnt == n)
	{
		if (cost[cur_city][1] == 0)
			return ;
		total_cost += cost[cur_city][1];
		if (total_cost < lowest_cost)
			lowest_cost = total_cost;
		return ;
	}
	for (int i = 1; i <= n; i++)
	{
		if (visited[i] == 0 && cost[cur_city][i] != 0)
		{
			visited[cur_city] = 1;
			recursive_travel(i, visit_cnt + 1, total_cost + cost[cur_city][i]);
			visited[cur_city] = 0;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			scanf("%d", &cost[i][j]);
	}
	lowest_cost = INT_MAX;
	recursive_travel(1, 1, 0);
	printf("%d\n", lowest_cost);
}