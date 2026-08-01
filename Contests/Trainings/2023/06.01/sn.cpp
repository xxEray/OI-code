#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N];

int lg[N];
struct ST_Table {
	int t[N << 2];
	int (*calc)(int, int);
	void build(int *arr, int x = 1, int l = 1, int r = 3 * n) {
		if(l == r) { t[x] = arr[l]; return; }
		int mid = (l + r) >> 1;
		build(arr, x << 1, l, mid), build(arr, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	int get(int ql, int qr, int x = 1, int l = 1, int r = 3 * n) {
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return get(ql, qr, x << 1, l, mid);
		else if(ql > mid) return get(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(get(ql, qr, x << 1, l, mid), get(ql, qr, x << 1 | 1, mid + 1, r));
	}
} STmn[19], STmx[19];
int mymin(int x, int y) { return x < y ? x : y; }
int mymax(int x, int y) { return x > y ? x : y; }

int l[19][N], r[19][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i + n] = a[i + 2 * n] = a[i];
	for(int i = 1; i <= 3 * n; i++) l[0][i] = std::max(i - a[i], 1), r[0][i] = std::min(i + a[i], 3 * n);
	for(int i = 2; i <= 3 * n; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 0; i <= 18; i++) STmn[i].calc = mymin, STmx[i].calc = mymax;
	STmn[0].build(l[0]), STmx[0].build(r[0]);
	for(int j = 1; j <= 18; j++) {
		for(int i = 1; i <= 3 * n; i++) if(l[j - 1][i] && r[j - 1][i])
			l[j][i] = STmn[j - 1].get(l[j - 1][i], r[j - 1][i]), r[j][i] = STmx[j - 1].get(l[j - 1][i], r[j - 1][i]);
			// printf("l[%d][%d] = %d, r[%d][%d] = %d\n", j, i, l[j][i], j, i, r[j][i]);
		STmn[j].build(l[j]), STmx[j].build(r[j]);
	}
	for(int i = 1; i <= n; i++) {
		// printf("%d:\n", i);
		int ans = 0;
		int il = i + n, ir = i + n;
		for(int j = 18; j >= 0; j--) {
			int nl = STmn[j].get(il, ir), nr = STmx[j].get(il, ir);
			if(nl && nr && nr - nl + 1 < n) ans += (1 << j), il = nl, ir = nr;
			// printf("j = %d, [nl, nr] = [%d, %d], [il, ir] = [%d, %d], ans = %d\n", j, nl, nr, il, ir, ans);
		}
		if(ir - il + 1 < n) ans++;
		// printf("ans = ");
		printf("%d ", ans);
		// puts("");
	}
	return 0;
}