#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 3000 + 5;

typedef long long LL;

LL a[N];
int n;

LL cnt[N * N + N];

#define hash(a, b) ((a) * N + (b))

int main() {
	int T;
	std::scanf("%d", &T);
	while(T--) {
		std::memset(cnt, 0, sizeof(cnt));
		std::scanf("%d", &n);
		for(int i = 1; i <= n; i++) std::scanf("%lld", &a[i]);
		LL ans = 0;
		for(int pos = n; pos >= 2; pos--) {
			for(int i = pos + 1; i <= n; i++) cnt[hash(a[pos], a[i])]++;
			for(int i = 1; i < pos - 1; i++) ans += cnt[hash(a[i], a[pos - 1])];
		}
		std::printf("%lld\n", ans);
	}
	return 0;
}