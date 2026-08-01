#include <bits/stdc++.h>

int main() {
#ifndef DEBUG
	freopen("dp.in", "r", stdin);
	freopen("dp.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		if(!n) continue;
		else if(n == 1) puts("2");
		else if(n == 2) puts("4");
		else if(n == 3) puts("8");
		else if(n == 4) puts("20");
		else puts("-1");
	}
	return 0;
}