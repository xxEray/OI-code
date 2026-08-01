#include <cstdio>
#include <algorithm>

const int N = 20;
const int INF = 0x3f3f3f3f;

int a[N + 5];
int n;

int f[(1 << N) + 5];
int three[N + 5];

int size(int s) {
	int cnt = 0;
	while(s) cnt++, s &= s - 1;
	return cnt;
}

int sum(int s) {
	int ret = 0;
	for(int i = 0; i < n; i++)
		if((s & (1 << i)) == 0)
			ret += a[n - i];
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int U = (1 << n) - 1;
	for(int i = 0; i <= U; i++) f[i] = INF;
	for(int i = 0; i < n; i++)
		three[i] = (1 << i) | (1 << ((i + 1) % n)) | (1 << ((i + 2) % n));
	f[0] = 0;
	for(int s = 1; s <= U; s++)
		for(int i = 0; i < n; i++) {
			int t = three[i];
			f[s] = std::min(f[s], f[(s ^ t) & s] + sum(s));
		}
	printf("%d\n", f[U]);
	return 0;
} /*
7
4 2 2 1 4 1 3 
*/