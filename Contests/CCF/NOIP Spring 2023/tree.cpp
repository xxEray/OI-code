#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

typedef long double LD;

const int N = 1e3 + 5;
const LD eps = 1e-12;
const LD fINF = 1e18;

int n, topid;
LD x[N], y[N];

LD dist(int i, int j) { return sqrtl((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])); }

LD f[N][N][2];
int last[N][N][2];

int trim(int p) { return p <= 0 ? p + n : p > n ? p - n : p; }

void print(int i, int j, int k) {
	// printf("print(%d, %d, %d)\n", i, j, k);
	if(i != topid || j != topid) print(trim(i + !(last[i][j][k] >> 1 & 1)), trim(j - (last[i][j][k] >> 1 & 1)), last[i][j][k] & 1);
	printf("%d ", k ? j : i);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { double xx, yy; scanf("%lf%lf", &xx, &yy); x[i] = xx, y[i] = yy; }
	for(int i = 1; i <= n; i++) if(topid == 0 || y[i] >= y[topid] + eps) topid = i;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 0; k <= 1; k++) f[i][j][k] = fINF;
	f[topid][topid][0] = f[topid][topid][1] = 0;
	for(int i = topid; i >= topid - n + 1; i--) for(int j = topid; j <= topid + n - 1; j++) {
		#define trans(p, q, v, id)\
			if(f p >= f q + (v) + eps)\
				f p = f q + (v), last p = id;
		if(i <= topid - 1) {
			trans([trim(i)][trim(j)][0], [trim(i + 1)][trim(j)][0], dist(trim(i + 1), trim(i)), 0);
			trans([trim(i)][trim(j)][0], [trim(i + 1)][trim(j)][1], dist(trim(j), trim(i)), 1);
			// trans([trim(i)][trim(j)][1], [trim(i + 1)][trim(j)][0], dist(trim(i + 1), trim(j)), 0);
			// trans([trim(i)][trim(j)][1], [trim(i + 1)][trim(j)][1], dist(trim(j), trim(j)), 1);
		}
		if(j >= topid + 1) {
			// trans([trim(i)][trim(j)][0], [trim(i)][trim(j - 1)][0], dist(trim(i), trim(i)), 2);
			// trans([trim(i)][trim(j)][0], [trim(i)][trim(j - 1)][1], dist(trim(j - 1), trim(i)), 3);
			trans([trim(i)][trim(j)][1], [trim(i)][trim(j - 1)][0], dist(trim(i), trim(j)), 2);
			trans([trim(i)][trim(j)][1], [trim(i)][trim(j - 1)][1], dist(trim(j - 1), trim(j)), 3);
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 0; k <= 1; k++) if(f[i][j][k] < fINF - eps) printf("f[%d][%d][%d] = %.10Lf\n", i, j, k, f[i][j][k]);
	int idi = 0, idj = 0, idk = 0;
	for(int i = 1; i <= n; i++) for(int k = 0; k <= 1; k++)
		if(idi == 0 || f[i][trim(i - 1)][k] <= f[idi][idj][idk] - eps) idi = i, idj = trim(i - 1), idk = k;
	// printf("%.10Lf\n", f[idi][idj][idk]);
	print(idi, idj, idk);
	return 0;
}