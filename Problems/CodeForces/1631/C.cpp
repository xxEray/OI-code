#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = (1 << 16) + 5;

int n, m;
bool vis[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		assert((n & (n - 1)) == 0);
		n--;
		for(int i = 0; i <= n; i++) vis[i] = false;
		if(n == m) {
			if(n == 3) { puts("-1"); continue; }
			printf("%d %d\n", n, n - 1);
			printf("%d %d\n", 1, 3);
			vis[1] = vis[3] = vis[n - 1] = vis[n] = true;
		} else printf("%d %d\n", n, m), vis[n] = vis[m] = true;
		for(int i = 1; i <= n; i++) if(!vis[i]) {
			if(!vis[n ^ i]) printf("%d %d\n", i, n ^ i), vis[i] = vis[n ^ i] = true;
			else printf("%d %d\n", i, 0), vis[i] = vis[0] = true;
		}
	}
	return 0;
} /*
000
001
010
011
100
101
110
111
*/