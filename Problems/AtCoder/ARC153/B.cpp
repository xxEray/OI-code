#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 5e5 + 5;

int n, m, Q;
std::vector<char> a[N];

int r, c;
int tr[N], tc[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) a[i].resize(m + 2);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) { char str[2]; scanf("%1s", str); a[i][j] = str[0]; }
	r = c = 1;
	scanf("%d", &Q);
	for(int _ = 1; _ <= Q; _++) {
		int x, y;
		scanf("%d%d", &x, &y);
		r = (r <= x ? x + 1 - r : x + n + 1 - r);
		c = (c <= y ? y + 1 - c : y + m + 1 - c);
	}
	for(int i = r, j = 1; j <= n; i += (Q & 1) ? -1 : 1, j++) {
		if(i == 0) i = n;
		if(i == n + 1) i = 1;
		tr[i] = j;
	}
	for(int i = c, j = 1; j <= m; i += (Q & 1) ? -1 : 1, j++) {
		if(i == 0) i = m;
		if(i == m + 1) i = 1;
		tc[i] = j;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) putchar(a[tr[i]][tc[j]]);
		puts("");
	}
	return 0;
}