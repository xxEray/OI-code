#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N][2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%1d", &a[i][0]);
		for(int i = 1; i <= n; i++) scanf("%1d", &a[i][1]);
		bool flag = true;
		for(int i = 1; i <= n; i++) if(a[i][0] && a[i][1]) flag = false;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}