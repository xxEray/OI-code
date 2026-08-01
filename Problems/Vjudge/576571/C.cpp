#include <bits/stdc++.h>

const int N = 500 + 5;

int n;
int a[N];

int order[N], b[N * N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), order[i] = i, b[a[i]] = i;
	std::sort(order + 1, order + n + 1, [&](int x, int y) { return a[x] < a[y]; });
	int p = 1;
	for(int o = 1; o <= n; o++) {
		int i = order[o];
		if(p > a[i]) { puts("No"); return 0; }
		for(int _ = 1; _ < i; _++) {
			while(p < a[i] && b[p]) p++;
			if(p >= a[i]) { puts("No"); return 0; }
			b[p] = i, p++;
		}
	}
	std::reverse(order + 1, order + n + 1);
	p = n * n;
	for(int o = 1; o <= n; o++) {
		int i = order[o];
		if(p < a[i]) { puts("No"); return 0; }
		for(int _ = n; _ > i; _--) {
			while(p > a[i] && b[p]) p--;
			if(p <= a[i]) { puts("No"); return 0; }
			b[p] = i, p--;
		}
	}
	puts("Yes");
	for(int i = 1; i <= n * n; i++) printf("%d ", b[i]);
	puts("");
	return 0;
}