#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int d[N];

int ord[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
		for(int i = 1; i <= n; i++) ord[i] = i;
		std::sort(ord + 1, ord + n + 1, [&](int i, int j) { return d[i] < d[j]; });
		std::vector<std::pair<int, int>> edges;
		bool flag = true;
		bool turn = 0, type = (n >= 2 && d[ord[1]] == d[ord[2]]);
		int id = 1, j[2] = {0, 0}, jlast[2] = {0, 0};
		if(type) j[0] = ord[1], j[1] = ord[2], id = 3, flag &= (n <= 2 || d[ord[3]] > d[ord[1]]);
		else j[0] = j[1] = ord[1], id = 2, flag &= (n <= 1 || d[ord[2]] > d[ord[1]]);
		// printf("ord: "); for(int i = 1; i <= n; i++) printf("%d ", ord[i]); puts("");
		if(!flag) { puts("No"); continue; }
		if(type) edges.emplace_back(ord[1], ord[2]);
		for(; id <= n; id++) {
			int i = ord[id];
			// printf("i = %d\n", i);
			if(d[i] > d[j[0]] + 1) {
				if(jlast[0] == 0 || jlast[1] == 0 || d[i] > d[j[0]] + 2) { flag = false; break; }
				turn = 0;
				j[0] = jlast[0], j[1] = jlast[1];
				jlast[0] = jlast[1] = 0;
			}
			edges.emplace_back(j[turn], i);
			jlast[turn] = i;
			turn ^= 1;
		}
		if(n == 1) { puts(d[1] == 1 ? "Yes" : "No"); continue; }
		else if(n == 2) {
			if(d[1] == 2 && d[2] == 2) puts("Yes\n1 2");
			else puts("No");
			continue;
		}
		// printf("flag = %d\n", (int)flag);
		if(jlast[0] == 0 || jlast[1] == 0) flag = false;
		if(d[jlast[0]] - d[ord[1]] != d[ord[1]] - type - 1) flag = false;
		if(d[jlast[1]] - d[ord[1]] != d[ord[1]] - type - 1) flag = false;
		// if(d[ord[n]] != d[ord[1]] * 2 - type - 1) flag = false;
		if(!flag) { puts("No"); continue; }
		puts("Yes");
		for(auto [u, v] : edges) printf("%d %d\n", u, v);
	}
	return 0;
}