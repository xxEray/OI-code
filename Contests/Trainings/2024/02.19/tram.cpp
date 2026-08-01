#include <bits/stdc++.h>

typedef std::pair<int, int> Pos;
typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;

bool a[N][2];
std::set<int> st;
Pos pos[N];
struct cmp_pair {
	bool operator()(const std::pair<LL, Pos> &x, const std::pair<LL, Pos> &y) const {
		if(x.first != y.first) return x.first < y.first;
		else return x.second > y.second;
	}
};
std::priority_queue<std::pair<LL, Pos>, std::vector<std::pair<LL, Pos>>, cmp_pair> q;

LL dist(const Pos &x, const Pos &y) { return (LL)(x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second); }
LL dist(const Pos &x, int y) {
	LL base = (LL)(x.first - y) * (x.first - y);
	if(a[y][!x.second] && !a[y][x.second]) return base + 1;
	else if(a[y][x.second]) return base;
	else return LLINF;
}
LL dist(Pos p) {
	if(a[p.first][!p.second]) return 1;
	auto it = st.lower_bound(p.first);
	LL ret = LLINF;
	if(it != st.begin()) ret = std::min(ret, dist(p, *std::prev(it)));
	if(it != st.end()) ret = std::min(ret, dist(p, *it));
	return ret;
}
Pos best(int x, int y) {
	assert(x < y);
	// printf("best(%d, %d)\n", x, y);
	if(y == x + 1) {
		if(!a[x][0]) return {x, 0};
		else if(!a[x][1]) return {x, 1};
		else if(!a[y][0]) return {y, 0};
		else if(!a[y][1]) return {y, 1};
		else return {-1, -1};
	}
	if(y == x + 2 && !a[x][1] && !(!a[x][0] && !a[y][0]) && !(!a[x][1] && !a[y][1])) return {x, 1};
	int r = (x + y) / 2;
	if((x + y) & 1) {
		if(a[x][0] && !a[x][1]) return {r, 1};
		else if(a[x][0] && a[x][1] && !a[y][0]) return {r + 1, 0};
		else if(a[x][0] && a[x][1] && !a[y][1]) return {r + 1, 1};
		else return {r, 0};
	} else {
		if(a[x][0] && a[y][0]) return {r, 1};
		else return {r, 0};
	}
}

int main() {
#ifndef DEBUG
	freopen("tram.in", "r", stdin);
	freopen("tram.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	q.emplace(LLINF, Pos(1, 0));
	for(int qid = 1; qid <= m; qid++) {
		int type;
		scanf("%d", &type);
		// for(int i = 1; i <= n; i++) printf("  [%d %d]\n", a[i][0], a[i][1]);
		// printf("st: "); for(auto x : st) printf("%d ", x); puts("");
		// for(auto q2 = q; !q2.empty(); q2.pop()) printf("[%lld](%d, %d) ", q2.top().first, q2.top().second.first, q2.top().second.second);
		// puts("");
		if(type == 1) {
			// printf("insert\n");
			auto [v, p] = q.top();
			while(a[p.first][p.second] || dist(p) != v) q.pop(), std::tie(v, p) = q.top();
			// printf("ans = (%d, %d) [v=%lld]\n", p.first, p.second, v);
			q.pop();
			a[p.first][p.second] = true;
			auto it = st.emplace(p.first).first;
			if(it == st.begin()) {
				if(p.first != 1) {
					LL dist1 = dist(Pos(1, 0), p), dist2 = dist(Pos(1, 1), p);
					if(dist1 >= dist2) q.emplace(dist1, Pos(1, 0));
					else q.emplace(dist2, Pos(1, 1));
				} else if(!a[1][!p.second]) q.emplace(1, Pos(1, !p.second));
			} else {
				auto p2 = best(*std::prev(it), p.first);
				if(p2.first != -1) q.emplace(dist(p2), p2);
				// printf("best = (%d, %d)\n", p2.first, p2.second);
			}
			if(std::next(it) == st.end()) {
				if(p.first != n) {
					LL dist1 = dist(Pos(n, 0), p), dist2 = dist(Pos(n, 1), p);
					if(dist1 >= dist2) q.emplace(dist1, Pos(n, 0));
					else q.emplace(dist2, Pos(n, 1));
				} else if(!a[n][!p.second]) q.emplace(1, Pos(n, !p.second));
			} else {
				auto p2 = best(p.first, *std::next(it));
				if(p2.first != -1) q.emplace(dist(p2), p2);
				// printf("best = (%d, %d)\n", p2.first, p2.second);
			}
			printf("%d %d\n", p.first, p.second + 1);
			pos[qid] = p;
		} else {
			int x;
			scanf("%d", &x);
			auto p = pos[x];
			// printf("erase (%d, %d)\n", p.first, p.second);
			a[p.first][p.second] = false;
			if(!a[p.first][!p.second]) {
				st.erase(p.first);
				auto it = st.lower_bound(p.first);
				if(it == st.begin()) {
					LL dist1 = dist(Pos(1, 0)), dist2 = dist(Pos(1, 1));
					if(dist1 >= dist2) q.emplace(dist1, Pos(1, 0));
					else q.emplace(dist2, Pos(1, 1));
				} else if(it == st.end()) {
					LL dist1 = dist(Pos(n, 0)), dist2 = dist(Pos(n, 1));
					if(dist1 >= dist2) q.emplace(dist1, Pos(n, 0));
					else q.emplace(dist2, Pos(n, 1));
				} else {
					int i = *std::prev(it), j = *it;
					auto p2 = best(i, j);
					q.emplace(dist(p2), p2);
					// printf("best = (%d, %d)\n", p2.first, p2.second);
				}
			} else {
				auto it = st.find(p.first);
				if(it == st.begin()) {
					if(p.first != 1) {
						LL dist1 = dist(Pos(1, 0), p), dist2 = dist(Pos(1, 1), p);
						if(dist1 >= dist2) q.emplace(dist1, Pos(1, 0));
						else q.emplace(dist2, Pos(1, 1));
					} else q.emplace(1, Pos(1, p.second));
				} else {
					auto p2 = best(*std::prev(it), p.first);
					if(p2.first != -1) q.emplace(dist(p2), p2);
					// printf("best = (%d, %d)\n", p2.first, p2.second);
				}
				if(std::next(it) == st.end()) {
					if(p.first != n) {
						LL dist1 = dist(Pos(n, 0), p), dist2 = dist(Pos(n, 1), p);
						if(dist1 >= dist2) q.emplace(dist1, Pos(n, 0));
						else q.emplace(dist2, Pos(n, 1));
					} else q.emplace(1, Pos(n, p.second));
				} else {
					auto p2 = best(p.first, *std::next(it));
					if(p2.first != -1) q.emplace(dist(p2), p2);
					// printf("best = (%d, %d)\n", p2.first, p2.second);
				}
			}
		}
	}
	return 0;
} /*
5 20
1
2 1
1
1
1
1
2 5
1
1
1
1
2 4
2 3
1
1
2 8
1
2 14
2 17
2 9
*/