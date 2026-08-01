#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 1e9 + 7;

int n, m;
std::vector<int> to[2 * N];

int dis[2 * N];
int cnt[2 * N][2 * N];

std::vector<std::pair<int, int>> vct[4 * N];

void bfs() {
	std::queue<int> q;
	for(int i = 1; i <= 2 * n; i++) dis[i] = 0;
	dis[1] = 1, q.push(1);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(!dis[v]) dis[v] = dis[u] + 1, q.push(v);
	}
}

LL fac[2 * N], invfac[2 * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL power2[2 * N];
LL g[N][N][N], h[N][N];
void preprocess() {
	power2[0] = 1;
	for(int i = 1; i <= 200; i++) power2[i] = power2[i - 1] * 2 % MOD;
	// for(int i = 0; i <= 100; i++) for(int j = 0; j <= 100; j++) for(int i_ = 0; i_ <= i; i_++) {
	// 	LL tmp = (power2[i - i_ + j] - 1 + MOD) % MOD, tmp2 = ((i_ & 1) ? MOD - 1 : 1) * C(i, i_) % MOD;
	// 	for(int k = 0; k <= 100; k++) (g[i][j][k] += tmp2) %= MOD, (tmp2 *= tmp) %= MOD;
	// }
	for(int i=0;i<=100;++i)
		for(int j=0;j<=100;++j)
			g[0][i][j]=qpow((power2[i]-1+MOD)%MOD,j);
	for(int k=1;k<=100;++k)
		for(int i=1;i<=100;++i)
			for(int j=0;j<=100-i;++j)
				g[i][j][k]=(g[i-1][j+1][k]-g[i-1][j][k]+MOD)%MOD;
	for(int i = 0; i <= 100; i++) for(int j_ = 0; j_ <= 100; j_++) {
		LL tmp = qpow(2, (LL)(i - j_) * (i - j_ + 1) / 2);
		for(int j = j_; j <= 100; j++) (h[i][j] += ((j_ & 1) ? MOD - 1 : 1) * C(j, j_) % MOD * tmp) %= MOD;
	}
}

LL f1[2 * N][2 * N][N], f2[2 * N][2 * N][N];

int main() {
	get_factorial(200);
	preprocess();
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= 4 * n; i++) vct[i].clear();
		for(int i = 1; i <= 2 * n; i++) to[i].clear();
		for(int i = 0; i <= 2 * n + 1; i++) for(int j = 0; j <= 2 * n + 1; j++) cnt[i][j] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			to[u].push_back(v + n), to[u + n].push_back(v);
			to[v].push_back(u + n), to[v + n].push_back(u);
		}
		bfs();
		// for(int i = 1; i <= n; i++) printf("%d: %d %d\n", i, dis[i], dis[i + n]);
		if(dis[n + 1] == 0) {
			LL ans = 1;
			for(int i = 1; i <= n; i++) vct[std::max(dis[i], dis[i + n])].push_back({i, 0});
			for(int i = 2; i <= n; i++) (ans *= qpow((power2[vct[i - 1].size()] - 1 + MOD) % MOD, vct[i].size())) %= MOD;
			printf("%lld\n", ans);
			continue;
		}
		for(int i = 1; i <= n; i++) {
			int x = dis[i], y = dis[i + n];
			if(x > y) std::swap(x, y);
			if(!cnt[x][y]) vct[x + y].emplace_back(x, y);
			cnt[x][y]++;
		}
		for(int i = 1; i <= 4 * n; i++) std::sort(vct[i].begin(), vct[i].end());
		for(int t = 1; t <= 4 * n; t += 2) for(auto [x, y] : vct[t]) for(int v = 0; v <= cnt[x][y]; v++) f1[x][y][v] = f2[x][y][v] = 0;
		for(int t = 1; t <= 4 * n; t += 2) {
			for(auto [x, y] : vct[t]) {
				if(!cnt[x - 1][y + 1]) {
					if(x == 1) f2[x][y][cnt[x][y]] = 1;
					else f2[x][y][0] = qpow((power2[cnt[x - 1][y - 1]] - 1 + MOD) % MOD, cnt[x][y]) % MOD;
					continue;
				}
				for(int v = 0; v <= cnt[x][y]; v++) for(int v_ = 0; v_ <= cnt[x - 1][y + 1]; v_++)
					(f1[x][y][v] += C(cnt[x][y], v) * f2[x - 1][y + 1][v_] % MOD * g[v_][cnt[x - 1][y + 1] - v_][v]) %= MOD;
				for(int v = 0; v <= cnt[x][y]; v++) for(int v_ = cnt[x][y]; v_ >= v; v_--)
					(f2[x][y][v] += C(v_, v) * qpow((power2[cnt[x - 1][y - 1]] - 1 + MOD) % MOD, cnt[x][y] - v) % MOD * f1[x][y][v_]) %= MOD;
			}
			// for(auto [x, y] : vct[t]) for(int v = 0; v <= cnt[x][y]; v++) printf("(%d, %d) v=%d  f1=%lld, f2=%lld\n", x, y, v, f1[x][y][v], f2[x][y][v]);
		}
		LL ans = 1;
		for(int t = 1; t <= 4 * n; t += 2) if(!vct[t].empty()) {
			auto [x, y] = vct[t].back();
			if(y != x + 1) (ans *= f2[x][y][0]) %= MOD;
			else {
				LL ret = 0;
				for(int v = 0; v <= cnt[x][y]; v++) (ret += f2[x][y][v] * h[cnt[x][y]][v]) %= MOD;
				(ans *= ret) %= MOD;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
5 7
1 2
1 3
1 5
2 4
3 3
3 4
4 5
*/