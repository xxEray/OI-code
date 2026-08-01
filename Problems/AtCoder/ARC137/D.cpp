#include <cstdio>
#include <algorithm>

const int N = 1e6 + 5;

int a[N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ret = 0;
	for(int i = 1; i <= n; i++) ret ^= a[i];
	printf("%d ", ret);
	int cnt = 0;
	for(int i = 1; i < m; i++) {
		int old = cnt;
		int j = i; while(!(j & 1)) j >>= 1, cnt++;
		if(old != cnt)
			for(j = 0; j <= n; j += (1 << old)) if(j % (1 << cnt)) ret ^= a[j];
		printf("%d ", ret);
	}
	return 0;
}