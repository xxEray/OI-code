#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;
const int CS = 26; // CharSet

char s[N];
int n;

struct SAM {
	struct State { int len, link, next[CS]; } t[N << 1];
	int sz, last;
	SAM() : sz(1), last(0) { t[0].link = -1; }
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
    scanf("%d%s", &n, s + 1);
    for(int i = 1; i <= n; i++) sam.insert(s[i] - 'a');
    long long ans = 0;
    for(int i = 1; i < sam.sz; i++) ans += sam.t[i].len - sam.t[sam.t[i].link].len;
    printf("%lld\n", ans);
	return 0;
}