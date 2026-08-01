#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], b[N];
int n;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%1d", &b[i]);
		for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			if(!a[i]) continue;
			if(!b[i]) ans++;
			else if(i > 1 && b[i - 1]) b[i - 1] = 0, ans++;
			else if(i < n && b[i + 1]) b[i + 1] = 0, ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}