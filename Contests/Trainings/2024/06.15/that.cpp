#include <bits/stdc++.h>

#define CLEAR(arr) memset((arr), 0, sizeof((arr)))

typedef unsigned long long ull;

const int N = 2e4 + 5;
const ull HSH = 809;

int n, K;
char s[N];

struct SAM {
	int link[N << 1], len[N << 1];
	std::map<char, int> nxt[N << 1];
	int last, tot;
	void init() {
		for(int i = 0; i <= tot; i++) nxt[i].clear(), link[i] = len[i] = 0;
		last = tot = 0, link[0] = -1;
	}
	void insert(char c) {
		int cur = ++tot, p = last;
		len[cur] = len[p] + 1, last = cur;
		for(; ~p && !nxt[p][c]; p = link[p]) nxt[p][c] = cur;
		if(p == -1) link[cur] = 0;
		else {
			int q = nxt[p][c];
			if(len[q] == len[p] + 1) link[cur] = q;
			else {
				int clone = ++tot;
				len[clone] = len[p] + 1;
				link[clone] = link[q], link[q] = clone, link[cur] = clone;
				nxt[clone] = nxt[q];
				for(; ~p && nxt[p][c] == q; p = link[p]) nxt[p][c] = clone;
			}
		}
	}
} sam;

struct TreapNode { int ls, rs, v, w, sz, sum; };
struct Treap {
	TreapNode t[N * 20];
	int tot;
	std::vector<int> stk;
	void init() { tot = 0, stk.clear(); }
	int nw(int v) {
		int id;
		if(stk.empty()) id = ++tot;
		else id = stk.back(), stk.pop_back();
		t[id].ls = t[id].rs = 0, t[id].v = v, t[id].sz = 1, t[id].sum = v, t[id].w = rand();
		return id;
	}
	void recycle(int id) { stk.emplace_back(id); }
	void pushup(int x) {
		t[x].sz = t[t[x].ls].sz + t[t[x].rs].sz + 1;
		t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum + t[x].v;
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(t[x].w > t[y].w) { t[x].rs = merge(t[x].rs, y), pushup(x); return x; }
		else { t[y].ls = merge(x, t[y].ls), pushup(y); return y; }
	}
	void split(int rt, int v, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(t[rt].v <= v) x = rt, split(t[rt].rs, v, t[x].rs, y), pushup(x);
		else y = rt, split(t[rt].ls, v, x, t[y].ls), pushup(y);
	}
	void insert(int &rt, int v) {
		int x, y;
		split(rt, v, x, y);
		rt = merge(x, merge(nw(v), y));
	}
	void remove(int &rt, int v) {
		int x, y, z;
		split(rt, v - 1, x, y), split(y, v, y, z);
		if(y) recycle(y), y = merge(t[y].ls, t[y].rs);
		rt = merge(x, merge(y, z));
	}
	std::pair<int, int> query(int &rt, int v) {
		int x, y;
		split(rt, v, x, y);
		std::pair<int, int> ret(t[x].sz, t[x].sum);
		rt = merge(x, y);
		return ret;
	}
	void free(int &rt) {
		if(!rt) return;
		free(t[rt].ls), free(t[rt].rs);
		recycle(rt);
		rt = 0;
	}
} treap;

std::vector<int> son[N << 1];
std::set<int> st[N << 1];

int ansl, ansr;

int mp[305];
ull power[N], hsh[N];
ull hash(int l, int r) { return hsh[r] - hsh[l - 1] * power[r - l + 1]; }
bool compare(int i, int j, int len) {
	int l = 0, r = len - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(hash(i, i + mid) == hash(j, j + mid)) l = mid + 1;
		else r = mid;
	}
	if(l >= len) return false;
	else return s[i + l] < s[j + l];
}

int dfs(int u) {
	int uid = 0;
	for(int v : son[u]) {
		int vid = dfs(v);
		if(st[v].size() > st[u].size()) st[u].swap(st[v]), std::swap(uid, vid);
		for(int x : st[v]) {
			if(st[u].count(x)) continue;
			auto ir = st[u].lower_bound(x);
			if(ir != st[u].begin() && ir != st[u].end()) {
				auto il = std::prev(ir);
				treap.remove(uid, *ir - *il);
			}
			if(ir != st[u].end()) treap.insert(uid, *ir - x);
			if(ir != st[u].begin()) {
				auto il = std::prev(ir);
				treap.insert(uid, x - *il);
			}
			st[u].emplace(x);
		}
		st[v].clear();
		treap.free(vid);
	}
	if(u) {
		// printf("endpos[%d]: ", u); for(int x : st[u]) printf("%d ", x); puts("");
		int sz = st[u].size();
		int l = sam.len[sam.link[u]] + 1, r = sam.len[u];
		while(l < r) {
			int mid = (l + r) >> 1;
			auto pr = treap.query(uid, mid);
			if((sz - pr.first) * mid + pr.second >= K) r = mid;
			else l = mid + 1;
		}
		auto pr = treap.query(uid, l);
		if((sz - pr.first) * l + pr.second == K) {
			int nr = *st[u].begin(), nl = nr - l + 1;
			// printf("nl = %d, nr = %d\n", nl, nr);
			if(ansl == -1 || ansr - ansl > nr - nl) ansl = nl, ansr = nr;
			else if(ansr - ansl == nr - nl && compare(nl, ansl, nr - nl + 1)) ansl = nl, ansr = nr;
		}
	}
	return uid;
}

int main() {
#ifndef DEBUG
	freopen("that.in", "r", stdin);
	freopen("that.out", "w", stdout);
#endif
	for(int i = 1; i <= 300; i++) mp[i] = i;
	power[0] = 1;
	for(int i = 1; i <= 20000; i++) power[i] = power[i - 1] * HSH;
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s%d", s + 1, &K);
		n = strlen(s + 1);
		std::random_shuffle(mp + 1, mp + 300 + 1);
		hsh[0] = 0;
		for(int i = 1; i <= n; i++) hsh[i] = hsh[i - 1] * HSH + mp[(int)s[i]];
		sam.init();
		for(int i = 1; i <= n; i++) sam.insert(s[i]);
		// for(int i = 1; i <= sam.tot; i++) printf("%d: link=%d, len=%d\n", i, sam.link[i], sam.len[i]);
		treap.init();
		for(int i = 0; i <= sam.tot; i++) st[i].clear(), son[i].clear();
		for(int i = 1; i <= sam.tot; i++) son[sam.link[i]].emplace_back(i);
		int now = 0;
		for(int i = 1; i <= n; i++) now = sam.nxt[now][s[i]], st[now].emplace(i);
		ansl = ansr = -1;
		dfs(0);
		if(ansl == -1) puts("NOTFOUND!");
		else {
			for(int i = ansl; i <= ansr; i++) putchar(s[i]);
			puts("");
		}
	}
	return 0;
} /*
1
cdddd
5
*/