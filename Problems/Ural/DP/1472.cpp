#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int k[N], c[N], leaf[N];
int n;

int f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) leaf[i] = true;
	for(int i = 2; i <= n; i++) scanf("%d%d", &k[i], &c[i]), leaf[k[i]] = false;
	for(int i = 1; i <= n; i++) if(leaf[i]) f[i] = INF;
	for(int i = n; i >= 1; i--)
		f[k[i]] += std::min(f[i], c[i]);
	printf("%d.00\n", f[1]);
	return 0;
}