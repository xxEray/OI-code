#include <cstdio>

int n, m, k;

int main() {
	scanf("%d%d", &n, &m);
	k = m;
	int l = 1, r = m + 1;
	while(k--) {
		if(l >= r) l = m + 2, r = 2 * m + 1;
		printf("%d %d\n", l++, r--);
	}
	return 0;
}