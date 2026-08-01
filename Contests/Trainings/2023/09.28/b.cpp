#include <bits/stdc++.h>

const int N = 5000 + 5;

int n;
char s[N], t[N];

int pres[N], pret[N];
int sl[N], sr[N], tl[N], tr[N];
int csl, csr, ctl, ctr;

int main() {
#ifndef DEBUG
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		csl = ctl = csr = ctr = 0;
		scanf("%s%s", s + 1, t + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) pres[i] = pres[i - 1] + (s[i] == '1'), pret[i] = pret[i - 1] + (t[i] == '1');
		sr[0] = tr[0] = n + 1;
		for(int i = 1; i <= n; i++) if(s[i] == '0') sl[++csl] = i;
		for(int i = n; i >= 1; i--) if(s[i] == '2') sr[++csr] = i;
		for(int i = 1; i <= n; i++) if(t[i] == '0') tl[++ctl] = i;
		for(int i = n; i >= 1; i--) if(t[i] == '2') tr[++ctr] = i;
		int ans = 0;
		for(int i = 0; i <= std::min(csl, ctl); i++)
			for(int j = 0; j <= std::min(csr, ctr); j++) {
				if(sl[i] >= sr[j] || tl[i] >= tr[j]) break;
				ans = std::max(ans, std::min(pres[sr[j] - 1] - pres[sl[i]], pret[tr[j] - 1] - pret[tl[i]]) + i + j);
			}
		printf("%d\n", ans);
	}
	return 0;
}