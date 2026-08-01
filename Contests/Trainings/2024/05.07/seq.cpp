#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, Q;
int a[N];

struct SegNode {
	std::vector<std::pair<int, int>> seq;
	int optimal;
	SegNode() : seq(), optimal(0) {}
};
int calcall(std::vector<std::pair<int, int>> seq) {
	// printf("calcall  [");
	// for(auto v : seq) printf("%dx%d ", v.first, v.second);
	// printf("]\n");
	int ret = 0;
	while(!seq.empty()) {
		int sz = seq.size();
		int mnpos = -1;
		for(int i = 0; i <= sz - 1; i++)
			if(seq[i].second && (mnpos == -1 || seq[mnpos].second > seq[i].second)) mnpos = i;
		if(mnpos == -1) break;
		if(seq[mnpos].first == 1) {
			ret = std::max(ret, seq[mnpos].second);
			if(mnpos > 0 && mnpos < sz - 1 && seq[mnpos - 1].second == seq[mnpos + 1].second && seq[mnpos + 1].second == 0)
				seq.erase(seq.begin() + mnpos), sz--;
			else if(mnpos > 0 && seq[mnpos - 1].second == 0) seq.erase(seq.begin() + mnpos), sz--;
			else if(mnpos < sz - 1 && seq[mnpos + 1].second == 0) seq.erase(seq.begin() + mnpos), sz--;
			else seq[mnpos] = {0, 0};
		} else if(seq[mnpos].first & 1) {
			std::pair<int, int> v(seq[mnpos].first >> 1, seq[mnpos].second + 1);
			seq[mnpos] = {0, 0};
			int cnt = 0;
			if(mnpos > 0 && seq[mnpos - 1].second) {
				cnt++;
				if(seq[mnpos - 1].second == v.second) seq[mnpos - 1].first += v.first;
				else seq.insert(seq.begin() + mnpos, v), mnpos++, sz++;
			}
			if(mnpos < sz - 1 && seq[mnpos + 1].second) {
				cnt++;
				if(seq[mnpos + 1].second == v.second) seq[mnpos + 1].first += v.first;
				else seq.insert(seq.begin() + mnpos + 1, v), sz++;
			}
			if(cnt == 0) seq[mnpos] = v;
			else if(mnpos > 0 && seq[mnpos - 1].second == 0) seq.erase(seq.begin() + mnpos);
			else if(mnpos < sz - 1 && seq[mnpos + 1].second == 0) seq.erase(seq.begin() + mnpos);
		} else {
			seq[mnpos] = {seq[mnpos].first >> 1, seq[mnpos].second + 1};
			if(mnpos > 0 && seq[mnpos - 1].second == seq[mnpos].second)
				seq[mnpos - 1].first += seq[mnpos].first, seq.erase(seq.begin() + mnpos), mnpos--, sz--;
			if(mnpos < sz - 1 && seq[mnpos + 1].second == seq[mnpos].second)
				seq[mnpos + 1].first += seq[mnpos].first, seq.erase(seq.begin() + mnpos), sz--;
		}
		// printf("    =>  [");
		// for(auto v : seq) printf("%dx%d ", v.first, v.second);
		// printf("]\n");
	}
	return ret;
}
SegNode calc(SegNode x, SegNode y) {
	// printf("calc  %d,[", x.optimal);
	// for(auto v : x.seq) printf("%dx%d ", v.first, v.second);
	// printf("]  %d,[", y.optimal);
	// for(auto v : y.seq) printf("%dx%d ", v.first, v.second);
	// printf("]  =  ");
	SegNode z;
	z.optimal = std::max(x.optimal, y.optimal);
	if(!x.seq.empty() && !y.seq.empty() && x.seq.back().second == y.seq.front().second)
		y.seq.front().first += x.seq.back().first, x.seq.pop_back();
	z.seq = x.seq, z.seq.insert(z.seq.end(), y.seq.begin(), y.seq.end());
	auto &seq = z.seq;
	while(true) {
		int sz = seq.size();
		int zl = 0, zr = sz - 1;
		while(zl < sz - 1 && seq[zl].second < seq[zl + 1].second) zl++;
		while(zr > 0 && seq[zr].second < seq[zr - 1].second) zr--;
		if(zl >= zr) break;
		int mnpos = -1;
		for(int i = zl + 1; i <= zr - 1; i++)
			if(seq[i].second && (mnpos == -1 || seq[mnpos].second > seq[i].second)) mnpos = i;
		if(mnpos == -1) break;
		if(seq[mnpos].first == 1) {
			z.optimal = std::max(z.optimal, seq[mnpos].second);
			if(mnpos > 0 && mnpos < sz - 1 && seq[mnpos - 1].second == seq[mnpos + 1].second && seq[mnpos + 1].second == 0)
				seq.erase(seq.begin() + mnpos), seq.erase(seq.begin() + mnpos), sz -= 2;
			else if(mnpos > 0 && seq[mnpos - 1].second == 0) seq.erase(seq.begin() + mnpos), sz--;
			else if(mnpos < sz - 1 && seq[mnpos + 1].second == 0) seq.erase(seq.begin() + mnpos), sz--;
			else seq[mnpos] = {0, 0};
		} else if(seq[mnpos].first & 1) {
			std::pair<int, int> v(seq[mnpos].first >> 1, seq[mnpos].second + 1);
			seq[mnpos] = {0, 0};
			int cnt = 0;
			if(mnpos > 0 && seq[mnpos - 1].second) {
				cnt++;
				if(seq[mnpos - 1].second == v.second) seq[mnpos - 1].first += v.first;
				else seq.insert(seq.begin() + mnpos, v), mnpos++, sz++;
			}
			if(mnpos < sz - 1 && seq[mnpos + 1].second) {
				cnt++;
				if(seq[mnpos + 1].second == v.second) seq[mnpos + 1].first += v.first;
				else seq.insert(seq.begin() + mnpos + 1, v), sz++;
			}
			if(cnt == 0) seq[mnpos] = v;
			else if(mnpos > 0 && seq[mnpos - 1].second == 0) seq.erase(seq.begin() + mnpos);
			else if(mnpos < sz - 1 && seq[mnpos + 1].second == 0) seq.erase(seq.begin() + mnpos);
		} else {
			seq[mnpos] = {seq[mnpos].first >> 1, seq[mnpos].second + 1};
			if(mnpos > 0 && seq[mnpos - 1].second == seq[mnpos].second)
				seq[mnpos - 1].first += seq[mnpos].first, seq.erase(seq.begin() + mnpos), mnpos--, sz--;
			if(mnpos < sz - 1 && seq[mnpos + 1].second == seq[mnpos].second)
				seq[mnpos + 1].first += seq[mnpos].first, seq.erase(seq.begin() + mnpos), sz--;
		}
	}
	// printf("%d,[", z.optimal);
	// for(auto v : z.seq) printf("%dx%d ", v.first, v.second);
	// printf("]\n");
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int mx;
	void build() {
		for(mx = 1; mx <= n; mx <<= 1);
		for(int i = 1; i <= n; i++) t[mx + i].seq = {{1, a[i]}}, t[mx + i].optimal = a[i];
		for(int i = mx; i >= 1; i--) t[i] = calc(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int x, int val) {
		x += mx, t[x].seq = {{1, val}}, t[x].optimal = val;
		for(x >>= 1; x; x >>= 1) t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	int query(int l, int r) const {
		SegNode retl, retr;
		for(l += mx - 1, r += mx + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) {
				retl = calc(retl, t[l ^ 1]);
				// printf("L %d,[", t[l ^ 1].optimal);
				// for(auto v : t[l ^ 1].seq) printf("%dx%d ", v.first, v.second);
				// printf("]\n");
			}
			if(r & 1) {
				retr = calc(t[r ^ 1], retr);
				// printf("R %d,[", t[r ^ 1].optimal);
				// for(auto v : t[r ^ 1].seq) printf("%dx%d ", v.first, v.second);
				// printf("]\n");
			}
		}
		auto res = calc(retl, retr);
		return std::max(res.optimal, calcall(res.seq));
	}
} seg;

int main() {
// #ifndef DEBUG
	// freopen("in.txt", "r", stdin);
	// freopen("seq.out", "w", stdout);
// #endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	seg.build();
	// int cnt = 0;
	scanf("%d", &Q);
	while(Q--) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1) {
			// if(++cnt == 12617) {
			// 	for(int i = 1; i <= n; i++) fprintf(stderr, "%d ", a[i]);
			// 	fprintf(stderr, "\n%d %d\n", x, y);
			// }
			printf("%d\n", seg.query(x, y));
		} else seg.modify(x, y), a[x] = y;
	}
	return 0;
} /*
9
5 4 10 5 5 5 10 10 1
1
1 1 8
*/