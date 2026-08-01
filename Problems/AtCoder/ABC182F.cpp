#include <cstdio>
#include <iostream>

typedef long long LL;

const int N = 50 + 3;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL x;
LL a[N];

LL b[N], k[N];
LL f[N][2];

int main() {
	std::scanf("%d%lld", &n, &x);
	for(int i = 1; i <= n; i++) std::scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) b[i] = a[i + 1] / a[i];
	for(int i = n; i >= 1; i--) k[i] = x / a[i], x %= a[i];
	if(n == 1) { std::printf("1\n"); return 0; }
	f[1][0] = 1;
	if(k[1]) f[1][1] = 1;
	for(int i = 2; i <= n - 1; i++) {
		f[i][0] = f[i - 1][0]; // s_i 可以为 0，这样 p_i 无限制
		f[i][1] = f[i - 1][1]; // s_i 可以为 0
		if(k[i]) f[i][1] += f[i - 1][0]; // s_i 不为零则进位
		if(k[i] != b[i] - 1) f[i][0] += f[i - 1][1]; // s_i 不为零则进位
	}
	std::printf("%lld\n", f[n - 1][0] + f[n - 1][1]);
	return 0;
}