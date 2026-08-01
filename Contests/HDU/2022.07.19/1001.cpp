#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;
const LL MOD = 998244353;

char s[N];
int n, K;

int nxt[N];
LL f[N];
void get_nxt() {
    nxt[1] = 0;
    for(int i = 2, j = 0; i <= n; i++) {
        while(j && s[j + 1] != s[i]) j = nxt[j];
        if(s[j + 1] == s[i]) j++;
        nxt[i] = j;
    }
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s%d", s + 1, &K);
		n = strlen(s + 1);
		f[1] = 1;
		for(int i = 2; i <= n; i++) f[i] = (f[nxt[i]] + 1) % MOD;
		LL ans = 0;
		for(int i = 1; i <= n; i++) 
		printf("%lld\n", f[n]);
	}
	return 0;
}
