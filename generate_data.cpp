#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

const int maxn = 105;
const int maxm = 10005;

struct node {
	int x, y;
} res[maxm];

int n = 20;
int m = 100;
int p[maxn], cost[maxn], id[maxn];
bool fa[maxn], v[maxm], go[maxn][maxn];

bool cmp(int i, int j) {
	return i > j;
}

int main() {
	freopen("input.txt", "w", stdout);
	
	int x, y;
	
	srand((unsigned)time(NULL));
	
	printf("%d\n", n);
	
	memset(v, false, sizeof(v));
	for (int i = 1; i <= n; i++) {
		cost[i] = rand() % 1000 + 1;
		while (v[cost[i]]) cost[i] = rand() % 1000 + 1;
		v[cost[i]] = true;
	}
	sort(cost + 1, cost + n + 1, cmp);
	
	memset(v, false, sizeof(v));
	for (int i = 1; i <= n; i++) {
		x = rand() % n + 1;
		while (v[x]) x = rand() % n + 1;
		p[i] = x;
		v[x] = true;
		res[i].x = x;
		res[i].y = cost[i];
	}
	
	memset(v, false, sizeof(v));
	for (int i = 1; i <= n; i++) {
		x = rand() % n + 1;
		while (v[x]) x = rand() % n + 1;
		v[x] = true;
		id[i] = x;
	}
	
	for (int i = 1; i <= n; i++)
		printf("%d %d\n", res[id[i]].x, res[id[i]].y);
	
	memset(fa, true, sizeof(fa));
	memset(go, false, sizeof(go));
	for (int i = 1; i <= m; i++) {
		y = rand() % n + 1;
		while (y == 1) y = rand() % n + 1;
		x = rand() % (y - 1) + 1;
		while (go[x][y]) {
			y = rand() % n + 1;
			while (y == 1) y = rand() % n + 1;
			x = rand() % (y - 1) + 1;
		}
		go[x][y] = true;
		res[i].x = p[x];
		res[i].y = p[y];
		fa[y] = false;
	}
	
	for (int i = 1; i <= n; i++)
		if (fa[i]) {
			for (int j = i + 1; j <= n; j++)
				if (fa[j]) {
					m++;
					res[m].x = p[i];
					res[m].y = p[j];
				}
			break;
		}
	
	printf("%d\n", m);
	for (int i = 1; i <= m; i++)
		printf("%d %d\n", res[i].x, res[i].y);
	return 0;
}

