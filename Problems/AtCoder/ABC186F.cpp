#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
typedef long long LL;

int n, m, cntob;
int mxr[N], mxc[N];

int qry[N];

namespace BIT { // 树状数组
	int t[N];
	void add(int x) { while(x <= n) t[x]++, x += (x & -x); }
	int query(int x) { int ret = 0; while(x > 0) ret += t[x], x -= (x & -x); return ret; }
}

int main() {
	std::scanf("%d%d%d", &n, &m, &cntob);
	for(int i = 1; i <= n; i++) mxr[i] = m; // 第 i 行第一步可以到达最右的地方
	for(int i = 1; i <= m; i++) mxc[i] = n; // 第 i 列第一步可以到达最下的地方
	for(int i = 1; i <= cntob; i++) {
		int x, y;
		std::scanf("%d%d", &x, &y);
		mxr[x] = std::min(mxr[x], y - 1);
		mxc[y] = std::min(mxc[y], x - 1);
	}
	for(int i = mxr[1] + 1; i <= m; i++) mxc[i] = 0;
	for(int i = mxc[1] + 1; i <= n; i++) mxr[i] = 0;
	LL ans = 0;
	for(int i = 1; i <= m; i++) ans += mxc[i];
	int cntqry = mxc[1];
	for(int i = 1; i <= cntqry; i++) qry[i] = i;
	std::sort(qry + 1, qry + cntqry + 1, [](int x, int y) { return mxr[x] < mxr[y]; });
	int now = 1;
	for(int i = 1; i <= m; i++) {
		BIT::add(mxc[i] + 1);
		for(; mxr[qry[now]] <= i && now <= cntqry; now++)
			ans += BIT::query(qry[now]);
	}
	std::printf("%lld\n", ans);
	return 0;
} /* self
about TLE (with 14 ACs, 1 WA and 14 TLEs):
	BIT's indexes should add 1 each, because of zeros.
	(0 can't be the index of BIT)
about WA (with 21 ACs and 8 WAs):
	there shouldn't be n (H in the problem) querys
	(line 32 shouldn't be n but mxc[1])
*/