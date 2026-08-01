#include <cstdio>
#include <algorithm>
#include <deque>
#include <cassert>

typedef long long LL;

const int N = 4e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL m;
LL a[N], b[N];

int nxt[N], type[N];
LL f[N];
void calculate() {
	int last = 2 * n + 1;
	nxt[2 * n + 1] = 2 * n + 1, a[2 * n + 1] = LLINF;
	for(int i = 2 * n, j = 2 * n + 1; i >= 1; i--) {
		if(i < 2 * n && j > 2 * n) j = 2 * n;
		while(j > i + 1 && a[j] - a[i] > m) j--;
		if(a[last] - a[i] > m) {
			assert(j == 2 * n + 1 || b[j] == 2);
			nxt[i] = j, f[i] = m * b[i] - (m - a[j] + a[i]) * 2;
			type[i] = 1;
		} else {
			nxt[i] = last, f[i] = (a[last] - a[i]) * b[i];
			type[i] = 2;
		}
		if(b[i] == 1) last = i;
		f[i] = std::min(f[i], LLINF);
	}
	// for(int i = 1; i <= 2 * n; i++) printf("nxt[%d] = %d, f[%d] = %lld\n", i, nxt[i], i, f[i]);
}

int go[21][N];
LL gov[21][N];
int lg[N];
void init_ST() {
	lg[0] = -1;
	for(int i = 1; i <= 2 * n + 1; i++) lg[i] = lg[i >> 1] + 1, go[0][i] = nxt[i], gov[0][i] = f[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= 2 * n + 1; i++) {
			go[j][i] = go[j - 1][go[j - 1][i]];
			gov[j][i] = gov[j - 1][i] + gov[j - 1][go[j - 1][i]];
		}
}
LL calc(int l, int r) {
	// printf("calc(%d, %d) = ", l, r);
	LL ans = 0;
	for(int i = 20; i >= 0; i--) if(go[i][l] <= r + 1) ans += gov[i][l], l = go[i][l];
	// printf("%lld\n", ans);
	// assert(ans < LLINF);
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &m);
		for(int i = 2; i <= n; i++) scanf("%lld", &a[i]), a[i + n] = a[i];
		scanf("%lld", &a[1]), a[n + 1] = a[1];
		for(int i = 1; i <= n; i++) scanf("%lld", &b[i]), b[i + n] = b[i];
		for(int i = 1; i <= 2 * n; i++) a[i] += a[i - 1];
		calculate();
		init_ST();
		for(int i = 1; i <= n; i++) {
			int p = i, cnt = 0;
			LL ans;
			for(int j = 20; j >= 0; j--) if(go[j][p] <= i + n) p = go[j][p], cnt += (1 << j);
			if(cnt == 0) { printf("%lld ", (a[i + n] - a[i]) * b[i]); continue; }
			int lp = i;
			for(int j = 0; j <= 20; j++) if((cnt - 1) >> j & 1) lp = go[j][lp];
			// printf("p = %d, lp = %d\n", p, lp);
			if(type[lp] == 1) ans = calc(i, lp - 1) + std::min(m, a[i + n] - a[lp]) * b[lp] + 2 * std::max(0LL, a[i + n] - a[lp] - m);
			else ans = calc(i, p - 1) + (a[i + n] - a[p]) * b[p];
			printf("%lld ", ans);
		}
		puts("");
	}
	return 0;
} /*
1
5 2
2 1 2 2 1
1 1 2 1 1
*/