#include <bits/stdc++.h>

const int N = 2e6 + 5;
const int M = 300 + 5;

int n, m, K;
int a[N];

int pos[2 * M], tot[2 * M];

std::vector<std::array<int, 3>> ans;
std::deque<int> stk[M];
std::set<int> st[2];

int type(int x) { return stk[pos[x]].front() == x ? 0 : 1; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ans.clear(), st[0].clear(), st[1].clear();
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n; i++) stk[i].clear(), st[0].insert(i);
		for(int i = 1; i <= K; i++) pos[i] = 0;
		for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) {
			int v = a[i];
			if(pos[v]) {
				int estk = *st[0].begin(), x = pos[v];
				if(type(v) == 0) ans.push_back({1, estk, 0}), ans.push_back({2, x, estk}), st[stk[x].size()].erase(x), stk[x].pop_front(), st[stk[x].size()].insert(x);
				else ans.push_back({1, x, 0}), st[stk[x].size()].erase(x), stk[x].pop_back(), st[stk[x].size()].insert(x);
				pos[v] = 0;
			} else if(st[0].size() + st[1].size() > 1) {
				int x = *st[st[1].empty() ? 0 : 1].begin();
				ans.push_back({1, x, 0});
				pos[v] = x;
				stk[x].push_back(v);
				if(stk[x].size() == 2) st[1].erase(x);
				else st[0].erase(x), st[1].insert(x);
			} else {
				int estk = *st[0].begin();
				int j = i + 1;
				while(a[j] != v && type(a[j]) == 1) j++;
				int nv = a[j], nestk = pos[nv], cnt = 0;
				if(nestk) for(int k = i + 1; k <= j - 1; k++) cnt += (a[k] == stk[nestk].back());
				if(nv == v) ans.push_back({1, estk, 0});
				else if(cnt & 1) ans.push_back({1, estk, 0}), st[0].erase(estk), stk[estk].push_back(v), st[1].insert(estk), pos[v] = estk;
				else ans.push_back({1, nestk, 0}), stk[nestk].push_back(v), pos[v] = nestk;
				for(int k = i + 1; k <= j - 1; k++) tot[a[k]] = 0;
				for(int k = i + 1; k <= j - 1; k++) tot[a[k]]++, ans.push_back({1, pos[a[k]], 0});
				for(int k = i + 1; k <= j - 1; k++) if(tot[a[k]] & 1) st[1].insert(pos[a[k]]), stk[pos[a[k]]].pop_back(), pos[a[k]] = 0, tot[a[k]] = 0;
				if(nv == v) ans.push_back({1, estk, 0});
				else if(cnt & 1) ans.push_back({1, nestk, 0}), st[1].erase(nestk), stk[nestk].pop_back(), st[0].insert(nestk), pos[nv] = 0;
				else ans.push_back({1, estk, 0}), ans.push_back({2, estk, nestk}), st[1].erase(nestk), stk[nestk].pop_front(), pos[nv] = 0;
				i = j;
			}
		}
		printf("%d\n", (int)ans.size());
		for(auto &p : ans)
			if(p[0] == 1) printf("%d %d\n", p[0], p[1]);
			else printf("%d %d %d\n", p[0], p[1], p[2]);
	}
	return 0;
}