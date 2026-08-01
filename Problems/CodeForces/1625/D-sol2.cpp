#include <cstdio>
#include <algorithm>
#include <vector>
#include <assert.h>

const int N = 3e5 + 5;

struct Node { int val, id; } dat[N];
bool operator<(Node x, Node y) { return x.val < y.val; }
int a[N];
int n, m;

std::vector<int> ans;

std::pair<int, int> dfs2(int l1, int r1, int l2, int r2, int bit) {
	if(l1 > r1 || l2 > r2) return {-1, -1};
	if(bit < 0) return {l1, r2};
	int p1 = l1 - 1, p2 = l2 - 1;
	for(int i = l1; i <= r1; i++) if(!(a[i] >> bit & 1)) p1 = i;
	for(int i = l2; i <= r2; i++) if(!(a[i] >> bit & 1)) p2 = i;
	if(!(m >> bit & 1)) {
		bool has1 = (p1 - l1 + 1 > 0), has2 = (r1 - p1 > 0);
		bool has3 = (p2 - l2 + 1 > 0), has4 = (r2 - p2 > 0);
		if(has1 && has4) return {p1, p2 + 1};
		else if(has2 && has3) return {p1 + 1, p2};
		else if(has1 && has3) return dfs2(l1, p1, l2, p2, bit - 1);
		else if(has2 && has4) return dfs2(p1 + 1, r1, p2 + 1, r2, bit - 1);
		assert(false); // NOT reachable
	}
	auto ret1 = dfs2(l1, p1, p2 + 1, r2, bit - 1);
	auto ret2 = dfs2(p1 + 1, r1, l2, p2, bit - 1);
	if(ret1.first != -1) return ret1;
	else if(ret2.first != -1) return ret2;
	else return {-1, -1};
}

void dfs1(int l, int r, int bit) {
	if(l > r) return;
	if(bit < 0) { for(int i = l; i <= r; i++) ans.push_back(dat[i].id); return; }
	int p = l - 1;
	for(int i = l; i <= r; i++) if(!(a[i] >> bit & 1)) p = i;
	if(!(m >> bit & 1)) {
		dfs1(l, p, bit - 1), dfs1(p + 1, r, bit - 1);
	} else {
		auto pr = dfs2(l, p, p + 1, r, bit - 1);
		if(pr.first == -1) ans.push_back(dat[l].id);
		else ans.push_back(dat[pr.first].id), ans.push_back(dat[pr.second].id);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &dat[i].val), dat[i].id = i;
	std::sort(dat + 1, dat + n + 1);
	for(int i = 1; i <= n; i++) a[i] = dat[i].val;
	dfs1(1, n, 30);
	std::sort(ans.begin(), ans.end());
	if((int)ans.size() <= 1) puts("-1");
	else {
		printf("%d\n", (int)ans.size());
		for(auto x : ans) printf("%d ", x);
	}
	return 0;
}