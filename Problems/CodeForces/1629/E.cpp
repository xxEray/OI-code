#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

int a[N][N];
int n;

int cnt[N][N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]), cnt[i][j] = 0;
		int ans = 0;
		for(int i = 2; i <= n; i++) for(int j = 1; j <= n; j++) if(!cnt[i - 1][j])
			cnt[i - 1][j] ^= 1, cnt[i][j - 1] ^= 1, cnt[i + 1][j] ^= 1, cnt[i][j + 1] ^= 1, ans ^= a[i][j];
		printf("%d\n", ans);
	}
	return 0;
}