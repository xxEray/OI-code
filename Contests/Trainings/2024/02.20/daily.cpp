#include <bits/stdc++.h>

const int N = 2000 + 5;

int n;
std::pair<int, int> e[N];
int d[N];

namespace Subtask1 {
	int cnt;
	int fa[N];
	int find(int x) {
		cnt++;
		if(fa[x] == -1) return x;
		else return find(fa[x]);
	}
	void merge(int x, int y) { fa[find(y)] = find(x); }
	int p[N];
	void main() {
		for(int i = 1; i < n; i++) p[i] = i;
		int ans = 0;
		do {
			for(int s = 0; s < (1 << (n - 1)); s++) {
				cnt = 0;
				for(int i = 1; i <= n; i++) fa[i] = -1;
				for(int i = 1; i < n; i++) {
					int u = e[p[i]].first, v = e[p[i]].second;
					if(s >> (i - 1) & 1) std::swap(u, v);
					merge(u, v);
				}
				ans = std::max(ans, cnt);
			}
		} while(std::next_permutation(p + 1, p + n));
		printf("%d\n", ans);
	}
}

namespace Subtask5 {
	bool suitable() {
		for(int i = 1; i <= n; i++) if(d[i] > 2) return false;
		return true;
	}
	void main() {
		if(n == 1) puts("0");
		else printf("%d\n", 3 * (n - 1) - 1);
	}
}

namespace Subtask6 {
	bool suitable() {
		int cnt1 = 0;
		for(int i = 1; i <= n; i++) cnt1 += (d[i] == 1);
		return cnt1 == n - 1;
	}
	void main() {
		printf("%d\n", (n - 1) + (n - 1) * n / 2);
	}
}

int main() {
#ifndef DEBUG
	freopen("daily.in", "r", stdin);
	freopen("daily.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) scanf("%d%d", &e[i].first, &e[i].second), e[i].first++, e[i].second++, d[e[i].first]++, d[e[i].second]++;
	if(n <= 5) Subtask1::main();
	else if(Subtask5::suitable()) Subtask5::main();
	else if(Subtask6::suitable()) Subtask6::main();
	return 0;
}
