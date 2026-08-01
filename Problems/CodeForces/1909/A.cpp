#include <bits/stdc++.h>

const int N = 100 + 5;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		bool a[4] = {};
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			if(x < 0) a[0] = true;
			if(x > 0) a[1] = true;
			if(y < 0) a[2] = true;
			if(y > 0) a[3] = true;
		}
		if(a[0] && a[1] && a[2] && a[3]) puts("NO");
		else puts("YES");
	}
	return 0;
}