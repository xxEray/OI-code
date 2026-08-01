#include <cstdio>
#include <algorithm>

const int N = 5e5 + 5;

int a[N];
int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int ans = 0;
		for(int i = 0; i < m; i++) {
			int cnt[2] = {0, 0};
			for(int j = 1; j <= n; j++) cnt[a[j] >> i & 1]++;
			if(cnt[1] > cnt[0]) ans |= 1 << i;
		}
		printf("%d\n", ans);
	}
	return 0;
}