#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>

const int N = 1000 + 5;
const int DSU_N = N * 2;

int n;
int a[N][N];

struct Dsu {
	int t[DSU_N], ht[DSU_N];
	std::vector<std::array<int, 5>> op;
	void init(int mx) { op.clear(); for(int i = 1; i <= mx; i++) t[i] = i, ht[i] = 1; }
	int find(int x) { return x == t[x] ? x : find(t[x]); }
	bool same(int x, int y) { return find(x) == find(y); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if(x != y) {
			if(ht[x] > ht[y]) std::swap(x, y);
			op.push_back({x, t[x], ht[x], y, ht[y]});
			t[x] = y;
			if(ht[x] == ht[y]) ht[y]++;
			ht[x] = 0;
		} else op.push_back({0, 0, 0, 0, 0});
	}
	void undo() {
		auto p = op.back();
		op.pop_back();
		if(p[0] == 0) return;
		t[p[0]] = p[1], ht[p[0]] = p[2], ht[p[3]] = p[4];
	}
} dsu;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
		dsu.init(n * 2);
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++)
			if(a[i][j] > a[j][i]) {
				dsu.merge(i, j + n), dsu.merge(i + n, j);
				if(dsu.same(i, i + n) || dsu.same(j, j + n)) dsu.undo(), dsu.undo();
				else std::swap(a[i][j], a[j][i]);
			} else if(a[i][j] < a[j][i]) {
				dsu.merge(i, j), dsu.merge(i + n, j + n);
				if(dsu.same(i, i + n) || dsu.same(j, j + n)) dsu.undo(), dsu.undo(), std::swap(a[i][j], a[j][i]);
			}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) printf("%d ", a[i][j]);
			puts("");
		}
	}
	return 0;
}