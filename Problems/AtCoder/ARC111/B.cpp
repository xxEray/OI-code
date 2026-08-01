#include <bits/stdc++.h>

const int N = 400000 + 5;

int m;

int szv[N], sze[N], fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y, szv[y] += szv[x], sze[y] += sze[x] : 0; }

int main() {
	for(int i = 1; i <= 400000; i++) fa[i] = i, szv[i] = 1;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); merge(u, v), sze[find(u)]++; }
	int ans = 0;
	for(int i = 1; i <= 400000; i++) if(find(i) == i) ans += std::min(szv[find(i)], sze[find(i)]);
	printf("%d\n", ans);
	return 0;
}