#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n;

LL cf[N];

LL gcd_(LL a, LL b) { return b == 0 ? a : gcd_(b, a % b); }
LL gcd(LL a, LL b) { return gcd_(std::abs(a), std::abs(b)); }
LL go[N][21];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		n--;
		for(int i = 1; i <= n; i++) cf[i] = a[i + 1] - a[i];
		for(int i = 1; i <= n; i++) go[i][0] = cf[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[i][j] = gcd(go[i][j - 1], go[i + (1 << (j - 1))][j - 1]);
		int ans = 1;
		for(int l = 1; l <= n; l++) {
			if(cf[l] == 1) continue;
			int r = l;
			LL g = 0;
			for(int j = 20; j >= 0; j--) if(r + (1 << j) <= n + 1 && gcd(g, go[r][j]) > 1) g = gcd(g, go[r][j]), r += (1 << j);
			// printf("%d~: %d\n", l, r - l + 1);
			ans = std::max(ans, r - l + 1);
		}
		printf("%d\n", ans);
	}
	return 0;
} /*
1
7
5 11 18 3 20 20 8 

*/