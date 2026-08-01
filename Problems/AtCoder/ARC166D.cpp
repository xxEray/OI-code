#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = n + 1; i >= 1; i--) b[i] = b[i] - b[i - 1];
	// printf("b: "); for(int i = 1; i <= n + 1; i++) printf("%d ", b[i]); puts("");
	bool inf = true;
	int mn = INF;
	for(int i = 1, j = 1; i <= n + 1; i++) if(b[i] < 0) {
		int x = -b[i];
		while(b[j] < x) x -= std::max(b[j], 0), j++;
		b[j] -= x;
		if(x && j != 1 && i != n + 1) inf = false, mn = std::min(mn, a[i] - a[j - 1] - 2);
	}
	if(inf) puts("-1");
	else printf("%d\n", mn);
	return 0;
}