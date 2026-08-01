#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

typedef long long LL;

const int N = 5e5 + 5;

int n, K;
char s[N];

namespace BF {
	const int N = 300 + 5;

	int w[N][N];
	int f[N][N];

	void main() {
		srand(time(0));
		puts(s + 1);
		for(int i = 1; i <= n; i++) {
			int sum = 0;
			for(int j = i; j <= n; j++) {
				sum += (s[j] == '(' ? 1 : -1);
				if(sum < 0) break;
				w[i][j] = (sum == 0);
			}
		}
		for(int len = 1; len <= n; len++)
			for(int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				w[i][j] += w[i + 1][j] + w[i][j - 1] - w[i + 1][j - 1];
			}
		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= i; j++)
				for(int k = 0; k < i; k++)
					f[i][j] = std::min(f[i][j], f[k][j - 1] + w[k + 1][i]);
		printf("%d\n", f[n][K]);
	}
}

int ld[N], lmost[N], rmost[N], ts[N];
int cts;
int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }

struct Node {
	LL weight;
	int u, v, tsu, tsv;
	int random_weight;
};
bool operator<(const Node &x, const Node &y) {
	if(x.weight != y.weight) return x.weight > y.weight;
	else return x.random_weight < y.random_weight;
}
std::priority_queue<Node> pq;

int prvb[N], nxtb[N];
int prv[N], nxt[N];
int w[N];

LL getw(int u, int v) {
	assert(find(u) != find(v));
	u = find(u), v = find(v);
	if(s[u] == '|' || s[v] == '|') return 0;
	LL sum = 0;
	for(int l = rmost[u], r = lmost[v]; l && r && s[l] == '(' && s[r] == ')'; l = prv[l], r = nxt[r])
		sum += (LL)(w[l] + 1) * (w[r] + 1);
	// printf("getw(%d, %d) = %lld\n", u, v, sum);
	return sum;
}
void mergew(int u, int v) {
	assert(find(u) != find(v));
	u = find(u), v = find(v);
	if(s[u] == '|' || s[v] == '|') {
		if(s[u] == '|') {
			ld[u] = v;
			if(v && s[lmost[v]] == '(') w[lmost[v]]++;
		} else {
			ld[v] = u;
			if(u && s[rmost[u]] == ')') w[rmost[u]]++;
		}
		return;
	}
	int l = rmost[u], r = lmost[v];
	int lastwl = -1, lastwr = -1;
	while(l && r && s[l] == '(' && s[r] == ')') lastwl = w[l], lastwr = w[r], l = prv[l], r = nxt[r];
	if(!l && !r) {
		ld[v] = u;
		s[u] = '|';
		w[u] = 0, prv[u] = nxt[u] = 0;
		lmost[u] = rmost[u] = u;
		return;
	}
	if(l) nxt[l] = r, w[l] += (s[l] == ')' ? lastwr + 1 : 0);
	if(r) prv[r] = l, w[r] += (s[r] == '(' ? lastwl + 1 : 0);
	int t;
	if(l) t = ld[v] = u;
	else t = ld[u] = v;
	lmost[t] = (l ? lmost[u] : r), rmost[t] = (r ? rmost[v] : l);
}

#ifdef _WIN32
int myrand() { return rand() << 15 | rand(); }
#else
int myrand() { return rand(); }
#endif

int main() {
#ifndef DEBUG
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
#endif
	srand(time(0));
	scanf("%d%d%s", &n, &K, s + 1);
	if(n <= 300) { BF::main(); return 0; }
	for(int i = 1; i <= n; i++) lmost[i] = rmost[i] = ld[i] = i, ts[i] = ++cts;
	for(int i = 1; i <= n; i++) prvb[i] = i - 1, nxtb[i] = (i == n ? 0 : i + 1);
	for(int i = 1; i <= n - 1; i++) pq.push({(s[i] == '(' && s[i + 1] == ')'), i, i + 1, ts[i], ts[i + 1], myrand()});
	int cnt = n;
	LL ans = 0;
	while(cnt > K) {
		assert(!pq.empty());
		auto nd = pq.top();
		pq.pop();
		if(nd.tsu != ts[find(nd.u)] || nd.tsv != ts[find(nd.v)]) continue;
		// printf("w: "); for(int i = 1; i <= n; i++) printf("%d ", w[i]); puts("");
		// printf("find: "); for(int i = 1; i <= n; i++) printf("%d ", find(i)); puts("");
		// printf("ts:   "); for(int i = 1; i <= n; i++) printf("%d ", ts[find(i)]); puts("");
		// printf("prvb: "); for(int i = 1; i <= n; i++) printf("%d ", prvb[find(i)]); puts("");
		// printf("nxtb: "); for(int i = 1; i <= n; i++) printf("%d ", nxtb[find(i)]); puts("");
		// printf("merge %d %d (%lld)\n", nd.u, nd.v, nd.weight);
		assert(find(nxtb[find(nd.u)]) == find(nd.v) && find(prvb[find(nd.v)]) == find(nd.u));
		cnt--;
		ans += nd.weight;
		int pb = prvb[find(nd.u)], nb = nxtb[find(nd.v)];
		mergew(nd.u, nd.v);
		prvb[find(nd.u)] = pb, nxtb[find(nd.u)] = nb;
		ts[find(nd.u)] = ++cts;
		auto push_pq = [&](int t) {
			if(!t) return;
			int p = t, q = nd.u;
			if(p > q) std::swap(p, q);
			pq.push({getw(p, q), p, q, ts[find(p)], ts[find(q)], myrand()});
		};
		push_pq(prvb[find(nd.u)]), push_pq(nxtb[find(nd.u)]);
	}
	printf("%lld\n", ans);
	return 0;
} /*
24 3
()()((()))()()()(()((())
*/