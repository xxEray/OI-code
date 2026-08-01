#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

typedef long long LL;

const int N = 50 + 5;

int edge[N][N];
int used[70];
vector<int> to[N];

int nw_id() {
	for(int i = 0; i < 60; i++) if(!used[i]) return i;
	return -1;
}

LL ans[N];

class BitwiseAnd {
public:
	vector<LL> lexSmallest(vector<LL> st, int n) {
		int m = st.size();
		for(int i = 1; i <= m; i++) ans[i] = st[i - 1];
		for(int i = 1; i <= m; i++)
			for(int j = 0; j < 60; j++) if(st[i - 1] >> j & 1) {
				if(!used[j]) used[j] = i;
				else if(used[j] != -1) edge[i][used[j]] = edge[used[j]][i] = true, used[j] = -1;
				else return {};
			}
		for(int i = 59; i >= 0; i--) if(used[i] > 0) to[used[i]].push_back(i);
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++) if(!edge[i][j]) {
				if(i <= m && j <= m) return {};
				else if(i <= m) {
					if(to[i].empty()) return {};
					int id = to[i].back();
					to[i].pop_back();
					ans[j] |= 1LL << id;
					used[id] = -1;
				} else {
					int id;
					if(!to[i].empty()) id = to[i].back(), to[i].pop_back();
					else {
						id = 100;
						if(to[i].empty() && to[j].empty()) id = std::min(id, nw_id());
						if(!to[j].empty()) id = std::min(id, to[j].back()), to[j].pop_back();
					}
					if(id == -1 || id == 100) return {};
					ans[i] |= 1LL << id, ans[j] |= 1LL << id;
					used[id] = -1;
				}
			}
		auto v = vector<LL>(ans + 1, ans + n + 1);
		std::sort(v.begin(), v.end());
		return v;
	}
};

// int main() {
// 	BitwiseAnd T;
// 	auto v = T.lexSmallest({14, 20}, 3);
// 	for(auto x : v) printf("%lld ", x);
// 	return 0;
// }