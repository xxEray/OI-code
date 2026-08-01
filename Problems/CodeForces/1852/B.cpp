#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
struct Node { int v, id; } a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].id = i;
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.v > y.v; });
		for(int i = 1; i <= n; i++) b[i].id = a[i].id;
		int cnt = n;
		if(a[1].v < n) {
			for(int j = n; j > a[1].v; j--) b[j].v = -cnt;
			cnt--;
		}
		int bd = 0;
		while(bd < n && a[bd + 1].v >= bd + 1) bd++;
		// printf("bd = %d\n", bd);
		for(int i = 1; i <= bd; i++) {
			// if(i > 1 && a[i].v == a[i - 1].v) { b[i].v = b[i - 1].v; continue; }
			bool empty = true;
			for(int j = a[i].v; j > i && (i == bd || j > a[i + 1].v); j--) b[j].v = -(cnt - 1), empty = false;
			b[i].v = cnt;
			cnt -= (empty ? 1 : 2);
			// printf("%d: ", i); for(int j = 1; j <= n; j++) printf("%d ", b[j].v); puts("");
		}
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (b[i].v != 0);
		for(int i = 1, j = n; i <= n; i++) {
			while(j >= 1 && b[i].v + b[j].v < 0) j--;
			if(b[i].v + b[j].v == 0) flag = false;
			flag &= (j == a[i].v);
		}
		// printf("test: "); for(int i = 1; i <= n; i++) printf("%d ", b[i].v); puts("");
		if(flag) {
			std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.id < y.id; });
			puts("YES");
			for(int i = 1; i <= n; i++) printf("%d ", b[i].v);
			puts("");
		} else puts("NO");
	}
	return 0;
}