#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 2e5 + 5;

int a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int j = n, cnt = 0;
		while(j > 1 && a[j - 1] == a[n]) j--;
		while(j > 1) {
			cnt++;
			j -= n - j + 1;
			while(j > 1 && a[j - 1] == a[n]) j--;
		}
		printf("%d\n", cnt);
	}
	return 0;
}