#include <cstdio>
#include <algorithm>

int n, k;

inline int count(int s) { return std::min(n, s - 1) - std::max(1, s - n) + 1; }

int main() {
	std::scanf("%d%d", &n, &k);
	if(k < 0) k = -k;
	long long ans = 0;
	// a + b = s
	// 1 <= a <= n
	// 1 <= b <= n
	// a_max = min(n, s - 1)
	// a_min = max(1, s - n)
	for(int i = 2; i <= 2 * n - k; i++)
		ans += (long long)count(i) * count(i + k);
	std::printf("%lld\n", ans);
	return 0;
}