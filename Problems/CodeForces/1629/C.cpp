#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

const int N = 2e5 + 5;

int a[N];
int n;

std::deque<int> occur[N];
std::vector<int> ans;

bool vis[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		ans.clear();
		for(int i = 0; i <= n; i++) occur[i].clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), occur[a[i]].push_back(i);
		int mex = n + 1;
		for(int i = 0; i <= n; i++) if(occur[i].empty()) mex = std::min(mex, i);
		for(int i = 0; i < mex; i++) vis[i] = false;
		int cnt = 0, nextmex = mex;
		bool flag = true;
		for(int i = 1; i <= n; i++) {
			occur[a[i]].pop_front();
			if(occur[a[i]].empty()) nextmex = std::min(nextmex, a[i]);
			if(a[i] < mex && !vis[a[i]]) {
				vis[a[i]] = true;
				cnt++;
			}
			if(cnt == mex) {
				ans.push_back(mex);
				mex = nextmex;
				nextmex = mex;
				cnt = 0;
				for(int j = 0; j < mex; j++) vis[j] = false;
				if(i == n) flag = false;
			}
		}
		if(flag) ans.push_back(mex);
		printf("%d\n", (int)ans.size());
		for(int i : ans) printf("%d ", i);
		puts("");
	}
	return 0;
}