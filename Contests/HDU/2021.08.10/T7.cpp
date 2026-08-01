#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
int n;

std::pair<LL, LL> f[N];
bool vis[N];
std::vector<int> stk;
std::pair<LL, LL> dfs(int x) {
	if(vis[x]) {
		std::pair<LL, LL> ret = {0, 0};
		std::vector<int> st = stk;
		st.push_back(-1);
		do {
			st.pop_back(); ret.first += st.back(), ret.second++;
		} while(!st.empty() && st.back() != x);
		return ret;
	}
	if(f[x].first != -1) return f[x];
	vis[x] = true;
	stk.push_back(x);
	std::pair<LL, LL> ret = dfs(a[x]);
	stk.pop_back();
	vis[x] = false;
	return f[x] = ret;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) f[i] = {-1, 0}, vis[i] = false;
		bool flag = true;
		for(int i = 2; i <= n; i++) {
			std::pair<LL, LL> p1 = dfs(1), p2 = dfs(i);
			flag &= (p1.first * p2.second == p2.first * p1.second);
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}