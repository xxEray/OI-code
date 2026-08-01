#include <bits/stdc++.h>

const int N = 5000 + 5;

int n;

struct bign {
	int w[N];
	int len;
	void get() {
		char ch = getchar();
		while(ch < '0' || ch > '9') ch = getchar();
		len = 0;
		while('0' <= ch && ch <= '9') w[len++] = ch - '0', ch = getchar();
		std::reverse(w, w + len);
		while(w[len - 1] == 0) len--;
	}
	void put() const {
		if(len == 0) putchar('0');
		for(int i = len - 1; i >= 0; i--) putchar(w[i] + '0');
		puts("");
	}
	int mod2() const {
		return w[0] % 2;
	}
	void divby2() {
		for(int i = len - 1; i >= 0; i--) {
			if(i && w[i] % 2) w[i - 1] += 10;
			w[i] /= 2;
		}
		while(w[len - 1] == 0) len--;
	}
	void set1() {
		for(int i = 0; i < len; i++) w[i] = 0;
		len = 1;
		w[0] = 1;
	}
	bign &operator+=(const bign &x) {
		len = std::max(len, x.len) + 1;
		for(int i = 0; i < len; i++) {
			w[i] += x.w[i];
			if(w[i] >= 10) w[i] -= 10, w[i + 1]++;
		}
		while(w[len - 1] == 0) len--;
		return *this;
	}
};

bign X, Y, ans;

int x[N], y[N];
bign f[N][2][2];

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	scanf("%d", &n);
	X.get(), Y.get();
	for(int i = 1; i <= n; i++) x[i] = X.mod2(), y[i] = Y.mod2(), X.divby2(), Y.divby2();
	if(X.mod2() || Y.mod2()) { puts("0"); return 0; }
	f[0][0][0].set1();
	for(int i = 1; i <= n; i++) {
		int xx = x[i], yy = y[i];
		for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) for(int j2 = 0; j2 <= 1; j2++) for(int k2 = 0; k2 <= 1; k2++) {
			if((j2 && k2) || (((j + j2 + xx) & 1) && ((-k + k2 - yy) & 1))) continue;
			f[i][(j + j2 + xx) / 2][-k + k2 - yy < 0] += f[i - 1][j][k];
		}
		// printf("f[%d]: %d %d %d %d\n", i, f[i][0][0].x, f[i][0][1].x, f[i][1][0].x, f[i][1][1].x);
	}
	f[n][0][0].put();
	return 0;
} /*
80 7285610927563948192653 98210647293847192059
*/
