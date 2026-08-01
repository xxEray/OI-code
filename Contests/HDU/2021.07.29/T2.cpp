#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD1 = 1e9 + 7;
const LL MOD2 = 1e9 + 9;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], edgek;
void add_edge(int u, int v) { edge[edgek] = (Edge){v, head[u]}, head[u] = edgek++; }

int a[N];
int n;
LL ans1, ans2;

LL qpow(LL a, LL b, LL mod) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) { ret = ret * a % mod; } a = a * a % mod; } return ret; }

LL tot;
int cnt[N];
void dfs(int u, int fa) {
	tot += !cnt[a[u]]++;
	ans1 = (ans1 + tot * qpow(19560929, u - 1, MOD1) % MOD1) % MOD1;
	ans2 = (ans2 + tot * qpow(19560929, u - 1, MOD2) % MOD2) % MOD2;
	for(int i = head[u]; i; i = edge[i].nxt) {
		if(edge[i].to != fa)
			dfs(edge[i].to, u);
	}
	tot -= !--cnt[a[u]];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(head, 0, sizeof(head));
		edgek = 1;
		scanf("%d", &n);
		for(int i = 2; i <= n; i++) { int x; scanf("%d", &x); add_edge(i, x), add_edge(x, i); }
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) {
			ans1 = ans2 = 0;
			for(int j = 1; j <= n; j++) cnt[j] = 0;
			tot = 0;
			dfs(i, 0);
			printf("%lld %lld\n", ans1, ans2);
		}
	}
	return 0;
}