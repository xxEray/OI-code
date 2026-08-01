#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N], b[N];
LL n, m, K;

LL mod(LL x) { return (x % K + K) % K; }

int main() {
	scanf("%lld%lld%lld", &n, &m, &K);
	LL suma = 0, sumb = 0;
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), suma = mod(suma + a[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &b[i]), sumb = mod(sumb + b[i]);
	if(suma != sumb) { puts("-1"); return 0; }
	suma = sumb = 0;
	for(int i = 1; i <= n; i++) suma += mod(m * (K - 1) - a[i]);
	for(int i = 1; i <= m; i++) sumb += mod(n * (K - 1) - b[i]);
	printf("%lld\n", n * m * (K - 1) - std::max(suma, sumb));
	return 0;
}