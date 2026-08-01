#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int D = 2000;
const int NDMAX = N / D + 5;

int n, Q;
int a[N];

LL suma[N];

int fa[N], w[N], ws[N];
int find(int x) {
	if(x == fa[x]) return x;
	int y = fa[x];
	fa[x] = find(y);
	w[x] = ws[x] * w[y];
	ws[x] *= ws[y];
	return fa[x];
}

int f[NDMAX][2 * N];
int g[N];

int block(int x) { return (x - 1) / D + 1; }

int calc(int b, int x) {
	for(int i = (b - 1) * D + 1; i <= b * D; i++) x += (x > 0 ? -a[i] : a[i]);
	return x;
}

int main() {
	// freopen("/home/eray/Downloads/4.in", "r", stdin);
	// freopen("/home/eray/Downloads/3.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), suma[i] = suma[i - 1] + a[i];
	for(int st = 1; st <= n; st += D) {
		int lb = 0, rb = 200000, type = 0;
		for(int i = 0; i <= 200000; i++) fa[i] = i, ws[i] = w[i] = 1;
		g[0] = 0;
		for(int j = st; j <= std::min(n, st + D - 1); j++) g[0] += (g[0] > 0 ? -a[j] : a[j]);
		for(int i = st; i <= std::min(n, st + D - 1); i++) {
			if(type == 0) {
				int mid = lb + a[i];
				if(mid - lb > rb - mid) {
					for(int j = 1; j <= rb - mid; j++) fa[mid + j] = mid - j, ws[mid + j] *= -1;
					g[mid] = 0;
					for(int j = i + 1; j <= std::min(n, st + D - 1); j++) g[mid] += (g[mid] > 0 ? -a[j] : a[j]);
					lb++, rb = mid, type = 1;
				} else {
					for(int j = 1; j <= mid - lb - 1; j++) fa[mid - j] = mid + j, ws[mid - j] *= -1;
					g[mid] = 0;
					for(int j = i + 1; j <= std::min(n, st + D - 1); j++) g[mid] += (g[mid] > 0 ? -a[j] : a[j]);
					lb = mid, type = 0;
				}
			} else {
				int mid = rb - a[i];
				if(mid - lb >= rb - mid) {
					for(int j = 1; j <= rb - mid - 1; j++) fa[mid + j] = mid - j, ws[mid + j] *= -1;
					g[mid] = 0;
					for(int j = i + 1; j <= std::min(n, st + D - 1); j++) g[mid] += (g[mid] > 0 ? -a[j] : a[j]);
					rb = mid, type = 1;
				} else {
					for(int j = 1; j <= mid - lb; j++) fa[mid - j] = mid + j, ws[mid - j] *= -1;
					g[mid] = 0;
					for(int j = i + 1; j <= std::min(n, st + D - 1); j++) g[mid] += (g[mid] > 0 ? -a[j] : a[j]);
					rb--, lb = mid, type = 0;
				}
			}
		}
		if(type == 0) {
			for(int i = 1; i <= rb - lb; i++) g[lb + i] = i;
		} else {
			for(int i = 1; i <= rb - lb; i++) g[rb - i] = -i;
		}
		int stid = st / D + 1;
		for(int i = 0; i <= 200000; i++) {
			int j = find(i);
			if(lb + (type == 0) <= j && j <= rb - (type == 1)) f[stid][200000 + i] = w[i] * g[j], f[stid][200000 - i] = -w[i] * g[j];
			else f[stid][200000 + i] = f[stid][200000 - i] = g[j];
		}
		// printf("lb = %d, rb = %d, type = %d\n", lb, rb, type);
	}
	scanf("%d", &Q);
	while(Q--) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		int op = (x < 0 ? -1 : 1);
		if(x < 0) x = -x;
		int lft = l, rgt = r + 1;
		while(lft < rgt) {
			int mid = (lft + rgt) >> 1;
			if(suma[mid] - suma[l - 1] <= x) lft = mid + 1;
			else rgt = mid;
		}
		if(lft - 1 == r) { printf("%lld\n", op * (x - suma[r] + suma[l - 1])); continue; }
		x = op * (x - suma[lft - 1] + suma[l - 1]), l = lft;
		if(block(l) == block(r)) {
			for(int i = l; i <= r; i++) x += (x > 0 ? -a[i] : a[i]);
		} else {
			for(int i = l; i <= ((l - 1) / D + 1) * D; i++) x += (x > 0 ? -a[i] : a[i]);
			for(int i = block(l) + 1; i <= block(r) - 1; i++) x = f[i][x + 200000];
			for(int i = (r - 1) / D * D + 1; i <= r; i++) x += (x > 0 ? -a[i] : a[i]);
		}
		printf("%d\n", x);
	}
	return 0;
}