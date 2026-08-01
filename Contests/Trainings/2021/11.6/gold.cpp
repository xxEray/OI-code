#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

typedef long long LL;

const int N = 2000 + 5;
const int M = 3e5 + 5;
const LL W_MAX = 1e18 + 1;

LL a[N];
struct Query { int id, l, r; LL w; } q[M];
bool operator<(Query x, Query y) { return x.r < y.r; }
int n, m;

int cnt = 0;
LL out[M], t[N];
std::map<LL, int> mp;
std::set<LL> exist;

struct SegmentTree {
	LL t[N * N << 2];
	void setmax(int qind, LL qv, int x = 1, int l = 1, int r = cnt) {
		if(l == r) { t[x] = std::max(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) setmax(qind, qv, x << 1, l, mid);
		else setmax(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	LL querymax(int ql, int qr, int x = 1, int l = 1, int r = cnt) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		LL ret = -W_MAX;
		if(ql <= mid) ret = std::max(ret, querymax(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = std::max(ret, querymax(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
} seg;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) { int l, r; LL w; scanf("%d%d%lld", &l, &r, &w); q[i] = (Query){i, l, r, w}; }
	for(int i = 1; i <= n; i++) {
		LL sum = 0;
		for(int j = i; j >= 1; j--) {
			sum += a[j];
			if(sum >= W_MAX) break;
			if(mp.find(sum) == mp.end()) cnt++, mp[sum] = cnt, t[cnt] = sum;
		}
	}
	std::sort(q + 1, q + m + 1);
	std::sort(t + 1, t + cnt + 1);
	int j = 0;
	for(int i = 1; i <= m; i++) {
		while(j < q[i].r) {
			j++;
			LL sum = 0;
			for(int k = j; k >= 1; k--) {
				sum += a[k];
				if(sum >= W_MAX) break;
				seg.setmax(mp[sum], k), exist.insert(sum);
				printf("mp[%lld] max= %d\n", sum, k);
			}
		}
		int l = 1, r = cnt + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(t[mid] <= q[i].w && mid <= cnt && seg.querymax(mid, cnt) >= q[i].l) l = mid + 1;
			else r = mid;
		}
		auto iter = exist.upper_bound(t[l - 1]);
		out[q[i].id] = (iter == exist.begin() ? 0 : *--iter);
		printf("exist: "); for(auto x : exist) printf("%lld ", x); printf("\n");
		printf("Question %d: ans = (smallest x <= t[%d]=%lld) = %lld\n", q[i].id, l - 1, t[l - 1], out[q[i].id]);
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	return 0;
} /*
6 3
3 6 2 1 4 5
3 6 6
1 2 2
2 5 100
*/