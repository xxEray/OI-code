#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL HSH = 1361;
const LL MOD = 1000040017;
const int INF = 0x3f3f3f3f;

int n, m, Q;
int a[N];
struct Node { int l, r; } b[N];
char tmp[N];
std::deque<char> s;

std::vector<int> vct[N], vct2[N];
struct Query { int l, r, k, id; } q[N];

LL power[N], hsh[N];
LL hash(int l, int r) { return (hsh[r] - hsh[l - 1] * power[r - l + 1] % MOD + MOD) % MOD; }

struct SegmentTree {
	int t[N << 2];
	int mx;
	void build() {
		for(mx = 1; mx <= m; mx <<= 1);
		for(int i = 1; i <= (mx << 1); i++) t[i] = INF;
	}
	void modify(int x, int v) {
		x += mx, t[x] = v;
		for(x >>= 1; x; x >>= 1) t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	int query(int l, int r) {
		assert(l <= r);
		int ret = INF;
		l--, r++;
		for(l += mx, r += mx; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::min(ret, t[l ^ 1]);
			if(r & 1) ret = std::min(ret, t[r ^ 1]);
		}
		return ret;
	}
} seg;

int out[N];

int main() {
	scanf("%d%s%d", &n, tmp + 1, &m);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		if(isupper(tmp[i])) s.emplace_back(tolower(tmp[i]));
		else s.emplace_front(tmp[i]);
	s.emplace_front(0);
	b[n].l = 1, b[n].r = n;
	for(int i = n - 1; i >= 1; i--) {
		b[i] = b[i + 1];
		if(isupper(tmp[i + 1])) b[i].r--;
		else b[i].l++;
	}
	power[0] = 1;
	for(int i = 1; i <= n; i++) hsh[i] = (hsh[i - 1] * HSH + s[i]) % MOD, power[i] = power[i - 1] * HSH % MOD;
	for(int i = 1; i <= m; i++) {
		int l = 1, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(mid <= a[i] || hash(b[mid].l, b[mid].r - a[i]) == hash(b[mid].l + a[i], b[mid].r)) l = mid + 1;
			else r = mid;
		}
		l--;
		if(l >= a[i]){
			vct[l].emplace_back(i);
			vct2[a[i] - 1].emplace_back(i);
			// printf("[%d] %d, [%d..%d]\n", i, a[i], a[i], l);
		}
	}
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) scanf("%d%d%d", &q[i].k, &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](const Query &x, const Query &y) { return x.k > y.k; });
	seg.build();
	for(int i = n, j = 1; i >= 1; i--) {
		for(int x : vct[i]) seg.modify(x, a[x]);
		for(int x : vct2[i]) seg.modify(x, INF);
		while(j <= Q && q[j].k == i) {
			out[q[j].id] = seg.query(q[j].l, q[j].r);
			j++;
		}
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i] == INF ? -1 : out[i]);
	return 0;
} /*
7
AABAAba
9
4 3 2 1 7 5 3 6 1
6
1 4 4
2 1 4
2 1 3
3 3 5
5 4 7
7 8 9
*/