#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, K, Q;
int a[5][N];

std::vector<LL> f[N << 2][5][5];
std::vector<LL> merge(std::vector<LL> x, std::vector<LL> y) {
	assert(!x.empty() && !y.empty());
	// int len = (int)x.size() - 1 + (int)y.size() - 1;
	std::vector<LL> z;
	z.emplace_back(x.front() + y.front());
	for(int i = 0; i < (int)x.size() - 1; i++) x[i] = x[i + 1] - x[i];
	for(int i = 0; i < (int)y.size() - 1; i++) y[i] = y[i + 1] - y[i];
	x.pop_back(), y.pop_back();
	for(int i = 0, j = 0; i < (int)x.size() || j < (int)y.size(); ) {
		if(j >= (int)y.size() || (i < (int)x.size() && x[i] > y[j])) z.emplace_back(x[i++]);
		else z.emplace_back(y[j++]);
	}
	for(int i = 1; i < (int)z.size(); i++) z[i] += z[i - 1];
	// assert((int)z.size() - 1 == len);
	return z;
}
inline int mod(const int &x) { return x < 0 ? x + K : x; }
void solve(int x, int l, int r) {
	// printf("solve %d %d %d\n", x, l, r);
	if(l == r) {
		for(int i = 0; i < K; i++) f[x][i][i].emplace_back(a[i][l]);
		return;
	}
	int mid = (l + r) >> 1;
	solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) {
		f[x][i][j].resize((r - l + 1) / K + 2, -1);
		for(int k1 = 0; k1 < K; k1++) for(int k2 : {k1, k1 + 1 == K ? 0 : k1 + 1}) if(!f[x << 1][i][k1].empty() && !f[x << 1 | 1][k2][j].empty()) {
			auto tmp = merge(f[x << 1][i][k1], f[x << 1 | 1][k2][j]);
			int v = (mod(k1 - i) + mod(j - k2) + mod(k2 - k1) >= K);
			// assert(v <= 1);
			// printf("x = %d, i = %d, j = %d, k1 = %d, k2 = %d, tmp.size() = %d, v = %d\n", x, i, j, k1, k2, (int)tmp.size(), v);
			for(int k = 0; k < (int)tmp.size(); k++) f[x][i][j].at(k + v) = std::max(f[x][i][j].at(k + v), tmp[k]);
		}
		while(!f[x][i][j].empty() && f[x][i][j].back() == -1) f[x][i][j].pop_back();
		// printf("f[%d][%d][%d] = ", x, i, j); for(auto v : f[x][i][j]) printf("%lld ", v); puts("");
	}
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) {
		std::vector<LL>().swap(f[x << 1][i][j]);
		std::vector<LL>().swap(f[x << 1 | 1][i][j]);

		// f[x << 1][i][j].clear(), f[x << 1][i][j].shrink_to_fit();
		// f[x << 1 | 1][i][j].clear(), f[x << 1 | 1][i][j].shrink_to_fit();
	}
}

int main() {
#ifndef DEBUG
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &K, &Q);
	for(int i = 0; i < K; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	solve(1, 1, n);
	while(Q--) {
		int x;
		scanf("%d", &x);
		x--;
		printf("%lld\n", f[1][0][x % K].at(x / K));
	}
	return 0;
} /*
6 2 1
2 4 3 1 1 2 
1 5 1 3 1 1 
4
*/