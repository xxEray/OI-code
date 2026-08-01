#include <cstdio>
#include <algorithm>

const int N = 500 + 5;

struct Segment { int l, r, id; } a[N];
int n;

int tmp[N];
int f[N], last[N];

void preprocess() { // 离散化
	for(int i = 1; i <= n; i++) tmp[2 * i - 1] = a[i].l, tmp[2 * i] = a[i].r;
	std::sort(tmp + 1, tmp + 2 * n + 1);
	int n_ = std::unique(tmp + 1, tmp + 2 * n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		a[i].l = std::upper_bound(tmp + 1, tmp + n_ + 1, a[i].l) - tmp;
		a[i].r = std::upper_bound(tmp + 1, tmp + n_ + 1, a[i].r) - tmp;
	}
}

bool cmp(Segment x, Segment y) { return x.r - x.l + 1 < y.r - y.l + 1; }

void print(int x) {
	if(last[x]) print(last[x]);
	printf("%d ", a[x].id); 
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	preprocess();
	std::sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		f[i] = 1;
		for(int j = 1; j < i; j++)
			if(a[j].l > a[i].l && a[j].r < a[i].r && f[i] < f[j] + 1)
				f[i] = f[j] + 1, last[i] = j;
	}
	int ind = 1;
	for(int i = 2; i <= n; i++) if(f[i] > f[ind]) ind = i;
	printf("%d\n", f[ind]);
	print(ind);
	return 0;
}