#include <cstdio>
#include <algorithm>

const int N = 3 + 5;

int a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x;
		scanf("%d", &x);
		for(int i = 1; i <= 3; i++) scanf("%d", &a[i]);
		int cnt = 0;
		while(a[x] && a[x] != x) x = a[x], cnt++;
		puts(cnt == 2 ? "YES" : "NO");
	}
	return 0;
}