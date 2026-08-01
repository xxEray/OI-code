// 未完成

#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 200 + 5;

std::vector<int> a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i < n; i++) {
			int cnt;
			scanf("%d", &cnt);
			while(cnt--) { int x; scanf("%d", &x); a[i].push_back(x); }
		}
		for(int i = 1; i < n; i++) {
			for(int j = 1; j <= n; j++) if(j != i) {
				
			}
		}
	}
	return 0;
}