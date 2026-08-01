#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

const int N = 2e5 + 5;

int a[N];
int n, Q;

std::map<int, std::vector<int>> b;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[a[i]].push_back(i);
	while(Q--) {
		int x, k;
		scanf("%d%d", &x, &k);
		if((int)b[x].size() < k) puts("-1");
		else printf("%d\n", b[x][k - 1]);
	}
	return 0;
}