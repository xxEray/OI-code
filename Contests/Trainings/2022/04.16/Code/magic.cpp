#include <cstdio>
#include <algorithm>

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int a[N];
int n;

int last[N], l[N], f[N];

int main() {
#ifndef DEBUG
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) l[i] = last[a[i]], last[a[i]] = i;
	f[0] = 1;
	for(int i = 1; i <= n; i++) if(l[i] == i - 1 || l[i] == 0) l[i] = n + 1;
	for(int i = 1; i <= n; i++) f[i] = (f[i - 1] + f[l[i]]) % MOD;
	// for(int i = 1; i <= n; i++) printf("%d ", f[i]);
	printf("%d\n", f[n]);
	return 0;
} /*
5
2 1 2 1 2
*/