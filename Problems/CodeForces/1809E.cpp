#include <cstdio>
#include <algorithm>

const int N = 1e4 + 5;
const int M = 1e3 + 5;

int n, ma, mb;
int a[N];

int out[M][M], b[M];

int main() {
	scanf("%d%d%d", &n, &ma, &mb);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] = -a[i];
	for(int i = 0; i <= ma + mb; i++) {
		int lb = std::max(0, i - mb), rb = std::min(ma, i);
		for(int j = lb; j <= rb; j++) b[j] = j;
		int l = lb, r = rb, vl = b[l], vr = b[r];
		int tag = 0;
		for(int j = 1; j <= n; j++) {
			if(vl + a[j] < lb) {
				vl = lb;
				while(l < rb && b[l + 1] + tag + a[j] < lb) l++, b[l] = 0;
			} else vl = std::min(rb, std::max(lb, vl + a[j]));
			if(vr + a[j] > rb) {
				vr = rb;
				while(r > lb && b[r - 1] + tag + a[j] > rb) r--, b[r] = 0;
			} else vr = std::min(rb, std::max(lb, vr + a[j]));
			tag += a[j];
		}
		// printf("sum = %d [%d .. %d], l=%d, r=%d: ", i, lb, rb, l, r);
		// for(int j = lb; j <= l; j++) printf("%d ", vl);
		// printf(", ");
		// for(int j = l + 1; j <= r - 1; j++) printf("%d ", b[j] + tag);
		// printf(", ");
		// for(int j = r; j <= rb; j++) printf("%d ", vr);
		// puts("");
		for(int j = lb; j <= rb; j++) out[j][i - j] = b[j] + tag;
		for(int j = lb; j <= l; j++) out[j][i - j] = vl;
		for(int j = r; j <= rb; j++) out[j][i - j] = vr;
	}
	for(int i = 0; i <= ma; i++) for(int j = 0; j <= mb; j++) printf("%d%c", out[i][j], j == mb ? '\n' : ' ');
	return 0;
}