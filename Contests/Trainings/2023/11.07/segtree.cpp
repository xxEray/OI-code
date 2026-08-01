#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;

unsigned long long Seed;
long long W, X, Y, Z;
unsigned long long HRAND() {
	Seed ^= Seed << 9;
	Seed ^= Seed >> 11;
	Seed ^= Seed << 15;
	return Seed;
}
void Gen(int &op, int &k) {
	long long OP = HRAND() % (X + Y + 2 * Z);
	if(OP < X) op = 1 + HRAND() % 2, k = 0;
	else if(OP < X + Y) op = 3 + HRAND() % 2, k = HRAND() % (2 * W) - W;
	else if(OP < X + Y + Z) op = 5 + HRAND() % 2, k = 0;
	else op = 7 + HRAND() % 2, k = 0;
}

int x, y;
LL tagall, tagl, tagr, vall, valr;
LL a[N], pre[N], suf[N];
int pivot;

void maintain() {
	pre[pivot] = a[pivot];
	if(pivot > x) suf[pivot] = a[pivot];
	else suf[pivot] = LLINF;
	pre[pivot + 1] = LLINF;
	for(int i = pivot - 1; i >= x + 1; i--) pre[i] = std::min(pre[i + 1], a[i]);
	for(int i = pivot + 1; i <= y; i++) suf[i] = std::min(suf[i - 1], a[i]);
}

int main() {
#ifndef DEBUG
	freopen("segtree.in", "r", stdin);
	freopen("segtree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	scanf("%llu%lld%lld%lld%lld", &Seed, &W, &X, &Y, &Z);
	long long ans = 0;
	x = 0, y = n - 2, pivot = (x + y) / 2;
	for(int q = 1; q <= m; q++) {
		int op, k;
		Gen(op, k);
		// printf("op = %d, k = %d\n", op, k);
		LL ret = 0;
		if(op == 1) {
			if(x + 1 == y) {
				for(int i = 0; i <= x; i++) a[i] += tagl;
				tagl = 0;
				vall = a[0];
				x = 0, pivot = (x + y) / 2;
				maintain();
			} else if(x + 1 != pivot) x++, a[x] -= tagl, vall = std::min(vall, a[x]);
			else {
				x++, a[x] -= tagl, vall = std::min(vall, a[x]);
				pivot = (x + y) / 2;
				maintain();
			}
		} else if(op == 2) {
			if(y - 1 == x) {
				for(int i = n - 1; i >= y + 1; i--) a[i] += tagr;
				tagr = 0;
				valr = a[n - 1];
				y = n - 2, pivot = (x + y) / 2;
				maintain();
			}  else if(y - 1 != pivot) y--, a[y + 1] -= tagr, valr = std::min(valr, a[y + 1]);
			else {
				y--, a[y + 1] -= tagr, valr = std::min(valr, a[y + 1]);
				pivot = (x + y) / 2;
				maintain();
			}
		} else if(op == 3) tagl += k;
		else if(op == 4) tagall += k, tagr -= k;
		else if(op == 5) ret = vall + tagl + tagall;
		else if(op == 6) ret = std::min({vall + tagl, pre[x + 1], suf[y]}) + tagall;
		else if(op == 7) ret = std::min({pre[x + 1], suf[y], valr + tagr}) + tagall;
		else if(op == 8) ret = valr + tagr + tagall;
		// printf("                     x = %d, y = %d, pivot = %d, ret = %lld\n", x, y, pivot, ret);
		if(op >= 5) ans ^= (LL)(q % 998) * (ret + (LL)5e14);
	}
	printf("%lld\n", ans);
	return 0;
} /*
5 10
11794 10000000 1 1 1
*/