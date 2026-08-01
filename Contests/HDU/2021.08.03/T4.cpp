#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2e6 + 5;

int a[N];
int n;

int appear[N];
std::vector<int> pos[N];
std::vector<std::pair<int, int>> ops;

#define div(x, y) ((x) % (y) ? (exit(1), 0) : (x) / (y))

struct SegmentTree { // 伪线段树
	struct BIT {
		LL t[N];
		int size;
		void add(int x, LL v) { while(x <= size) t[x] += v, x += x & -x; }
		LL query(int x) { LL ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
	} t0, t1, t2;
	void add(int r, LL v) { t0.add(r, v), t1.add(r, v * r), t2.add(r, v * r * r); }
	void add(int l, int r, LL v) { add(l, v), add(r + 1, -v); }
	LL query(int r) { return (((LL)r * r + 3 * r + 2) * t0.query(r) + (-2LL * r - 3) * t1.query(r) + t2.query(r)) / 2; }
	LL query(int l, int r) { return query(r) - (l == 1 ? 0 : query(l - 1)); }
} seg;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(seg.t0.t, 0, sizeof(seg.t0.t));
		memset(seg.t1.t, 0, sizeof(seg.t1.t));
		memset(seg.t2.t, 0, sizeof(seg.t2.t));
		memset(appear, 0, sizeof(appear));
		for(int i = 0; i < N; i++) pos[i].clear();
		seg.t0.size = seg.t1.size = seg.t2.size = 2000000;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++)
			if(!appear[a[i]]) appear[a[i]] = i, pos[i].push_back(i);
			else pos[appear[a[i]]].push_back(i);
		LL ans = 0;
		for(int k = 1; k <= n; k++) {
			if(pos[k].empty()) continue;
			std::vector<int> p = pos[k];
			int size = p.size();
			for(int i = 0; i < size; i++) {
				int A = p[i] - (i == 0 ? 1 : p[i - 1] + 1);
				int B = (i == size - 1 ? n : p[i + 1] - 1) - p[i];
				seg.add(2 * i - p[i] + 1000000, 2 * i + A - p[i] + 1000000, 1);
				ops.push_back({2 * i - p[i] + 1000000, 2 * i + A - p[i] + 1000000});
				ans += seg.query(2 * i - p[i] - B + 1000000, 2 * i - p[i] + 1000000);
			}
			while(!ops.empty()) seg.add(ops.back().first, ops.back().second, -1), ops.pop_back();
		}
		printf("%lld\n", ans);
	}
	return 0;
}