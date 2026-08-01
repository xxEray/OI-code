#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;

LL a[N], b[N], fib[N];
int n, m; LL modnum;

void mod(LL &x) { x = (x % modnum + modnum) % modnum; }

int main() {
	scanf("%d%d%lld", &n, &m, &modnum);
	for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); b[i] += x; }
	for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); b[i] -= x; }
	a[1] = b[1], mod(a[2] = b[2] - b[1]);
	int cnt = !a[1] + !a[2];
	for(int i = 3; i <= n + 2; i++) mod(a[i] = b[i] - b[i - 1] - b[i - 2]), cnt += !a[i];
	fib[1] = fib[2] = 1;
	for(int i = 3; i <= n + 2; i++) mod(fib[i] = fib[i - 1] + fib[i - 2]);
	// for(int i = 1; i <= n + 2; i++) printf("%lld ", a[i]);
	// printf("\ncnt = %d\n", cnt);
	for(int i = 1; i <= m; i++) {
		char c[2]; int l, r; scanf("%s%d%d", c, &l, &r);
		int op = (c[0] == 'A' ? 1 : -1);
		cnt -= !a[l] + !a[l + 1] + (l != r && !a[r + 1]) + !a[r + 2];
		mod(a[l] += op * 1);
		mod(a[r + 1] += -op * fib[r - l + 2]);
		mod(a[r + 2] += -op * fib[r - l + 1]);
		cnt += !a[l] + !a[l + 1] + (l != r && !a[r + 1]) + !a[r + 2];
		// for(int j = 1; j <= n + 2; j++) printf("%lld ", a[j]);
		// printf("\ncnt = %d\n", cnt);
		puts(cnt == n + 2 ? "YES" : "NO");
	}
	return 0;
}