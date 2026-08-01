#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

std::vector<int> a[N];
int n, m;

int pos[N];
std::pair<int, int> getpos(int ind) {
	auto &v = a[ind];
	auto t = v;
	std::sort(t.begin() + 1, t.begin() + m + 1);
	int cnt = 0;
	for(int i = 1; i <= m; i++) if(v[i] != t[i]) pos[++cnt] = i;
	if(cnt == 2) return {pos[1], pos[2]};
	else return {-1, -1};
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) std::vector<int> (m + 3, 0).swap(a[i]);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
		std::pair<int, int> p = {0, 0};
		for(int i = 1; i <= n; i++) if(!std::is_sorted(a[i].begin() + 1, a[i].begin() + m + 1)) {
			auto t = getpos(i);
			if(p.first == 0) p = t;
			else if(p != t) p = {-1, -1};
		}
		for(int i = 1; i <= n; i++) {
			std::swap(a[i][p.first], a[i][p.second]);
			if(!std::is_sorted(a[i].begin() + 1, a[i].begin() + m + 1)) { p = {-1, -1}; break; }
		}
		printf("\t\t\t");
		if(p.first == -1) puts("-1");
		else if(p.first == 0) puts("1 1");
		else printf("%d %d\n", p.first, p.second);
	}
	return 0;
}