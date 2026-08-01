const int N = 1e6 + 5; // string length
const int CHARSET = 'z'; // 最大字符
int sa[N << 1], rk[N << 1], tot[N], tp[N], ht[N];
void init_SA(char *s, int n) { // s: 1-indexed
	int m = CHARSET;
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
		for(int j = 2; j <= n; j++) rk[sa[j]] = ((tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i]) ? p : ++p);
	}
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) { ht[rk[i]] = 0; continue; }
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}