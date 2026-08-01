#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

int b[N], cn;
int f[N], g[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		cn = 0;
		for(int i = 1; i <= n; i++) b[i] = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] == a[i - 1]) b[cn]++;
			else b[++cn]++;
		int sum = 0;
		for(int i = 0, j = 1; i < 30; i++) {
			int v = 1 << i;
			while(j <= cn && b[j] + sum <= v) sum += b[j], j++;
			f[i] = sum;
		}
		sum = 0;
		for(int i = 0, j = cn; i < 30; i++) {
			int v = 1 << i;
			while(j >= 1 && b[j] + sum <= v) sum += b[j], j--;
			g[i] = sum;
		}
		int ans = INF;
		for(int i = 0; i < 30; i++)
			for(int j = 0; j < 30; j++) {
				int rest = n - f[i] - g[j];
				int v = 1;
				while(v < rest) v <<= 1;
				int ret = (1 << i) + (1 << j) + v - n;
				ans = std::min(ans, ret);
			}
		printf("%d\n", ans);
	}
	return 0;
}