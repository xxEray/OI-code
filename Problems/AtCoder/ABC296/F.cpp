#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n;
int a[N], b[N];

int cnta[N], cntb[N];

struct BIT {
	int t[N];
	void clear() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnta[a[i]]++;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), cntb[b[i]]++;
	for(int i = 1; i <= n; i++) if(cnta[i] != cntb[i]) { puts("No"); return 0; }
	for(int i = 1; i <= n; i++) if(cnta[i] > 1 || cntb[i] > 1) { puts("Yes"); return 0; }
	long long inva = 0, invb = 0;
	bit.clear();
	for(int i = 1; i <= n; i++) inva += bit.query(n) - bit.query(a[i]), bit.add(a[i], 1);
	bit.clear();
	for(int i = 1; i <= n; i++) invb += bit.query(n) - bit.query(b[i]), bit.add(b[i], 1);
	puts(inva % 2 == invb % 2 ? "Yes" : "No");
	return 0;
}