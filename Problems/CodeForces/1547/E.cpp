#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

struct Node { int a, t; int val(int i) { return t + std::abs(a - i); } } a[N];
int n, k;
bool cmp(Node a, Node b) { return a.a < b.a; }

int lmin[N], rmin[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= k; i++) scanf("%d", &a[i].a);
		for(int i = 1; i <= k; i++) scanf("%d", &a[i].t);
		for(int i = 0; i <= std::max(n, k) + 1; i++) lmin[i] = rmin[i] = INF;
		std::sort(a + 1, a + k + 1, cmp);
		for(int i = 1; i <= k; i++) lmin[1] = std::min(lmin[1], a[i].val(1));
		for(int i = 1; i <= k; i++) rmin[n] = std::min(rmin[n], a[i].val(n));
		for(int i = 2, j = 1; i <= n; i++) {
			if(i != 1) {
				lmin[i] = std::min(lmin[i], lmin[i - 1]);
				lmin[i]++;
			}
			while(j <= k && a[j].a < i) lmin[i] = std::min(lmin[i], a[j].val(i)), j++;
		}
		for(int i = n, j = k; i >= 1; i--) {
			if(i != n) {
				rmin[i] = std::min(rmin[i], rmin[i + 1]);
				rmin[i]++;
			}
			while(j >= 1 && a[j].a >= i) rmin[i] = std::min(rmin[i], a[j].val(i)), j--;
		}
		for(int i = 1; i <= n; i++) printf("%d ", std::min(lmin[i], rmin[i]));
		puts("");
	}
	return 0;
}