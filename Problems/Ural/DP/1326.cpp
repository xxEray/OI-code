#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int S = (1 << 20) + 5;
const int INF = 0x3f3f3f3f;

int a[N];
struct Sells { int price, things; } b[N];
int n, m;
int cntwant, want;

int f[S];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int t, x;
		scanf("%d%d", &b[i].price, &t);
		while(t--) scanf("%d", &x), b[i].things |= (1 << (x - 1));
	}
	scanf("%d", &cntwant);
	for(int i = 1; i <= cntwant; i++) {
		int x;
		scanf("%d", &x);
		want |= (1 << (x - 1));
	}
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++) f[s] = INF;
	f[0] = 0;
	for(int s = 0; s <= U; s++) {
		for(int i = 1; i <= m; i++)
			if((s | b[i].things) != s)
				f[s | b[i].things] = std::min(f[s | b[i].things], f[s] + b[i].price);
		for(int i = 1; i <= n; i++)
			if((s | (1 << (i - 1))) != s)
				f[s | (1 << (i - 1))] = std::min(f[s | (1 << (i - 1))], f[s] + a[i]);
	}
	int ans = INF;
	for(int s = 0; s <= U; s++)
		if((s & want) == want)
			ans = std::min(ans, f[s]);
	printf("%d\n", ans);
	return 0;
}