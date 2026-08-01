#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

const int N = 2e5 + 5;

int n, m;
std::vector<int> a[N];

bool f[N];
int sum[N];
std::map<int, int> mp;

int main() {
	int T; scanf("%d", &T);
	// bool test = (T == 1000);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			int x, y;
			a[i].clear();
			scanf("%d", &x);
			while(x--) scanf("%d", &y), a[i].push_back(y);
			std::sort(a[i].begin(), a[i].end());
			a[i].erase(std::unique(a[i].begin(), a[i].end()), a[i].end());
		}
		int j = 1;
		int last = 0, cnt = 0;
		mp.clear();
		f[0] = true, sum[0] = 1;
		// int lasts = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i].empty()) { last = i; f[i] = true, sum[i] = sum[i - 1] + f[i]; continue; }
			int oldj = (cnt ? j : -1);
			for(int x : a[i]) mp[x]++, cnt += (mp[x] == 2);
			while(cnt) {
				for(int x : a[j]) mp[x]--, cnt -= (mp[x] == 1);
				j++;
				if(!cnt) {
					j--;
					for(int x : a[j]) mp[x]++, cnt += (mp[x] == 2);
					break;
				}
			}
			// printf("i = %d, j = %d, cnt = %d, last = %d, lasts = %d\n", i, j, cnt, last, lasts);
			f[i] = false;
			// if(j != oldj) lasts = i;
			if(j > last && j != oldj && cnt) f[i] |= sum[j - 1] - (oldj - 1 >= 0 ? sum[oldj - 1] : 0);
			if(j <= last && j != oldj) {
				if(cnt) f[i] |= sum[last - 1] - (j - 2 >= 0 ? sum[j - 2] : 0);
				else f[i] |= sum[last - 1];
				if(cnt) f[i] |= (j - 2 >= 0 ? sum[j - 2] : 0) - (oldj - 1 >= 0 ? sum[oldj - 1] : 0);
			}
			if(oldj == j && j <= last) f[i] |= sum[last - 1] - sum[j - 1];
			sum[i] = sum[i - 1] + f[i];
		}
		// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
		mp.clear();
		int ans = 0;
		bool fl = false, fl2 = false;
		for(int i = n; i >= 1; i--) {
			bool flag = true;
			for(int x : a[i]) mp[x]++, flag &= (mp[x] <= 1);
			if(!flag) break;
			if(a[i].empty()) fl2 = true;
			if(f[i - 1]) fl |= fl2, ans = std::max(ans, (int)mp.size());
		}
		if(fl) ans = m;
		// if(!test)
		printf("%d\n", ans);
		// else {
		// 	if(T == 20000 - 351) {
		// 		printf("%d %d\n", n, m);
		// 		for(int i = 1; i <= n; i++) {
		// 			printf("%d ", (int)a[i].size());
		// 			for(int x : a[i]) printf("%d ", x);
		// 			puts("");
		// 		}
		// 	}
		// }
	}
	return 0;
} /*
1
10 10
1 5
6 1 3 4 5 8 9
5 2 5 6 9 10
0
0
4 2 4 5 9
2 1 6
7 1 2 3 5 6 7 10
6 3 4 5 7 8 9
1 8
*/