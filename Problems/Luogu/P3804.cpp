#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 5;
const int CS = 26; // CharSet

char s[N];
int n;

struct Edge { int to, nxt; } edge[N << 2];
int head[N << 1];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}; head[u] = k++; }

int cnt[N << 1];
struct SAM {
	struct State { int len, link, next[CS]; } t[N << 1];
	int sz, last;
	SAM() : sz(1), last(0) { t[0].link = -1; }
	void insert(int c) {
		int cur = sz++, p = last;
		t[cur].len = t[last].len + 1, cnt[cur] = 1;
		for(; ~p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
		if(p == -1) t[cur].link = 0;
		else {
			int q = t[p].next[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = sz++;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link;
				for(int i = 0; i < 26; i++) t[clone].next[i] = t[q].next[i];
				for(; ~p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
				t[q].link = t[cur].link = clone;
			}
		}
		last = cur;
	}
} sam;

long long ans = 0;
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) dfs(edge[i].to), cnt[u] += cnt[edge[i].to];
	if(cnt[u] > 1) ans = std::max(ans, (long long)cnt[u] * sam.t[u].len);
}

int main() {
	// freopen("P3804_2.in", "r", stdin);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) sam.insert(s[i] - 'a');
	for(int i = 1; i < sam.sz; i++) add_edge(sam.t[i].link, i);
	dfs(0);
	printf("%lld\n", ans);
	return 0;
}