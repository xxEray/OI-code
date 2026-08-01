#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 5;

bool a[N][N];
int n, m, Q;
bool swaped;

void calc(LL &ans) {
	int i = 1, j = m, it = 0;
	while(i < n) {
		int x = i, y = j, t = it;
		LL len = 0;
		while(x <= n && y <= m) {
			len++;
			t ? x++ : y++;
			t ^= 1;
		}
		// printf("(%d, %d), len = %lld\n", i, j, len);
		ans += len * (len - 1) / 2;
		if(i == 1 && j == 1 && it == 0) it = 1;
		else j == 1 ? i++ : j--;
	}
}

LL _case(int x, int y, int t_init) {
	LL len1 = 1, len2 = 1;
	int tx = x, ty = y, t = t_init;
	while(true) {
		t ? ty-- : tx--;
		if(tx < 1 || ty < 1 || a[tx][ty]) break;
		len1++, t ^= 1;
	}
	tx = x, ty = y, t = !t_init;
	while(true) {
		t ? ty++ : tx++;
		if(tx > n || ty > m || a[tx][ty]) break;
		len2++, t ^= 1;
	}
	return len1 * len2 - 1;
}

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	if(n < m) std::swap(n, m), swaped = true;
	LL ans = (LL)n * m;
	calc(ans);
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(swaped) std::swap(x, y);
		if(a[x][y] == 0) ans -= _case(x, y, 0) + _case(x, y, 1) + 1;
		else ans += _case(x, y, 0) + _case(x, y, 1) + 1;
		a[x][y] ^= 1;
		printf("%lld\n", ans);
	}
	return 0;
}