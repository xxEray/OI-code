#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

typedef long long LL;

const LL MOD = 1e9 + 7;

char s[500005];
int n, m;
namespace BaoLi {
	const int N = 1000 + 5;
	
	int a[N];
	
	int divv[N][N];
	LL f[N][N][2];
	
	void main() {
		for(int i = 1; i <= n; i++) a[i] = s[i] - '0';
		for(int i = 1; i <= n; i++)
			for(int j = i; j <= n; j++)
				divv[i][j] = (divv[i][j - 1] * 10 + a[j]) % m;
		f[1][1][1] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = i; j <= n; j++) {
				if(divv[i][j] == 0) (f[j + 1][j + 1][1] += f[i][j][0] + f[i][j][1]) %= MOD;
				else (f[j + 1][j + 1][0] += f[i][j][1]) %= MOD;
				(f[i][j + 1][0] += f[i][j][0]) %= MOD;
				(f[i][j + 1][1] += f[i][j][1]) %= MOD;
			}
//		for(int i = 1; i <= n + 1; i++)
//			for(int j = i; j <= n + 1; j++)
//				printf("f[%d][%d] = {%lld, %lld}, div = %d\n", i, j, f[i][j][0], f[i][j][1], divv[i][j]);
		printf("%lld\n", (f[n + 1][n + 1][0] + f[n + 1][n + 1][1]) % MOD);
	}
}

namespace LuanGao {
	const int N = 1e6 + 5;
	int a[N];
	LL f[N], pref[N];
	std::map<LL, LL> mp;
	void main() {
		for(int i = 1; i <= n; i++) a[i] = s[i] - '0';
		LL power = 1;
		for(int i = n; i >= 1; i--) (a[i] *= power) %= MOD, (power *= 10) %= MOD;
		for(int i = 1; i <= n; i++) {
			if(mp.find(a[i]) != mp.end()) f[i] = 1;
			(f[i] += mp[a[i]]) %= MOD;
			pref[i] = pref[i - 1] + f[i];
			mp[a[i]] += pref[i - 1];
		}
		printf("%lld\n", pref[n]);
	}
}

int main() {
#ifndef DEBUG
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
#endif
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	if(n <= 1000) BaoLi::main();
	else LuanGao::main();
	return 0;
} /*
0145217 7
*/
