#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
LL m, cpm;
char s0[3], s[N], tmp[N];

std::set<int> st[3];
int next(int i, char c) {
	assert(!st[c].empty());
	auto it = st[c].lower_bound(i);
	if(it != st[c].end()) return *it;
	else return *st[c].begin();
}

int main() {
#ifndef DEBUG
	freopen("botbox.in", "r", stdin);
	freopen("botbox.out", "w", stdout);
#endif
	scanf("%d%lld%1s%s", &n, &m, s0, s);
	n--, cpm = m;
	for(int i = 0; i < n; i++) s[i] -= 'A';
	s0[0] -= 'A';
	int exist[3] = {};
	for(int i = 0; i < n; i++) exist[s[i]]++;
	exist[s0[0]]++;
	if(!exist[0] || !exist[1] || !exist[2]) {
		if(exist[(s0[0] + 2) % 3]) {
			for(int i = 0; i < n; i++) {
				m--;
				if((s[i] + 1) % 3 == s0[0]) {
					std::swap(s[i], s0[0]);
					break;
				}
			}
		}
	} else {
		int diff = 0; int cntAB = 0;
		for(int i = 0; i < n; i++) diff += (s[i] != s[(i + 1) % n]), cntAB += (s[i] == 0 && s[(i + 1) % n] == 1);
		for(int i = 0; i < n; i++) st[s[i]].insert(i);
		int now = 0;
		// printf("diff = %d, cntAB = %d\n", diff, cntAB);
		while(!(exist[s0[0]] == 1 && diff == 2) && !(diff == 3 && !cntAB)) {
			int nxt = next(now, (s0[0] + 2) % 3);
			int d = (nxt - now + 1 + n) % n;
			if(m < d) break;
			// printf("s[%d] => %d (now = %d)\n", nxt, s0[0], now);
			int t = s[nxt];
			diff -= (s[(nxt - 1 + n) % n] != s[nxt]) + (s[nxt] != s[(nxt + 1) % n]);
			cntAB -= (s[(nxt - 1 + n) % n] == 0 && s[nxt] == 1) + (s[nxt] == 0 && s[(nxt + 1) % n] == 1);
			st[s[nxt]].erase(nxt);
			s[nxt] = s0[0];
			diff += (s[(nxt - 1 + n) % n] != s[nxt]) + (s[nxt] != s[(nxt + 1) % n]);
			cntAB += (s[(nxt - 1 + n) % n] == 0 && s[nxt] == 1) + (s[nxt] == 0 && s[(nxt + 1) % n] == 1);
			st[s[nxt]].insert(nxt);
			s0[0] = t;
			m -= d, now = (nxt + 1) % n;
		}
		if((exist[s0[0]] == 1 && diff == 2) || (diff == 3 && !cntAB)) {
			while(m % (n + 1)) {
				if((s[now] + 1) % 3 == s0[0]) std::swap(s[now], s0[0]);
				m--, now = (now + 1) % n;
			}
			m /= n + 1;
			for(int i = 0; i < n; i++) tmp[i] = s[((i - m) % n + n) % n];
			for(int i = 0; i < n; i++) s[i] = tmp[i];
		} else {
			while(m) {
				if((s[now] + 1) % 3 == s0[0]) std::swap(s[now], s0[0]);
				m--, now = (now + 1) % n;
			}
		}
		// printf("s: "); for(int i = 0; i < n; i++) putchar(s[i] + 'A'); puts("");
	}
	putchar(s0[0] + 'A');
	for(int i = cpm % n; i < n; i++) putchar(s[i] + 'A');
	for(int i = 0; i < cpm % n; i++) putchar(s[i] + 'A');
	return 0;
}