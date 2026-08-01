#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N];
int n;

int g[N << 2][20];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int gcds(int st, int len) {
	int r = 0;
	for(int i = 19; i >= 0; i--)
		if(len & (1 << i)) {
			r = gcd(r, g[st][i]), st += (1 << i), len -= (1 << i);
			if(st > n) st -= n;
		}
	return r;
}

bool check(int x) {
	int r = gcds(1, x);
	for(int i = 2; i <= n; i++) if(gcds(i, x) != r) return true;
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), g[i][0] = g[i + n][0] = a[i];
		for(int i = 1; i < 20; i++)
			for(int j = 1; j + (1 << i) - 1 <= 2 * n; j++)
				g[j][i] = g[j + n][i] = gcd(g[j][i - 1], g[j + (1 << (i - 1))][i - 1]);
		// for(int i = 1; i <= n; i++) printf("gcds(%d, %d) = %d\n", i, 2, gcds(i, 2));
		int l = 1, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) l = mid + 1;
			else r = mid;
		}
		printf("%d\n", l - 1);
	}
	return 0;
}