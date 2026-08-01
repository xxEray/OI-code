#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

char s[N];
int n;

LL f[N];
int last[300];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) f[i] = 1;
	LL ret = 0;
	for(int i = 2; i <= n + 2; i++) {
		(f[i] += ret) %= MOD;
		(ret += f[i - 1]) %= MOD;
		if(last[(int)s[i - 1]]) (ret += MOD - f[last[(int)s[i - 1]]]) %= MOD;
		last[(int)s[i - 1]] = i - 1;
	}
	printf("%lld\n", f[n + 2]);
	return 0;
} /*
abc
*/