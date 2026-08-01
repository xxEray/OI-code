#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 500 + 5;

const int PLUS = 1;

LL a[N][N];
int n;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return a == 0 || b == 0 ? a ^ b : a / gcd(a, b) * b; }
LL llcm(LL a, LL b, LL c, LL d) { return lcm(lcm(a, b), lcm(c, d)); }

bool isprm[10005];
std::vector<int> prime;
void sieve() {
	for(int i = 2; i <= 10000; i++) isprm[i] = true;
	for(int i = 2; i <= 10000; i++) {
		if(!isprm[i]) continue;
		prime.push_back(i);
		for(int j = i + i; j <= 10000; j += i) isprm[j] = false;
	}
}

int main() {
	// freopen("B.out", "w", stdout);
	sieve();
	scanf("%d", &n);
	if(n == 2) { puts("4 7\n23 10"); return 0; }
	int p = 0, q = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if((i & 1) + (j & 1) == 1)
				a[i][j] = prime[(i + j - 1) / 2], p = std::max(p, (i + j - 1) / 2 + 1), q = std::min(q, (i - j - 1) / 2);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if((i & 1) + (j & 1) == 1) a[i][j] *= prime[p + -q + (i - j - 1) / 2];
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= n; j++)
	// 		printf("%lld%c", a[i][j], j == n ? '\n' : ' ');
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(!a[i][j])
				a[i][j] = llcm(a[i - 1][j], a[i + 1][j], a[i][j - 1], a[i][j + 1]) + PLUS;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%lld%c", a[i][j], j == n ? '\n' : ' ');
	return 0;
}