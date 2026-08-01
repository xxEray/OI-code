#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;

int n;
int a[N];

int f[N];
int trie[N * 32][2], val[N * 32][2][2];
int tot;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) f[i] = 0;
		for(int i = 1; i <= tot; i++) trie[i][0] = trie[i][1] = val[i][0][0] = val[i][0][1] = val[i][1][0] = val[i][1][1] = 0;
		tot = 1;
		for(int i = 1; i <= n; i++) {
			int now = 1;
			f[i] = 1;
			for(int j = 31; j >= 0; j--) {
				f[i] = std::max(f[i], val[now][(i - 1) >> j & 1][~a[i] >> j & 1] + 1);
				if(!trie[now][(a[i] ^ (i - 1)) >> j & 1]) break;
				now = trie[now][(a[i] ^ (i - 1)) >> j & 1];
			}
			now = 1;
			for(int j = 31; j >= 0; j--) {
				val[now][a[i] >> j & 1][(i - 1) >> j & 1] = std::max(val[now][a[i] >> j & 1][(i - 1) >> j & 1], f[i]);
				// printf("val[%d][%d][%d] max= %d\n", now, a[i] >> j & 1, (i - 1) >> j & 1, f[i]);
				if(!trie[now][(a[i] ^ (i - 1)) >> j & 1]) trie[now][(a[i] ^ (i - 1)) >> j & 1] = ++tot;
				now = trie[now][(a[i] ^ (i - 1)) >> j & 1];
			}
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}