#include <cstdio>

typedef long long LL;

const int N = 45 + 5;

int n;

LL f[N][2];

int main() {
	scanf("%d", &n);
	f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++) {
		f[i][0] = f[i - 1][1] + f[i - 2][1];
		f[i][1] = f[i - 1][0] + f[i - 2][0];
	}
	printf("%lld\n", f[n][0] + f[n][1]);
	return 0;
}