#include <cstdio>
#include <algorithm>

typedef long long LL;

int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int ansi, ansj, ansk;
		int l = 1, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			printf("? %d %d\n", 1, mid), fflush(stdout);
			LL ret; scanf("%lld", &ret);
			if(ret == 0) l = mid + 1;
			else r = mid;
		}
		ansi = l - 1;
		LL ret1, ret2;
		printf("? %d %d\n", ansi, n), fflush(stdout);
		scanf("%lld", &ret1);
		printf("? %d %d\n", ansi + 1, n), fflush(stdout);
		scanf("%lld", &ret2);
		ansj = ansi + ret1 - ret2;
		printf("? %d %d\n", ansj + 1, n), fflush(stdout);
		scanf("%lld", &ret1);
		printf("? %d %d\n", ansj + 2, n), fflush(stdout);
		scanf("%lld", &ret2);
		ansk = ansj + 1 + ret1 - ret2;
		printf("! %d %d %d\n", ansi, ansj + 1, ansk); fflush(stdout);
	}
	return 0;
}