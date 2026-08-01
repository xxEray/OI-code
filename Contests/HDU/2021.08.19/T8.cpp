#include <cstdio>
#include <algorithm>
#include <bitset>

const int N = 2e5 + 5;

int n, Q;
char s[N];

int nxtl[N], nxtr[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s", &n, &Q, s + 1);
		for(int i = 2, j = 0; i <= n; i++) {
			while(j && s[j + 1] != s[i]) j = nxtl[j];
			if(s[j + 1] == s[i]) j++;
			nxtl[i] = j;
		}
		nxtr[n] = n + 1;
		for(int i = n - 1, j = n + 1; i >= 1; i--) {
			while(j <= n && s[j - 1] != s[i]) j = nxtr[j];
			if(s[j - 1] == s[i]) j--;
			nxtr[i] = j;
		}
		for(int i = 1; i <= n; i++) printf("nxt[%d] = %d, %d\n", i, nxtl[i], nxtr[i]);
		while(Q--) {

		}
	}
	return 0;
}