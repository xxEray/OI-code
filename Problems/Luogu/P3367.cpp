#include <bits/stdc++.h>

const int N = 1e4 + 5;

int a[N];
int n, m;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) fa[i] = i;
	while(m--) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1) x = find(x), y = find(y), fa[x] = y;
		else putchar(find(x) == find(y) ? 'Y' : 'N'), putchar('\n');
	}
	return 0;
}