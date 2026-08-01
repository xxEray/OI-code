#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;
const LL D = 998244353;

int n;
int a[N], b[N];

int tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) b[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
}

int sa[N << 1], rk[N << 1], tot[N], tp[N], ht[N];
void init_SA(int *s, int len) {
	int m = len;
	for(int i = 0, p = 0; p < len; i = (i ? i << 1 : 1), m = p) {
		if(i) {
			p = 0;
			for(int j = 1; j <= i; j++) tp[++p] = len - i + j;
			for(int j = 1; j <= len; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
		} else for(int j = 1; j <= len; j++) rk[j] = s[j], tp[j] = j;
		for(int j = 0; j <= m; j++) tot[j] = 0;
		for(int j = 1; j <= len; j++) tot[rk[j]]++;
		for(int j = 0; j <= m; j++) tot[j] += tot[j - 1];
		for(int j = len; j >= 1; j--) sa[tot[rk[tp[j]]]--] = tp[j];
		if(!i) continue;
		for(int j = 1; j <= len; j++) tp[j] = rk[j];
		rk[sa[1]] = p = 1;
		for(int j = 2; j <= len; j++) rk[sa[j]] = ((tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i]) ? p : ++p);
	}
	for(int i = 1, k = 0; i <= len; i++) {
		if(rk[i] == 1) { ht[rk[i]] = 0; continue; }
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(i + k <= len && j + k <= len && s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}



int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	discrete();
	init_SA(b, n);
	int mx = 0;
	for(int i = 1; i <= n; i++) mx = std::max(mx, ht[i]);

	return 0;
}