#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

int n, Q;
LL m;

LL a[N], c[N];
int b[N];
bool vis[N];
std::vector<int> cycle[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), b[i] = i;
	for(int i = n; i >= 1; i--) a[i] -= a[i - 1];
	scanf("%d%lld", &Q, &m);
	while(Q--) {
		int x;
		scanf("%d", &x);
		std::swap(b[x], b[x + 1]);
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		vis[i] = true;
		int j = b[i];
		cycle[i].push_back(i);
		while(j != i) {
			vis[j] = true;
			cycle[i].push_back(j);
			j = b[j];
		}
	}
	for(int i = 1; i <= n; i++) {
		int sz = cycle[i].size();
		for(int j = 0; j < sz; j++) c[cycle[i][j]] = a[cycle[i][(j + m) % sz]];
	}
	for(int i = 1; i <= n; i++) c[i] += c[i - 1];
	for(int i = 1; i <= n; i++) printf("%lld.0\n", c[i]);
	return 0;
}