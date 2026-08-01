#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
char a[N], b[N];

int main() {
	scanf("%d%s%s", &n, a + 1, b + 1);
	int la = n + 1, rb = 0;
	int la2b = n + 1, rb2a = 0;
	for(int i = 1; i <= n; i++) {
		if(b[i] == 'A') la = std::min(la, i);
		if(b[i] == 'B') rb = std::max(rb, i);
		if(a[i] == 'A' && b[i] == 'B') la2b = std::min(la2b, i);
		if(a[i] == 'B' && b[i] == 'A') rb2a = std::max(rb2a, i);
	}
	if(la > la2b || rb < rb2a) { puts("-1"); return 0; }
	int cnt = 0, ans = 0;
	for(int i = 1; i <= n; i++) if(a[i] != b[i]) {
		if(b[i] == 'A') cnt++, ans++;
		else {
			if(cnt) cnt--;
			else ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}