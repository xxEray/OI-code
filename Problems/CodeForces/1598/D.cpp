#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 2e5 + 5;

int a[N], b[N];
int n;

std::map<int, int> mpa, mpb;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mpa.clear(), mpb.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), mpa[a[i]]++, mpb[b[i]]++;
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += (LL)(mpa[a[i]] - 1) * (mpb[b[i]] - 1);
		printf("%lld\n", (LL)n * (n - 1) * (n - 2) / 6 - ans);
	}
	return 0;
}