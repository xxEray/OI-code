#include <bits/stdc++.h>

const int N = 1000 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x, y;
		scanf("%d%d%d", &x, &y, &n);
		a[1] = x, a[n] = y;
		int d = 1;
		for(int i = n - 1; i >= 2; i--) a[i] = a[i + 1] - d, d++;
		if(a[2] - a[1] > a[3] - a[2]) {
			for(int i = 1; i <= n; i++) printf("%d ", a[i]);
			puts("");
		} else puts("-1");
	}
	return 0;
}