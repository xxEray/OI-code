#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

int n, m, Q;
char s[N], t[N];

int cnts[N], cntt[N];
int lasts[N], lastt[N];

int main() {
#ifndef DEBUG
	freopen("always.in", "r", stdin);
	freopen("always.out", "w", stdout);
#endif
	scanf("%s%s%d", s + 1, t + 1, &Q);
	n = strlen(s + 1), m = strlen(t + 1);
	for(int i = 1; i <= n; i++) s[i] = (s[i] == 'A' ? 0 : 1);
	for(int i = 1; i <= m; i++) t[i] = (t[i] == 'A' ? 0 : 1);
	for(int i = 1; i <= n; i++) cnts[i] = cnts[i - 1] + (s[i] == 1);
	for(int i = 1; i <= m; i++) cntt[i] = cntt[i - 1] + (t[i] == 1);
	for(int i = 1; i <= n; i++) lasts[i] = (s[i] == 1 ? 0 : lasts[i - 1] + 1);
	for(int i = 1; i <= m; i++) lastt[i] = (t[i] == 1 ? 0 : lastt[i - 1] + 1);
	for(int _ = 1; Q--; _++) {
		int ls, rs, lt, rt;
		scanf("%d%d%d%d", &ls, &rs, &lt, &rt);
		int cs = std::min(rs - ls + 1, lasts[rs]), ct = std::min(rt - lt + 1, lastt[rt]);
		int cut = std::min(cs, ct);
		rs -= cut, rt -= cut, cs -= cut, ct -= cut;
		int cns = cnts[rs] - cnts[ls - 1], cnt = cntt[rt] - cntt[lt - 1];
		if(cs < ct) putchar('0');
		else if(cs == ct) {
			// cs = ct = 0
			if(cns == 0) putchar(cnt == 0 ? '1' : '0');
			else putchar(cns <= cnt && (cns & 1) == (cnt & 1) ? '1' : '0');
		} else {
			// cs > 0, ct = 0
			if(cns == 0 && cnt == 0) { putchar(cs % 3 == 0 ? '1' : '0'); continue; }
			if(cs % 3 == 0 && cns) cs = 0;
			else cns += 2, cs--;
			putchar(cns <= cnt && (cns & 1) == (cnt & 1) ? '1' : '0');
		}
	}
	puts("");
	return 0;
}
