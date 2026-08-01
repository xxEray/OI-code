#include <cstdio>
#include <algorithm>
#include <cstring>
#include <atcoder/modint>

typedef atcoder::modint998244353 mint;

int mask[50];
int n, m;
char tmp[50];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", tmp);
		int len = strlen(tmp);
		for(int j = 0; j < len; j++) mask[i] |= 1 << (tmp[j] - 'a');
	}
	mint ans = 0;
	int U = (1 << n) - 1;
	for(int s = 1; s <= U; s++) {
		int msk = (1 << 26) - 1;
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) msk &= mask[i];
		if(__builtin_popcount(s) & 1) ans += mint(__builtin_popcount(msk)).pow(m);
		else ans -= mint(__builtin_popcount(msk)).pow(m);
	}
	printf("%d\n", ans.val());
	return 0;
}