#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N], b[N];
int st, n, m;

int ans[N], top;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &st, &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		int i = 1, j = 1, now = st;
		top = 0;
		while(i <= n || j <= m) {
			if(i <= n && a[i] == 0) ans[++top] = 0, i++, now++;
			else if(j <= m && b[j] == 0) ans[++top] = 0, j++, now++;
			else if(i <= n && a[i] <= now) ans[++top] = a[i], i++;
			else if(j <= m && b[j] <= now) ans[++top] = b[j], j++;
			else { top = -1; break; }
		}
		if(top == -1) printf("-1");
		else for(int i = 1; i <= top; i++) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}