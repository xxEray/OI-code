#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.5e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[N], b[N];
int vb[N], ib[N];
LL sum[N];

int tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = b[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) vb[i] = std::lower_bound(tmp + 1, tmp + c + 1, b[i]) - tmp, ib[vb[i]] = b[i];
}

int poss;
struct SegValue { int cnt; LL sum; };
SegValue calc(const SegValue &x, const SegValue &y) { return {x.cnt + y.cnt, x.sum + y.sum}; }
struct SegNode { SegValue t; int ls, rs; };
struct SegmentTree {
	SegNode t[N * 20];
	int tot;
	int copy(int x) { tot++; t[tot] = t[x]; return tot; }
	void modify(int qind, LL qv, int &x, int l = 1, int r = n) {
		x = copy(x);
		if(l == r) { t[x].t.cnt++, t[x].t.sum += qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, t[x].ls, l, mid);
		else modify(qind, qv, t[x].rs, mid + 1, r);
		t[x].t = calc(t[t[x].ls].t, t[t[x].rs].t);
	}
	LL query1(int qk, int x, int y, int l = 1, int r = n) const {
		// assert(t[y].t.cnt - t[x].t.cnt >= qk);
		if(l == r) return ib[l] * qk;
		int mid = (l + r) >> 1;
		if(t[t[y].rs].t.cnt - t[t[x].rs].t.cnt >= qk) return query1(qk, t[x].rs, t[y].rs, mid + 1, r);
		else return query1(qk - (t[t[y].rs].t.cnt - t[t[x].rs].t.cnt), t[x].ls, t[y].ls, l, mid) + (t[t[y].rs].t.sum - t[t[x].rs].t.sum);
	}
	LL query2(int qk, int x, int y, int l = 1, int r = n) const {
		// assert(t[y].t.cnt - t[x].t.cnt >= qk);
		if(l == r) return poss = ib[l], ib[l] * qk;
		int mid = (l + r) >> 1;
		if(t[t[y].rs].t.cnt - t[t[x].rs].t.cnt >= qk) return query2(qk, t[x].rs, t[y].rs, mid + 1, r);
		else return query2(qk - (t[t[y].rs].t.cnt - t[t[x].rs].t.cnt), t[x].ls, t[y].ls, l, mid) + (t[t[y].rs].t.sum - t[t[x].rs].t.sum);
	}
} seg;
int ver[N];

LL f[N];
int p[N];
void cdq(int l, int r, int cl, int cr) {
	if(l > r) return;
	int mid = (l + r) >> 1;
	LL val = -LLINF;
	for(int i = cl; i <= std::min(cr, mid - K + 1); i++) {
		// printf("query [%d, %d] = %lld\n", i, mid, seg.queryS(K, ver[i - 1], ver[mid]));
		LL val2 = sum[i - 1] + seg.query1(K, ver[i - 1], ver[mid]);
		if(val2 >= val) val = val2, p[mid] = i;
	}
	f[mid] = val - sum[mid];
	cdq(l, mid - 1, cl, p[mid]), cdq(mid + 1, r, p[mid], cr);
}

std::multiset<int> st;
std::vector<int> add[N], del[N];

int main() {
#ifndef DEBUG
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	discrete();
	for(int i = 1; i <= n; i++) ver[i] = ver[i - 1], seg.modify(vb[i], b[i], ver[i]);
	cdq(K, n, 1, n);
	LL ans = *std::max_element(f + K, f + n + 1);
	printf("%lld\n", ans);
	std::vector<int> vct;
	for(int i = K; i <= n; i++) if(f[i] == ans) vct.emplace_back(i);
	for(int o = 0; o < (int)vct.size(); o++) {
		int i = vct[o];
		for(int j = (o ? p[vct[o - 1]] : 1); j <= p[i]; j++)
			if(seg.query2(K, ver[j - 1], ver[i]) - sum[i] + sum[j - 1] == ans) {
				int mn = poss;
				add[j].emplace_back(mn), del[i + 1].emplace_back(mn);
			}
	}
	for(int i = 1; i <= n; i++) {
		for(int x : add[i]) st.emplace(x);
		for(int x : del[i]) st.erase(st.find(x));
		if(!st.empty() && b[i] >= *st.begin()) putchar('1');
		else putchar('0');
	}
	puts("");
	return 0;
	
} /*
7 2
1 5 1 5 1 5 1
1 1 1 1 1 1 1

*/