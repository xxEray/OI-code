#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;

struct Node1 { int pre, pos, nxt; LL sum; };
bool operator<(const Node1 &x, const Node1 &y) { return x.sum > y.sum; }
struct Box {
	// int id;
	std::vector<int> a;
	mutable std::vector<LL> ans;
	int l, r;
	mutable std::priority_queue<Node1> q;
	void init() {
		std::sort(a.begin(), a.end());
		if(l == 0) {
			ans.push_back(0);
			l++;
			if(l > r) return;
		}
		LL sum = 0;
		for(int i = 0; i < l; i++) sum += a[i];
		// printf("%d: sum = %lld\n", id, sum);
		q.push({l - 2, l - 1, (int)a.size(), sum});
	}
	LL at(int k) const {
		if(k <= (int)ans.size()) return ans[k - 1];
		if(q.empty()) return -1;
		auto next = [&]() -> LL {
			auto p = q.top();
			q.pop();
			if(p.nxt == (int)a.size() && p.pos + 1 < r && p.pre == p.pos - 1) q.push({p.pos, p.pos + 1, (int)a.size(), p.sum + a[p.pos + 1]});
			if(p.pos + 1 < p.nxt) q.push({p.pre, p.pos + 1, p.nxt, p.sum - a[p.pos] + a[p.pos + 1]});
			if(p.pre >= 0 && p.pre + 1 < p.pos) q.push({p.pre - 1, p.pre + 1, p.pos, p.sum - a[p.pre] + a[p.pre + 1]});
			return p.sum;
		};
		while(k > (int)ans.size()) {
			if(q.empty()) break;
			ans.push_back(next());
			// assert(ans.back() == a[(int)ans.size() - 1]);
			// printf("b[%d].at(%d) = %lld (instead of %d)\n", id, (int)ans.size(), ans.back(), a[(int)ans.size() - 1]);
		}
		return k <= (int)ans.size() ? ans[k - 1] : -1LL;
	}
} b[N];

struct Node2 { int pos, k; LL sum; };
bool operator<(const Node2 &x, const Node2 &y) { return x.sum > y.sum; }
std::priority_queue<Node2> q;
std::vector<LL> ans;
void init() {
	LL sum = 0;
	for(int i = 1; i <= m; i++) sum += b[i].at(1);
	ans.push_back(sum);
	int pos = 1;
	while(pos <= m && b[pos].at(2) == -1) pos++;
	if(pos <= m) q.push({pos, 2, sum - b[pos].at(1) + b[pos].at(2)});
}
LL at(int k) {
	if(k <= (int)ans.size()) return ans[k - 1];
	if(q.empty()) return -1;
	auto next = [&]() -> LL {
		auto p = q.top();
		q.pop();
		if(b[p.pos].at(p.k + 1) != -1) q.push({p.pos, p.k + 1, p.sum - b[p.pos].at(p.k) + b[p.pos].at(p.k + 1)});
		if(p.pos < m) q.push({p.pos + 1, 2, p.sum - b[p.pos + 1].at(1) + b[p.pos + 1].at(2)});
		if(p.k == 2 && p.pos < m) q.push({p.pos + 1, 2, p.sum - b[p.pos].at(2) + b[p.pos].at(1) - b[p.pos + 1].at(1) + b[p.pos + 1].at(2)});
		return p.sum;
	};
	while(k > (int)ans.size()) {
		if(q.empty()) break;
		ans.push_back(next());
	}
	return k <= (int)ans.size() ? ans[k - 1] : -1LL;
}

int main() {
#ifndef DEBUG
	freopen("plan.in", "r", stdin);
	freopen("plan.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); b[x].a.push_back(y); }
	for(int i = 1; i <= m; i++) scanf("%d%d", &b[i].l, &b[i].r), b[i].r = std::min(b[i].r, (int)b[i].a.size());
	for(int i = 1; i <= m; i++)
		if(b[i].l > (int)b[i].a.size()) {
			while(K--) puts("-1");
			return 0;
		}
	// for(int i = 1; i <= m; i++) b[i].id = i;
	for(int i = 1; i <= m; i++) b[i].init();
	std::sort(b + 1, b + m + 1, [&](const Box &x, const Box &y) { return std::make_pair(x.at(2) != -1, x.at(2) - x.at(1)) < std::make_pair(y.at(2) != -1, y.at(2) - y.at(1)); });
	// printf("index(b): "); for(int i = 1; i <= m; i++) printf("%d ", b[i].id); puts("");
	init();
	for(int i = 1; i <= K; i++) printf("%lld\n", at(i));
	return 0;
} /*
5 2 7
1 5
1 3
2 3
1 6
2 1
1 1
1 1
*/