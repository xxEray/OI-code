#include <cstdio>

typedef long long LL;

const int N = 44 + 5;
LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL k;

LL f[N][2];

#define val(x) (f[(x)][0] + f[(x)][1])

int main() {
	scanf("%d%lld", &n, &k);
	f[n][0] = f[n][1] = 1;
	for(int i = n - 1; i >= 1; i--) {
		f[i][0] = f[i + 1][0] + f[i + 1][1];
		f[i][1] = f[i + 1][0];
	}
	if(f[1][0] + f[1][1] < k) { puts("-1"); return 0; }
	for(int i = 1; i <= n; i++)
		if(f[i][0] < k) printf("1"), k -= f[i][0];
		else printf("0");
	return 0;
}