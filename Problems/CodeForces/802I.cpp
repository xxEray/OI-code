#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;
const int CS = 26; // CharSet

char s[N];
int n;

struct Edge { int to, nxt; } edge[N << 2];
int head[N << 1], edgek;
void add_edge(int u, int v) { edge[edgek] = (Edge){v, head[u]}, head[u] = edgek++; }
int cnt[N << 1];

struct SAM {
	struct State { int len, link, next[CS]; } t[N << 1];
	int sz, last;
	SAM() : sz(1), last(0) { t[0] = State(), t[0].link = -1; }
	void insert(int c) {
		int cur = sz++, p = last;
		t[cur].len = t[last].len + 1;
		cnt[cur] = 1;
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

void dfs(int u) { for(int i = head[u]; i; i = edge[i].nxt) dfs(edge[i].to), cnt[u] += cnt[edge[i].to]; }

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		edgek = 1, memset(head, 0, sizeof(head)); // clear Graph
		sam = SAM(), memset(cnt, 0, sizeof(cnt)); // clear SAM
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) sam.insert(s[i] - 'a');
		for(int i = 1; i < sam.sz; i++) add_edge(sam.t[i].link, i);
		dfs(0);
		long long ans = 0;
		for(int i = 1; i < sam.sz; i++) ans += (long long)cnt[i] * cnt[i] * (sam.t[i].len - sam.t[sam.t[i].link].len);
		printf("%lld\n", ans);
	}
	return 0;
}