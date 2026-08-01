#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
char s[N];

bool ok1[N], ok2[N];

void solve(bool *ok) {
	int cntp = (s[1] == 'P'), cntn = (s[1] == 'N');
	int cnt = (s[1] == 'K');
	bool hasn = (s[1] == 'N');
	if(s[2] == 'P') ok[2] &= (s[1] == 'K');
	for(int i = 2; i <= n - 1; i++) {
		cntp += (s[i] == 'P'), cntn += (s[i] == 'N');
		if(s[i] == 'N') hasn = true;
		else if(s[i] == 'K') { if(cnt == 0) cnt += hasn, hasn = false; }
		if(s[i + 1] == 'P') ok[i + 1] &= (cnt == 1 && (s[i] == 'K' || hasn) && (!cntp || cntn));
	}
}

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		for(int i = 1; i <= n; i++) ok1[i] = ok2[i] = true;
		solve(ok1);
		for(int i = 1; i <= n; i++) s[i] = (s[i] == 'N' ? 'P' : (s[i] == 'P' ? 'K' : 'N'));
		solve(ok1);
		for(int i = 1; i <= n; i++) s[i] = (s[i] == 'N' ? 'P' : (s[i] == 'P' ? 'K' : 'N'));
		solve(ok1);
		for(int i = 1; i <= n; i++) s[i] = (s[i] == 'N' ? 'P' : (s[i] == 'P' ? 'K' : 'N'));
		std::reverse(s + 1, s + n + 1);
		solve(ok2);
		for(int i = 1; i <= n; i++) s[i] = (s[i] == 'N' ? 'P' : (s[i] == 'P' ? 'K' : 'N'));
		solve(ok2);
		for(int i = 1; i <= n; i++) s[i] = (s[i] == 'N' ? 'P' : (s[i] == 'P' ? 'K' : 'N'));
		solve(ok2);
		for(int i = 1; i <= n; i++) putchar(ok1[i] && ok2[n - i + 1] ? '1' : '0');
		puts("");
	}
	return 0;
} /*
3
2
PP
3
NKP
6
PPKNPK
*/