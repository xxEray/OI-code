#include <bits/stdc++.h>

const int N = 5000 + 5;

int n, m;
int a[N], b[N], c[N];

int tmp[N];
void discrete() {
	m = 0;
	for(int i = 1; i <= n; i++) tmp[++m] = a[i], tmp[++m] = b[i];
	std::sort(tmp + 1, tmp + m + 1);
	m = std::unique(tmp + 1, tmp + m + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(tmp + 1, tmp + m + 1, a[i]) - tmp;
		b[i] = std::lower_bound(tmp + 1, tmp + m + 1, b[i]) - tmp;
	}
}

int fa[N << 2];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	scanf("%*d%d", &n);
	for(int i = 1; i <= n; i++) { char s[5]; scanf("%d%d%s", &a[i], &b[i], s); a[i]--; c[i] = (s[0] == 'e' ? 0 : 1); }
	discrete();
	for(int i = 0; i <= 2 * m; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) {
		if(c[i] == 0) merge(a[i], b[i]), merge(a[i] + m, b[i] + m);
		else merge(a[i], b[i] + m), merge(a[i] + m, b[i]);
		if(find(a[i]) == find(a[i] + m) || find(b[i]) == find(b[i] + m)) { printf("%d\n", i - 1); return 0; }
	}
	printf("%d\n", n);
	return 0;
}