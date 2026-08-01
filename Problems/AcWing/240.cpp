#include <bits/stdc++.h>

const int N = 50000 + 5;

int n, Q;

int fa[N], w[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i, w[i] = 0; }
int find(int x) {
	if(x == fa[x]) return x;
	int t = find(fa[x]);
	w[x] = (w[fa[x]] + w[x]) % 3;
	fa[x] = t;
	return t;
}

int main() {
	scanf("%d%d", &n, &Q);
	init();
	int ans = 0;
	while(Q--) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		t--;
		if(x > n || y > n) { ans++; continue; }
		int fx = find(x), fy = find(y);
		if(fx == fy) {
			if((w[y] - w[x] + 3) % 3 != t) ans++;
		} else {
			fa[fy] = fx, w[fy] = (t + w[x] - w[y] + 3) % 3;
		}
	}
	printf("%d\n", ans);
	return 0;
}