#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 1e9 + 7;

int n;

int a[N];
template<typename T, int L, int R> struct Array { T data[R - L + 1]; T &operator[](int ind) { return data[ind - L]; } };
Array<int, -N, N> lcnt, rcnt, sum;
int lgt[N], rgt[N];

int main() {
// #ifndef DEBUG
	// freopen("bracket.in", "r", stdin);
	// freopen("bracket.out", "w", stdout);
// #endif
	char ch; n = 0;
	while(ch = getchar(), (ch == '(' || ch == ')')) n++, a[n] = a[n - 1] + (ch == '(' ? 1 : -1);
	for(int i = 0; i <= n; i++)
		if(a[i] < a[i + 1] || i == n) lcnt[a[i]]++, lgt[i] = lcnt[a[i]];
		else lcnt[a[i]] = 0, lgt[i] = 0;
	for(int i = n; i >= 0; i--)
		if(a[i] < a[i + 1] || i == n) rcnt[a[i]]++, rgt[i] = rcnt[a[i]] - 1;
		else rcnt[a[i]] = 1, rgt[i] = 0;
//	for(int i = 0; i <= n; i++) printf("gt[%d] = {l=%lld, r=%lld}\n", i, lgt[i], rgt[i]);
	memset(lcnt.data, 0, sizeof(lcnt.data));
	memset(rcnt.data, 0, sizeof(rcnt.data));
	LL ans = 0, ret = 0;
	lcnt[0]++;
	for(int i = 1; i <= n && a[i] >= a[0]; i++) rcnt[a[i]]++;
	for(int i = 0; i <= n; i++) sum[i] = lcnt[i] * rcnt[i] % MOD, (ret += sum[i]) %= MOD;
	for(int i = 1; i <= n; i++) {
		int v = a[i - 1];
		(ret += MOD - sum[v]) %= MOD;
		sum[v] = (LL)lgt[i - 1] * rgt[i - 1] % MOD;
		(ret += sum[v]) %= MOD;
		ans += ret * i % MOD;
//		printf("%lld * %d\n", ret, i);
	}
	printf("%lld\n", ans);
	return 0;
} /*
(()())
*/
