#include <cstdio>
#include <algorithm>
#include <cstring>
#include <assert.h>

typedef long long LL;

const int N = 1e6 + 5;

char s[N], t[N];
int n, m;

LL r[N], l[N];

LL mp[100][100];

int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	for(int i = 1; i <= n; i++) l[i] = m + 1;
	for(int i = 1, j = 0; i <= n; i++) {
		while(j < m && s[i] != t[j + 1]) j++;
		if(j < m && s[i] == t[j + 1]) j++;
		r[i] = j;
	}
	for(int i = 1, j = 0; i <= m; i++) {
		int lastj = j;
		while(j < n && t[i] != s[j + 1]) j++;
		if(j < n && t[i] == s[j + 1]) j++;
		for(int k = lastj + 1; k <= j; k++) l[k] = i;
	}
	// for(int i = 1; i <= n; i++) printf("s[1 .. %d]: t[1 .. %lld~%lld]\n", i, l[i], r[i]);
	LL ans = 0;
	int jl = 0, jr = 0;
	for(int i = 1; i <= n; i++) {
		while(jl < l[i]) {
			if(jl > 1 && t[jl - 1] != t[jl]) mp[t[jl - 1]][t[jl]]--;
			jl++;
		}
		while(jr < r[i]) {
			jr++;
			if(jr > 1 && t[jr - 1] != t[jr]) mp[t[jr - 1]][t[jr]]++;
		}
		ans += r[i] - l[i] + 1;
		if(i > 1 && s[i - 1] != s[i]) ans -= mp[s[i]][s[i - 1]];
	}
	printf("%lld\n", ans);
	return 0;
} /*
GRGR
RGRG

*/