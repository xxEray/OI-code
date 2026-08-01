#include <bits/stdc++.h>

const int N = 1000 + 5;

int n, K;
int a[N];
bool b[N];

std::vector<int> occ[N];

int cnt[N];
struct cmp {
	bool operator()(int x, int y) const {
		if(cnt[x] != cnt[y]) return cnt[x] > cnt[y];
		else if(b[x] != b[y]) return b[x] > b[y];
		else if(occ[x].empty() && occ[y].empty()) return x < y;
		else return (occ[x].empty() ? n + 1 : occ[x].back()) > (occ[y].empty() ? n + 1 : occ[y].back());
	}
};
std::set<int, cmp> st;

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[a[i]] ^= 1;
	for(int i = n; i >= K + 1; i--) occ[a[i]].emplace_back(i);
	for(int i = 1; i <= K; i++) cnt[a[i]]++;
	for(int i = 1; i <= K; i++) st.emplace(a[i]);
	// printf("st: "); for(int z : st) printf("%d(%d) ", z, cnt[z]); puts("");
	int ans = 0, now = K + 1;
	while(!st.empty()) {
		int x = *st.begin();
		if(cnt[x] >= 2) {
			st.erase(st.begin());
			ans++, cnt[x] -= 2;
			if(cnt[x]) st.emplace(x);
			// printf("throw 2 * %d\n", x);
		} else {
			st.erase(st.begin());
			int y = *st.begin();
			st.erase(st.begin());
			assert(cnt[x] == 1 && cnt[y] == 1);
			cnt[x]--, cnt[y]--;
			b[x] ^= 1, b[y] ^= 1;
			// printf("throw %d and %d\n", x, y);
		}
		if(now <= n) {
			if(st.count(a[now])) st.erase(a[now]);
			cnt[a[now]]++, occ[a[now]].pop_back();
			st.emplace(a[now]);
			now++;
			if(st.count(a[now])) st.erase(a[now]);
			cnt[a[now]]++, occ[a[now]].pop_back();
			st.emplace(a[now]);
			now++;
		}
		// printf("st: "); for(int z : st) printf("%d(%d) ", z, cnt[z]); puts("");
	}
	printf("%d\n", ans);
	return 0;
}