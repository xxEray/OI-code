#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 2e5 + 5;

int n, m;
std::vector<int> a[N];
std::vector<int> tmp;

int main() {
#ifndef DEBUG
	freopen("potato.in", "r", stdin);
	freopen("potato.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) std::vector<int> ().swap(a[i]);
		for(int i = 1; i <= n; i++) a[i].push_back(0);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) { int x; scanf("%d", &x); a[i].push_back(x); }
		for(int i = 1; i <= n; i++) a[i].push_back(1000000001); // 1e9 + 1
		int x = 0, y = 0, z = 0;
		for(int i = 1; i <= n; i++) if(!std::is_sorted(a[i].begin(), a[i].end())) {
			tmp = a[i];
			std::sort(tmp.begin(), tmp.end());
			for(int j = 1; j <= m; j++) if(a[i][j] != tmp[j]) (x ? (y ? z : y) : x) = j;
			break;
		}
		if(z) { printf("-1\n"); continue; }
		if(!x) x = y = 1;
		for(int i = 1; i <= n; i++) std::swap(a[i][x], a[i][y]);
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= std::is_sorted(a[i].begin(), a[i].end());
		if(flag) printf("%d %d\n", x, y);
		else printf("-1\n");
	}
	return 0;
} /*
1 10
1 2 3 3 3 3 3 2 3 3
*/