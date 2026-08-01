#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1000 + 5;

int n;

bool isprm[N];
std::vector<int> prime;
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) if(isprm[i]) {
		prime.push_back(i);
		for(int j = i + i; j <= mx; j += i) isprm[j] = false;
	}
}

LL f[N][N];

int main() {
	scanf("%d", &n);
	sieve(n);
	f[0][0] = 1;
	for(int i = 1; i <= (int)prime.size(); i++) {
		for(int j = 0; j <= n; j++) {
			int p = 1;
			f[i][j] = f[i - 1][j];
			while(true) {
				if((long long)p * prime[i - 1] > n) break;
				p *= prime[i - 1];
				if(j >= p) f[i][j] += f[i - 1][j - p];
				else break;
			}
		}
		// for(int j = 0; j <= n; j++) printf("f[%d][%d] =z %d\n", prime[i - 1], j, f[i][j]);
	}
	LL ans = 0;
	for(int i = 0; i <= n; i++) ans += f[(int)prime.size()][i];
	printf("%lld\n", ans);
	return 0;
}