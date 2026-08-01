#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N], w[N];
int n, m;

int sml[N], smr[N]; // sum-left, sum-right

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) std::scanf("%d", &w[i]);
	std::sort(a + 1, a + n + 1);
	sml[0] = sml[1] = smr[n + 1] = smr[n] = 0;
	for(int i = 2; i <= n; i++) sml[i] = sml[i - 2] + a[i] - a[i - 1];
	for(int i = n - 1; i >= 1; i--) smr[i] = smr[i + 2] + a[i + 1] - a[i];
	int ans = INF;
	for(int i = 1; i <= m; i++) {
		int pos = std::upper_bound(a + 1, a + n + 1, w[i]) - a;
		if(pos & 1) ans = std::min(ans, sml[pos - 1] + smr[pos + 1] + std::abs(a[pos] - w[i]));
		else ans = std::min(ans, sml[pos - 2] + smr[pos] + std::abs(a[pos - 1] - w[i]));
	}
	std::printf("%d\n", ans);
	return 0;
}