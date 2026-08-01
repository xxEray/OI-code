#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

const int N = 300005, T = 512, V = 65536;
struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
Edge e[N << 1];
int n, hd[N], pnt, w[N], siz[N], son[N];
vector <pair <long long, int> > nd[N];
long long dp[N];

struct xorPlusMax {
	long long tri[17][V], taga;
	int tagb;
	vector <pair <long long, int> > smx;
	inline void Clear() {
		smx.clear();
		memset(tri, 0x3f, sizeof(tri));
		taga = tagb = 0;
	}
	xorPlusMax() {
		Clear();
	}
	inline void Build(int p, int pl, int pr, int dep) {
		if (pl == pr) return;
		int mid = pl + pr >> 1;
		Build(p << 1, pl, mid, dep - 1); Build(p << 1 | 1, mid + 1, pr, dep - 1);
		for (int i = pl;i <= mid;i++) tri[dep][i] = min(tri[dep - 1][i], tri[dep - 1][i - pl + mid + 1] + (1 << dep - 1));
		for (int i = mid + 1;i <= pr;i++) tri[dep][i] = min(tri[dep - 1][i], tri[dep - 1][i - mid - 1 + pl] + (1 << dep - 1));
	}
	inline void Modify(int p, int pl, int pr, long long a, int b, int dep) {
		if (pl == pr) {
			tri[dep][pl] = min(tri[dep][pl], a);
			return;
		}
		int mid = pl + pr >> 1;
		if (b <= mid) Modify(p << 1, pl, mid, a, b, dep - 1);
		else Modify(p << 1 | 1, mid + 1, pr, a, b, dep - 1);
	}
	inline void Ins(long long a, int b) {
		a -= taga; b ^= tagb;
		smx.push_back(make_pair(a, b));
		Modify(1, 0, V - 1, a, b, 16);
		if (smx.size() > T) {
			smx.clear();
			Build(1, 0, V - 1, 16);
		}
	}
	inline long long Query(int b) {
		b ^= tagb;
		long long ans = tri[16][b];
		for (pair <long long, int> x : smx) ans = min(ans, x.first + (x.second ^ b));
		return ans + taga;
	}
};
xorPlusMax xpm;

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) w[i] = qread();
	for (int i = 1;i < n;i++) {
		int u = qread(), v = qread();
		AddEdge(u, v); AddEdge(v, u);
	}
}

inline void Dfs1(int u, int fa) {
	siz[u] = 1;
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			Dfs1(e[i].to, u);
			siz[u] += siz[e[i].to];
			if (siz[e[i].to] > siz[son[u]]) son[u] = e[i].to;
		}
	}
}

inline void Brute(int u, int fa) {
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) Brute(e[i].to, u);
	}
	long long sum = 0;
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) sum += dp[e[i].to];
	}
	dp[u] = sum + w[u];
	nd[u].push_back(make_pair(sum, w[u]));
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			for (pair <long long, int> x : nd[u]) {
				for (pair <long long, int> y : nd[e[i].to]) dp[u] = min(dp[u], x.first + y.first + (x.second ^ y.second) - dp[e[i].to]);
			}
			for (pair <long long, int> x : nd[e[i].to]) nd[u].push_back(make_pair(x.first + sum - dp[e[i].to], x.second ^ w[u]));
			nd[e[i].to].clear();
		}
	}
}

inline void getVect(int u, int fa, int rt, long long a, int b) {
	long long sum = 0;
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) sum += dp[e[i].to];
	}
	nd[rt].push_back(make_pair(a + sum, b));
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			getVect(e[i].to, u, rt, a + sum - dp[e[i].to], b ^ w[e[i].to]);
		}
	}
}

inline void Dfs2(int u, int fa) {
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa && e[i].to != son[u]) {
			if (siz[e[i].to] < T) Brute(e[i].to, u);
			else {
				Dfs2(e[i].to, u);
				getVect(e[i].to, u, e[i].to, 0, w[e[i].to]);
			}
		}
	}
	if (son[u]) Dfs2(son[u], u);
	else {
		xpm.Clear();
		dp[u] = w[u];
		xpm.Ins(0, w[u]);
		return;
	}
	long long sum = 0;
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			dp[u] += dp[e[i].to];
			sum += dp[e[i].to];
		}
	}
	dp[u] += w[u];
	long long tmp = xpm.Query(w[u]) + sum - dp[son[u]];
	xpm.taga += sum - dp[son[u]];
	xpm.tagb ^= w[u];
	xpm.Ins(sum, w[u]);
	dp[u] = min(dp[u], tmp);
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa && e[i].to != son[u]) {
			if (siz[e[i].to] < T) {
				for (pair <long long, int> x : nd[e[i].to]) dp[u] = min(dp[u], x.first + xpm.Query(x.second) - dp[e[i].to]);
				for (pair <long long, int> x : nd[e[i].to]) xpm.Ins(x.first + sum - dp[e[i].to], x.second ^ w[u]);
				nd[e[i].to].clear();
			} else {
				xpm.Build(1, 0, V - 1, 16); xpm.smx.clear();
				for (pair <long long, int> x : nd[e[i].to]) dp[u] = min(dp[u], x.first + xpm.Query(x.second) - dp[e[i].to]);
				for (pair <long long, int> x : nd[e[i].to]) xpm.Modify(1, 0, V - 1, x.first + sum - dp[e[i].to] - xpm.taga, x.second ^ w[u] ^ xpm.tagb, 16);
				nd[e[i].to].clear();
				xpm.Build(1, 0, V - 1, 16);
			}
		}
	}
}

int main() {
    // freopen("arcanaeden.in", "r", stdin);
    // freopen("arcanaeden.out", "w", stdout);
	memset(hd, -1, sizeof(hd));
	Read();
	Dfs1(1, -1);
	if (siz[1] < T) Brute(1, -1);
	else Dfs2(1, -1);
	cout << dp[1] << endl;
	return 0;
}
