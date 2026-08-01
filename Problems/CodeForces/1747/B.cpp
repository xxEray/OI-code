#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 100 + 5;

int a[N];
int n;

std::vector<std::pair<int, int>> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		ans.clear();
		int i = 1, j = n;
		while(i <= j) ans.push_back({3 * i - 2, 3 * j - 1}), i++, j--;
		printf("%d\n", (int)ans.size());
		for(auto p : ans) printf("%d %d\n", p.first, p.second);
	}
	return 0;
} /*
ABCABCABC
BBCBACAAC
*/