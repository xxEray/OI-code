#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e7 + 5;
const int CS = 5;

char s[N], t[N];
int n, m, Q;

inline int id(char c) { return c == 'N' ? 0 : (c == 'E' ? 1 : (c == 'W' ? 2 : 3)); }

struct SAM {
	struct State { int link, len, next[CS]; } t[N << 1];
	int last, sz;
	SAM() : last(0), sz(1) { t[0].link = -1; }
	void insert(int c) {
		int cur = sz++, p = last;
		t[cur].len = t[last].len + 1;
		for(; ~p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
		if(p == -1) t[cur].link = 0;
		else {
			int q = t[p].next[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = sz++;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link;
				for(int i = 0; i < CS; i++) t[clone].next[i] = t[q].next[i];
				for(; ~p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
				t[q].link = t[cur].link = clone;
			}
		}
		last = cur;
	}
} sam;

int main() {
	scanf("%d%d", &n, &Q);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++) sam.insert(id(s[i]));
	while(Q--) {
		scanf("%s", t + 1);
		m = strlen(t + 1);
		int now = 0, ans = 0;
		for(int i = 1; i <= m; i++)
			if(sam.t[now].next[id(t[i])]) ans++, now = sam.t[now].next[id(t[i])];
			else break;
		printf("%d\n", ans);
	}
	return 0;
}