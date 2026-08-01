#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n, m;
LL a[2][N], b[2][N], c[2][N];
int d[2][N];

std::vector<int> vct[N];
std::set<int> st;

LL f[N];

void add(int ind, LL val) {
	// printf("add %d %lld\n", ind, val);
	if(ind < 0 || ind > m || val == 0) return;
	if(val > 0) {
		f[ind] += val, st.insert(ind);
	} else {
		val = -val;
		while(val) {
			LL sub = std::min(f[ind], val);
			f[ind] -= sub, val -= sub;
			if(f[ind]) break;
			st.erase(ind);
			if(st.lower_bound(ind) == st.end()) break;
			ind = *st.lower_bound(ind);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld%lld", &a[0][i], &b[0][i], &c[0][i]);
	for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &a[1][i], &b[1][i], &c[1][i]);
	for(int i = 1; i <= n; i++) a[0][i] += a[0][i - 1];
	for(int i = 1; i <= m; i++) a[1][i] += a[1][i - 1];
	for(int i = 1; i <= n; i++) {
		int l = 0, r = m + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(a[0][i] + a[1][mid] <= b[0][i]) l = mid + 1;
			else r = mid;
		}
		d[0][i] = l - 1;
	}
	for(int j = 1; j <= m; j++) {
		int l = 0, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(a[0][mid] + a[1][j] <= b[1][j]) l = mid + 1;
			else r = mid;
		}
		d[1][j] = l - 1;
	}
	// printf("d[0]: "); for(int i = 1; i <= n; i++) printf("%d ", d[0][i]); puts("");
	// printf("c[0]: "); for(int i = 1; i <= n; i++) printf("%lld ", c[0][i]); puts("");
	// printf("d[1]: "); for(int i = 1; i <= m; i++) printf("%d ", d[1][i]); puts("");
	// printf("c[1]: "); for(int i = 1; i <= m; i++) printf("%lld ", c[1][i]); puts("");
	for(int j = 1; j <= m; j++) vct[d[1][j] + 1].push_back(j);
	// for(int j = 1; j <= m; j++) if(d[1][j] >= 0) add(j, -c[1][j]);
	for(int i = 1; i <= n; i++) {
		for(int j : vct[i]) if(c[1][j] >= 0) add(j, c[1][j]);
		if(d[0][i] >= 0) {
			f[0] += c[0][i];
			add(d[0][i] + 1, -c[0][i]);
		}
		for(int j : vct[i]) if(c[1][j] < 0) add(j, c[1][j]);
		// printf("%d: ", i); for(int j = 0; j <= m; j++) printf("%lld ", f[j]); puts("");
	}
	LL ans = 0;
	for(int i = 0; i <= m; i++) ans += f[i] + (d[1][i] == n) * c[1][i];
	printf("%lld\n", ans);
	return 0;
} /*
7 5
3 73 2
10 73 7
16 73 19
12 73 4
15 73 15
20 73 14
15 73 8
16 73 16
17 73 10
20 73 1
14 73 16
18 73 10
*/