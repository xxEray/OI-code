#include <cstdio>
#include <algorithm>
#include <cstring>

#define CLEAR(arr) memset(arr, 0, sizeof(arr))

const int N = 1e5 + 5;

struct Node { int a, b, id; } a[N], b[N];
bool cmpa(Node x, Node y) { return x.a < y.a; }
bool cmpb(Node x, Node y) { return x.b < y.b; }
int n;

int mxa[N], mxb[N], ta[N], tb[N], sfa[N];
bool ok[N];

int tmp[N];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i].a;
	std::sort(tmp + 1, tmp + n + 1);
	int n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].a = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i].a) - tmp;
	for(int i = 1; i <= n; i++) tmp[i] = a[i].b;
	std::sort(tmp + 1, tmp + n + 1);
	n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].b = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i].b) - tmp;
	// for(int i = 1; i <= n; i++) { printf("%d ", a[i].a); } puts("");
	// for(int i = 1; i <= n; i++) { printf("%d ", a[i].b); } puts("");
}

int has_bigger(int x, int y) { return sfa[x + 1] > y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		CLEAR(a), CLEAR(b), CLEAR(mxa), CLEAR(mxb), CLEAR(ta), CLEAR(tb), CLEAR(sfa), CLEAR(ok);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].a), a[i].id = i;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].b);
		preprocess();
		for(int i = 1; i <= n; i++) b[i] = a[i];
		std::sort(a + 1, a + n + 1, cmpa);
		std::sort(b + 1, b + n + 1, cmpb);
		for(int i = 1; i <= n; i++) ok[i] = true;
		for(int i = 1; i <= n; i++) mxa[i] = std::max(mxa[i - 1], a[i].b), ta[a[i].id] = mxa[i];
		for(int i = 1; i <= n; i++) mxb[i] = std::max(mxb[i - 1], b[i].a), tb[b[i].id] = mxb[i];
		sfa[n + 1] = 0;
		for(int i = n; i >= 1; i--) sfa[i] = std::max(sfa[i + 1], a[i].b);
		// for(int i = 1; i <= n; i++) printf("%d: !has_bigger(%d, %d)\n", i, ta[i], tb[i]);
		for(int i = 1; i <= n; i++) printf("%d", 1 - has_bigger(tb[i], ta[i]));
		puts("");
	}
	return 0;
} /*
4
1 3 2 4
2 1 4 3
*/