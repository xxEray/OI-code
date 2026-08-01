#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 17 + 1;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Point { LL x, y, z; } a[N];
int n;

LL distance(const Point &x, const Point &y) {
	LL ret = std::abs(x.x - y.x) + std::abs(x.y - y.y) + std::max(0LL, x.z - y.z);
	return ret;
}

LL f[1 << N][N];

int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) std::scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z);
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++)
		for(int i = 1; i <= n; i++)
			f[s][i] = LLINF;
	f[1][1] = 0;
	for(int s = 0; s <= U; s++)
		for(int i = 1; i <= n; i++)	{
			if(!(s & (1 << (i - 1)))) continue;
			for(int j = 1; j <= n; j++) {
				if(s & (1 << (j - 1))) continue;
				f[s | (1 << (j - 1))][j] = std::min(f[s | (1 << (j - 1))][j], f[s][i] + distance(a[i], a[j]));
			}
		}
	LL ans = LLINF;
	for(int i = 1; i <= n; i++) ans = std::min(ans, f[U][i] + distance(a[i], a[1]));
	std::printf("%lld\n", ans);
	return 0;
}