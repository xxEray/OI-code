#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 200 + 5;

int n;
int a[N], b[N], c[N], d[N];

int f[N][N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]), b[c[i]]++;
	for(int i = 1; i <= n; i++) a[c[i]] += d[i];
	// for(int i = 1; i <= n; i++) printf("%d %d\n", a[i], b[i]);
	LL coe = 1;
	for(int i = 1; i <= n; i++) (coe *= )
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 0; k <= n; k++)

	return 0;
}