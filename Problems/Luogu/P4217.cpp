#include <cstdio>
#include <algorithm>
#include <cassert>
#include <set>

typedef long long LL;
const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL sf[N], tf[N], tc[N], lc[N], rc[N];

std::set<int> st;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	int id[N << 2];
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		for(int i = ql; i <= qr; i++) t[i] += qv;
	}
	void set(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		t[qind] = qv;
	}
	LL get(int qind, int x = 1, int l = 1, int r = n) {
		return t[x];
	}
	int minid(int ql, int qr, int x = 1, int l = 1, int r = n) {
		LL ret = LLINF, rid = 0;
		for(int i = ql; i <= qr; i++) if(t[i] <= ret) rid = i, ret = t[i];
		return rid;
	}
	LL min(int ql, int qr, int x = 1, int l = 1, int r = n) {
		LL ret = LLINF;
		for(int i = ql; i <= qr; i++) ret = std::min(ret, t[i]);
		return ret;
	}
} segrc, seglc, seglf;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &sf[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &tf[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &tc[i]);
	for(int i = 1; i < n; i++) scanf("%lld", &lc[i]);
	for(int i = 1; i < n; i++) scanf("%lld", &rc[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) segrc.set(i, tc[i]), seglc.set(i, tc[i]);
	for(int i = 1; i < n; i++) segrc.add(i + 1, n, rc[i]);
	for(int i = 1; i <= n; i++) seglf.set(i, LLINF), st.insert(i);
	for(int i = 1; i <= n; i++) {
		LL total = sf[i];
		while(total) {
			LL fl = seglc.min(1, i - 1), fr = segrc.min(i, n);
			if(fl > fr) {
				int j = segrc.minid(i, n);
				LL flow = std::min(total, tf[j]);
				printf("%d -> %d (c=%lld,f=%lld) A\n", i, j, fr, flow);
				if(!flow) return 0;
				tf[j] -= flow, total -= flow;
				if(!tf[j]) seglc.set(j, LLINF), segrc.set(j, LLINF);
				ans += flow * fr;
				if(!tf[j]) segrc.set(j, LLINF);
				while(!st.empty() && *st.lower_bound(i) <= j - 1) {
					int u = *st.lower_bound(i);
					st.erase(u);
					seglf.set(u, 0);
					seglc.add(1, u, -rc[u] - lc[u]);
				}
				seglf.add(i, j - 1, flow);
			} else {
				int j = seglc.minid(1, i - 1);
				LL flow = std::min({total, tf[j], seglf.min(j, i - 1)});
				printf("%d -> %d (c=%lld,f=%lld) B\n", i, j, fl, flow);
				if(!flow) return 0;
				tf[j] -= flow, total -= flow;
				if(!tf[j]) seglc.set(j, LLINF), segrc.set(j, LLINF);
				ans += flow * fl;
				seglf.add(j, i - 1, -flow);
				while(seglf.min(j, i - 1) == 0) {
					int u = seglf.minid(j, i - 1);
					st.insert(u);
					seglf.set(u, LLINF);
					seglc.add(1, u, lc[u] + rc[u]);
				}
			}
		}
		segrc.add(i + 1, n, -rc[i]);
		seglc.add(1, i, lc[i]);
	}
	printf("%lld\n", ans);
	return 0;
}