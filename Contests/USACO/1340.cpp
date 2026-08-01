#include <bits/stdc++.h>

const int N = 1e5 + 5;

int m, n;

template<typename T, int L, int R> struct Array {
	T a[R - L + 1];
	T &operator[](const int &index) { return a[index - L]; }
	const T &operator[](const int &index) const { return a[index - L]; }
};

Array<bool, -N, N> target;
Array<Array<int, -N, N>, -2, 2> a;
Array<int, -2, 2> ret;
char op[N];

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++) { int x; scanf("%d", &x); target[x] = true; }
	scanf("%s", op + 1);
	int now = 0;
	for(int i = 1; i <= n; i++)
		if(op[i] == 'L') now--;
		else if(op[i] == 'R') now++;
		else {
			for(int j = -2; j <= 2; j++) a[j][now + j]++;
		}
	for(int j = -2; j <= 2; j++) for(int i = -n; i <= n; i++) ret[j] += (target[i] && a[j][i]);
	int ans = ret[0];
	now = 0;
	for(int i = 1; i <= n; i++) {
		if(op[i] == 'L') now--;
		else if(op[i] == 'R') now++;
		else {
			for(int j = -2; j <= 2; j++) {
				ret[j] -= (target[now + j] && a[j][now + j]);
				ret[j] -= (target[now] && a[j][now]);
				a[j][now + j]--, a[j][now]++;
				ret[j] += (target[now] && a[j][now]);
				ret[j] += (target[now + j] && a[j][now + j]);
			}
		}
		if(op[i] == 'L') {
			ans = std::max(ans, ret[2]);
			ans = std::max(ans, ret[1] - (target[now + 1] && a[1][now + 1]) + target[now + 1]);
		} else if(op[i] == 'R') {
			ans = std::max(ans, ret[-2]);
			ans = std::max(ans, ret[-1] - (target[now - 1] && a[-1][now - 1]) + target[now - 1]);
		} else {
			ans = std::max(ans, ret[1] - (target[now] && a[1][now]) + (target[now] && a[1][now] - 1));
			ans = std::max(ans, ret[-1] - (target[now] && a[-1][now]) + (target[now] && a[-1][now] - 1));
		}
	}
	printf("%d\n", ans);
	return 0;
}