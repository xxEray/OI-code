#include <bits/stdc++.h>

const int N = 500 + 5;
const int to[] = {0, 2, 4, 1, 3};

int n;
int a[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) printf("%d ", to[a[i][j]]);
		puts("");
	}
	return 0;
}