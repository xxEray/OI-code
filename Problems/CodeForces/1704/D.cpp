#include <cstdio>
#include <algorithm>
#include <vector>
#include "biginteger"

typedef BigInteger LL;

const int N = 1e5 + 5;

std::vector<LL> a[N];
LL sum[N];
int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			a[i].clear(), a[i].shrink_to_fit();
			a[i].push_back(0);
			sum[i] = 0;
			for(int j = 1; j <= m; j++) {
				long long x;
				scanf("%lld", &x);
				a[i].push_back(a[i].back() + x);
				sum[i] += a[i].back();
			}
		}
		int special = 0, normal;
		if(sum[1] != sum[2] && sum[1] != sum[3]) special = 1, normal = 2;
		else {
			normal = 1;
			for(int i = 2; i <= n; i++) if(sum[i] != sum[1]) special = i;
		}
		printf("%d %lld\n", special, (long long)(sum[normal] - sum[special]));
	}
	return 0;
}