#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int ans = 0;
		for(int i = 1, j = n; i < j;) {
			while(i < j && a[i] == 0) i++;
			while(i < j && a[j] == 1) j--;
			if(i < j) i++, j--, ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
} /*
*/