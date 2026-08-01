#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int u, int v) { (u = find(u)) != (v = find(v)) ? fa[u] = v : 0; }

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) fa[i] = i;
	int cnt = 0, w = 0;
	for(int i = n; i >= 1 && cnt < n - 1; i--)
		for(int j = i + i; j <= n && cnt < n - 1; j += i)
			if(find(i) != find(j))
				merge(i, j), cnt++, w += gcd(i, j);
	printf("%d %d\n", w, n - 1);
	return 0;
}