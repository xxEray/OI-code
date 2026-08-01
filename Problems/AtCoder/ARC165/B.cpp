#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N];

int pre[N];

struct ST {
	int lg[N], go[21][N];
	std::function<int(int, int)> calc;
	void preprocess() {
		for(int i = 1; i <= n; i++) go[0][i] = a[i];
		for(int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[j][i] = calc(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int get(int l, int r) {
		int k = lg[r - l + 1];
		return calc(go[k][l], go[k][r - (1 << k) + 1]);
	}
} STmn, STmx;

bool sorted(int l, int r) { return pre[r] - pre[l] == r - l; }
bool less_than(int x, int y) {
	if(x > y) return !less_than(y, x);
	if(x + K - 1 < y) return sorted(x, x + K - 1);
	if(!sorted(x, y - 1) || STmx.get(x, y - 1) > STmn.get(y, x + K - 1)) return false;
	return true;
}

int main() {
	STmn.calc = [&](int x, int y) { return x < y ? x : y; };
	STmx.calc = [&](int x, int y) { return x > y ? x : y; };
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	STmn.preprocess(), STmx.preprocess();
	for(int i = 2; i <= n; i++) pre[i] = pre[i - 1] + (a[i] > a[i - 1]);
	int t = 0;
	for(int i = 1; i <= n - K + 1; i++) if(t == 0 || less_than(i, t)) t = i;
	std::sort(a + t, a + t + K);
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}