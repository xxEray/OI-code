#include <map>
const int N = 1e5 + 5; // string length
struct SAM {
	struct State { int len, link; std::map<int, int> next; } t[N << 1];
	int tot, last;
	SAM() : tot(1), last(0) { t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
	void init() { tot = 1, last = 0, t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
	void insert(int c) {
		int cur = tot++, p = last;
		t[cur].len = t[last].len + 1, t[cur].next.clear();
		last = cur;
		for(; ~p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
		if(p == -1) t[cur].link = 0;
		else {
			int q = t[p].next[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = tot++;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link, t[q].link = clone;
				t[clone].next = t[q].next;
				t[cur].link = clone;
				for(; ~p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
			}
		}
	}
};