#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
std::vector<int> vct;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		vct.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) { int x; scanf("%1d", &x); if(x) vct.push_back(i); }
		if(vct.size() & 1) { puts("-1"); continue; }
		if(vct.size() != 2) { printf("%d\n", (int)vct.size() / 2); continue; }
		int x = vct[0], y = vct[1];
		if(y - x >= 2) puts("1");
		else if(n <= 3) puts("-1");
		else if(n == 4) printf("%d\n", x == 2 ? 3 : 2);
		else puts("2");
	}
	return 0;
}