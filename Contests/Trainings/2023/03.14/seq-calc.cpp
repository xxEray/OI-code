#include <cstdio>
#include <algorithm>

int a[100];

bool t[100];
int mex(int l, int r) {
	for(int i = 0; i < 100; i++) t[i] = 0;
	for(int i = l; i <= r; i++) t[a[i]] = 1;
	int x = 0;
	while(t[x]) x++;
	return x;
}

int cnt[100];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int l = 1; l <= n; l++) for(int r = l; r <= n; r++) cnt[mex(l, r)]++;
	for(int i = 0; i <= n; i++) if(cnt[i]) printf("%d: %d\n", i, cnt[i]);
	return 0;
}
