#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int a[N], b[N];
int n;

int cnt[N];
std::vector<int> occur[N];
std::vector<int> numbers;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		numbers.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) occur[i].clear(), cnt[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = 0;
		for(int i = 1; i <= n; i++) cnt[a[i]]++, occur[a[i]].push_back(i);
		for(int i = 1; i <= n; i++) if(cnt[i]) numbers.push_back(i);
		std::sort(numbers.begin(), numbers.end(), [](int x, int y) { return cnt[x] > cnt[y]; });
		while(!numbers.empty()) {
			int p = numbers[0];
			int sz = numbers.size();
			int erase = sz;
			for(int i = 1; i < sz; i++) {
				b[occur[numbers[i]].back()] = p, p = numbers[i];
				occur[numbers[i]].pop_back();
				if(occur[numbers[i]].empty()) erase = std::min(erase, i);
			}
			b[occur[numbers[0]].back()] = p;
			occur[numbers[0]].pop_back();
			if(occur[numbers[0]].empty()) erase = 0;
			for(int i = erase; i < sz; i++) numbers.pop_back();
		}
		// printf("\t\t\t");
		for(int i = 1; i <= n; i++) printf("%d ", b[i]);
		puts("");
	}
	return 0;
} /*
2
2
2 1
4
1 2 3 3

*/