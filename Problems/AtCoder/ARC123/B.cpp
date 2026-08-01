#include <cstdio>
#include <algorithm>
#include <set>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N], b[N], c[N];
int n;

std::multiset<int> stb, stc;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), stb.insert(b[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]), stc.insert(c[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		auto pos = stb.upper_bound(a[i]);
		if(pos == stb.end()) b[i] = INF;
		else b[i] = *pos, stb.erase(pos);
	}
	for(int i = 1; i <= n; i++) {
		if(b[i] == INF) { c[i] = INF; continue; }
		auto pos = stc.upper_bound(b[i]);
		if(pos == stc.end()) c[i] = INF;
		else c[i] = *pos, stc.erase(pos);
	}
	c[n + 1] = INF;
	for(int i = 1; i <= n + 1; i++) if(c[i] == INF) { printf("%d\n", i - 1); break; }
	return 0;
}