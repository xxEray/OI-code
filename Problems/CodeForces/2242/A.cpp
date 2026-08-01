#include <bits/stdc++.h>

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		int cnt2 = 0, cnt3 = 0;
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			cnt2 += (x >= 2), cnt3 += (x >= 3);
		}
		if(cnt2 >= 2 || cnt3 >= 1) puts("YES");
		else puts("NO");
	}
	return 0;
}