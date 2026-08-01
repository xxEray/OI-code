#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n;

int ans[N], f[N], last[N][2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) ans[i] = last[i][0] = last[i][1] = f[i] = 0;
		for(int i = 1; i <= n; i++) {
			if(last[a[i]][!(i & 1)]) f[i] = f[last[a[i]][!(i & 1)]] + 1;
			else f[i] = 1;
			ans[a[i]] = std::max(ans[a[i]], f[i]);
			last[a[i]][i & 1] = i;
		}
		for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}