#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

typedef long long LL;

const int N = 2e6 + 5;
const int SQRTN = 2000 + 3;

int n, m, K, Q;

bool swap_tag;

LL buff[N * 28];

LL *cv[SQRTN], *cv1[SQRTN], *cv2[SQRTN], *cx[SQRTN], *cx1[SQRTN], *cy[SQRTN], *cy2[SQRTN];

void init_array(LL **arr) {
	static int p = 0;
	for(int i = 0; i <= n + 2; i++) arr[i] = &buff[p], p += m + 3;
}

void init_arrays() {
	init_array(cv), init_array(cv1), init_array(cv2);
	init_array(cx), init_array(cx1);
	init_array(cy), init_array(cy2);
}

void sum(LL **arr, int xl, int yl, int xr, int yr, LL v) {
	// if(&arr == &cv) printf("[%d..%d][%d..%d] += %lld\n", xl, xr, yl, yr, v);
	xl = std::max(xl, 1), xr = std::min(xr, n);
	yl = std::max(yl, 1), yr = std::min(yr, m);
	if(xl > xr || yl > yr) return;
	arr[xr + 1][yr + 1] += v, arr[xl][yr + 1] -= v, arr[xr + 1][yl] -= v, arr[xl][yl] += v;
}
void sum_tri1(LL **arr1, LL **arr2, int xl, int yl, int xr, int yr, LL v) {
	if(xl < 1) yr -= 1 - xl, xl = 1;
	if(yl < 1) xr -= 1 - yl, yl = 1;
	if(xr > n + m) { sum(arr1, xl, yl, n, m, v); return; }
	if(xr > n) {
		sum(arr1, xl, yl, n, yl + (xr - n), v);
		yl += xr - n + 1, xr = n - 1;
	}
	if(yr > m) yr = m;
	if(xl > xr || yl > yr) return;
	arr2[xr][yl] += v, arr2[xl - 1][yr + 1] -= v;
	sum(arr1, 1, yl, xl - 1, yr, -v);
}
void sum_tria1(LL **arr1, LL **arr2, int xl, int yl, int xr, int yr, LL v) {
	if(xl > xr || yl > yr) return;
	sum(arr1, xl, yl, xr, yr, v);
	sum_tri1(arr1, arr2, xl, yl, xr, yr, -v);
}
void sum_tri2(LL **arr1, LL **arr2, int xl, int yl, int xr, int yr, LL v) {
	if(xl < 1) yl += 1 - xl, xl = 1;
	if(yr > m) xr -= yr - m, yr = m;
	if(xr > n + m) { sum(arr1, xl, 1, n, yr, v); return; }
	if(xr > n) {
		sum(arr1, xl, yr - (xr - n), n, yr, v);
		yr -= xr - n + 1, xr = n - 1;
	}
	if(yl < 1) yl = 1;
	if(xl > xr || yl > yr) return;
	arr2[xr][yr] += v, arr2[xl - 1][yl - 1] -= v;
	sum(arr1, 1, yl, xl - 1, yr, -v);
}
void sum_tria2(LL **arr1, LL **arr2, int xl, int yl, int xr, int yr, LL v) {
	if(xl > xr || yl > yr) return;
	sum(arr1, xl, yl, xr, yr, v);
	sum_tri2(arr1, arr2, xl, yl, xr, yr, -v);
}
void normalize(LL **arr) {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
}
void normalize_tri1(LL **arr) {
	for(int i = n; i >= 1; i--) for(int j = 1; j <= m; j++) arr[i][j] += arr[i + 1][j] + arr[i + 1][j - 1] - arr[i + 2][j - 1];
}
void normalize_tri2(LL **arr) {
	for(int i = n; i >= 1; i--) for(int j = m; j >= 1; j--) arr[i][j] += arr[i + 1][j] + arr[i + 1][j + 1] - arr[i + 2][j + 1];
}

void print_(const char *arr_name, const LL **arr) {
	printf("%s:\n", arr_name);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%2lld%c", arr[i][j], " \n"[j == m]);
}
#define print(arr) print_(#arr, arr)

int main() {
#ifndef DEBUG
	freopen("fireworks.in", "r", stdin);
	freopen("fireworks.out", "w", stdout);
#endif
	read(n), read(m);
	if(n > m) std::swap(n, m), swap_tag = true;
	init_arrays();
	fprintf(stderr, "clock = %f\n", (double)clock() / CLOCKS_PER_SEC);
	read(K);
	while(K--) {
		int x, y; LL a, b;
		read(x), read(y), read(a), read(b);
		if(swap_tag) std::swap(x, y);
		LL t = (a + b - 1) / b;
		// printf("t = %lld\n", t);
		a *= 2;
		sum(cv, x - t + 1, y - t + 1, x + t - 1, y + t - 1, a + 2 * b * x);
		sum_tri1(cv, cv1, x - t + 1, y - t + 1, x + t - 1, y + t - 1, 2 * -b * (x + y));
		sum_tri1(cx, cx1, x - t + 1, y - t + 1, x + t - 1, y + t - 1, 2 * b);
		// sum_tria1(cv, cv1, x - t + 1, y - t + 1, x + t - 1, y + t - 1, b * (x + y));
		// sum_tria1(cx, cx1, x - t + 1, y - t + 1, x + t - 1, y + t - 1, -b);
		// sum(cv, x - t + 1, y - t + 1, x + t - 1, y + t - 1, b * (x + y));
		sum(cx, x - t + 1, y - t + 1, x + t - 1, y + t - 1, -b);
		sum_tri2(cv, cv2, x - t + 1, y - t + 1, x + t - 1, y + t - 1, 2 * -b * (x - y));
		sum_tri2(cy, cy2, x - t + 1, y - t + 1, x + t - 1, y + t - 1, 2 * b);
		// sum_tria2(cv, cv2, x - t + 1, y - t + 1, x + t - 1, y + t - 1, b * (x - y));
		// sum_tria2(cy, cy2, x - t + 1, y - t + 1, x + t - 1, y + t - 1, -b);
		// sum(cv, x - t + 1, y - t + 1, x + t - 1, y + t - 1, b * (x - y));
		sum(cy, x - t + 1, y - t + 1, x + t - 1, y + t - 1, -b);
	}
	fprintf(stderr, "clock = %f\n", (double)clock() / CLOCKS_PER_SEC);
	normalize(cv), normalize(cx), normalize(cy);
	normalize_tri1(cv1), normalize_tri1(cx1);
	normalize_tri2(cv2), normalize_tri2(cy2);
	// print(cv), print(cv1), print(cv2), print(cx), print(cx1), print(cx2), print(cy), print(cy1), print(cy2);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		cv[i][j] = (cv[i][j] + cv1[i][j] + cv2[i][j]) + (i + j) * (cx[i][j] + cx1[i][j]) + (i - j) * (cy[i][j] + cy2[i][j]);
	// print(cv);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cv[i][j] += cv[i - 1][j] + cv[i][j - 1] - cv[i - 1][j - 1];
	fprintf(stderr, "clock = %f\n", (double)clock() / CLOCKS_PER_SEC);
	read(Q);
	LL ans = 0;
	while(Q--) {
		int xl, yl, xr, yr;
		read(xl), read(yl), read(xr), read(yr);
		if(swap_tag) std::swap(xl, yl), std::swap(xr, yr);
		LL ret = (cv[xr][yr] - cv[xl - 1][yr] - cv[xr][yl - 1] + cv[xl - 1][yl - 1]) / 2;
		LL cnt = (xr - xl + 1) * (yr - yl + 1);
		// printf("%lld\n", ret);
		ans ^= (LL)round((double)ret / cnt);
	}
	printf("%lld\n", ans);
	fprintf(stderr, "clock = %f\n", (double)clock() / CLOCKS_PER_SEC);
	return 0;
} /*
1 3
3
1 3 89912538 20
1 3 475488829 7
1 1 773803329 2981
3
1 2 1 2
1 1 1 3
1 3 1 3

1 3
1
1 1 100 1

*/
