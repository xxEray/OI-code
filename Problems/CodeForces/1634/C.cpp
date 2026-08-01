#include <cstdio>
#include <algorithm>

const int N = 500 + 5;

int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		if(m == 1) {
			puts("YES");
			for(int i = 1; i <= n; i++) printf("%d\n", i);
		} else if(!((n * m) & 1) && n * m / 2 % m == 0) {
			puts("YES");
			int val = 1;
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					printf("%d ", val);
					val += 2;
					if(val > n * m) val = 2;
				}
				puts("");
			}
		} else puts("NO");
	}
	return 0;
}