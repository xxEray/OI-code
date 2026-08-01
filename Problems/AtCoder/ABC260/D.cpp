#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

const int N = 2e5 + 5;

int n, K;
int a[N];

std::map<int, int> mp;
int c;
std::vector<int> vct[N];
int out[N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), out[i] = -1;
	for(int i = 1; i <= n; i++) {
		auto it = mp.upper_bound(a[i]);
		if(it == mp.end()) {
			mp[a[i]] = ++c;
			vct[c].push_back(i);
			if(K == 1) {
				mp.erase(a[i]);
				out[a[i]] = i;
				vct[c].clear();
			}
		} else {
			mp.erase(a[vct[it->second].back()]);
			mp[a[i]] = it->second;
			vct[it->second].push_back(i);
			if((int)vct[it->second].size() == K) {
				for(auto v : vct[it->second]) out[a[v]] = i;
				mp.erase(a[i]);
				vct[it->second].clear();
			}
		}
		// printf("mp: ");
		// for(auto p : mp) printf("(%d, %d) ", p.first, p.second);
		// puts("");
		// for(int j = 1; j <= c; j++) if(!vct[j].empty()) {
		// 	printf("%d: ", j);
		// 	for(auto v : vct[j]) printf("%d ", a[v]);
		// 	puts("");
		// }
		// puts("--------");
	}
	for(int i = 1; i <= n; i++) printf("%d\n", out[i]);
	puts("");
	return 0;
}