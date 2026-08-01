#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n, m, Q;
struct Node { int l, r; } a[N];

bool tin[N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		for(int i = 1; i <= n; i++) tin[i] = false;
		for(int i = 1; i <= m; i++) if(l <= a[i].l && a[i].r <= r)
			for(int j = a[i].l; j <= a[i].r; j++)
				tin[j] = true;
		bool flag = true;
		for(int i = l; i <= r; i++) flag &= tin[i];
		puts(flag ? "YES" : "NO");
	}
	return 0;
}