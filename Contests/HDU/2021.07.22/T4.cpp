#pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 1e5 + 5;

int a[N];
int n, m;

int blocksize;
struct Query { int l, r, a, b, id; } q[N];
bool operator<(const Query &a, const Query &b) { return ((a.l / blocksize) ^ (b.l / blocksize)) ? (a.l / blocksize) < (b.l / blocksize) : (((a.l / blocksize) & 1) ? a.r < b.r : a.r > b.r); }
int cnt[N], out[N];

namespace Trie {
	int s[3000005][2], sum[3000005];
	int triek = 1;
	void ins(int x) {
		int u = 1;
		for(int i = 18; i >= 0; i--) {
			int v = (x >> i) & 1;
			if(!s[u][v]) s[u][v] = ++triek;
			u = s[u][v], sum[u]++;
		}
	}
	void del(int x) {
		int u = 1;
		for(int i = 18; i >= 0; i--) {
			int v = (x >> i) & 1;
			u = s[u][v], sum[u]--;
		}
	}
	int calc(int a, int b) {
		int u = 1, ret = 0;
		for(int i = 18; u && i >= 0; i--) {
			int va = (a >> i) & 1, vb = (b >> i) & 1;
			if(vb == 0) u = s[u][va];
			else ret += sum[s[u][va]], u = s[u][!va];
		}
		return ret + sum[u];
	}
}

inline void add(int i) { if(!cnt[a[i]]++) Trie::ins(a[i]); }
inline void del(int i) { if(!--cnt[a[i]]) Trie::del(a[i]); }

int main() {
	scanf("%d", &n); blocksize = sqrt(n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d", &q[i].l, &q[i].r, &q[i].a, &q[i].b), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(l < q[i].l) del(l++);
		while(l > q[i].l) add(--l);
		while(r > q[i].r) del(r--);
		while(r < q[i].r) add(++r);
		out[q[i].id] = Trie::calc(q[i].a, q[i].b);
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
} /*
5
1 2 2 4 5
4
1 3 1 3
2 4 4 2
1 5 2 3
4 5 3 6

7
3 5 4 2 6 1 7
2
2 6 0 7
2 3 0 9
*/