#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 5;

char s[N];
int n, m;

int sa[N << 1], rk[N << 1], tot[N], tp[N];
void calcSA() {
	m = 'z';
	for(int i = 0, p = 0; p < n; i = (i ? i << 1 : 1), m = p) {
		if(i) {
			p = 0;
			for(int j = 1; j <= i; j++) tp[++p] = n - i + j;
			for(int j = 1; j <= n; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
		} else for(int j = 1; j <= n; j++) rk[j] = s[j], tp[j] = j;
		for(int j = 0; j <= m; j++) tot[j] = 0;
		for(int j = 1; j <= n; j++) tot[rk[j]]++;
		for(int j = 0; j <= m; j++) tot[j] += tot[j - 1];
		for(int j = n; j >= 1; j--) sa[tot[rk[tp[j]]]--] = tp[j];
		if(!i) continue;
		for(int j = 1; j <= n; j++) tp[j] = rk[j];
		rk[sa[1]] = p = 1;
		for(int j = 2; j <= n; j++)
			rk[sa[j]] = ((tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i]) ? p : ++p);
		// printf("*****************\n");
		// printf("i  "); for(int i = 1; i <= n; i++) { printf("%d ", i);     } puts("");
		// printf("sa "); for(int i = 1; i <= n; i++) { printf("%d ", sa[i]); } puts("");
		// printf("rk "); for(int i = 1; i <= n; i++) { printf("%d ", rk[i]); } puts("");
		// printf("tp "); for(int i = 1; i <= n; i++) { pri ntf("%d ", tp[i]); } puts("");
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	calcSA();
	for(int i = 1; i <= n; i++) printf("%d ", sa[i]);
	return 0;
}