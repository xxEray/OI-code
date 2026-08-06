#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e3 + 5;

int n, m;
LL a[N][N];

const LL val[4] = {0, 1, 3, 6};

// inline int hash(int x, int y, int z) { return x * 9 + y * 3 + z; }

// int f[31];
// void preprocess() {
// 	for(int x = 0; x <= 2; x++) for(int y = 0; y <= 2; y++) for(int z = 0; z <= 2; z++) {
// 		// x,y,z 编码哪个面被遮住了
// 		// U&D都遮住等价于没遮住&直接-7
// 		// x=0/1/2 -- none/U/D
// 		// y=0/1/2 -- none/L/R
// 		// x=0/1/2 -- none/F/B (front/back)
// 		int &ret = f[hash(x, y, z)]; // 某种遮挡情况下最少损失多少
// 		ret = 100;
// 		auto g = [&](int v, int p, int q) { return v == 0 ? 0 : (v == 1 ? p : q); }; // v为编码，p,q为两个面的数字
// 		auto process = [&](int u, int d, std::array<int, 4> sur) { // 对于特定的 u/d，枚举周围4个翻转，sur逆时针
// 			ret = std::min(ret, g(x, u, d) + g(y, sur[0], sur[2]) + g(z, sur[1], sur[3]));
// 			ret = std::min(ret, g(x, u, d) + g(y, sur[1], sur[3]) + g(z, sur[2], sur[0]));
// 			ret = std::min(ret, g(x, u, d) + g(y, sur[2], sur[0]) + g(z, sur[3], sur[1]));
// 			ret = std::min(ret, g(x, u, d) + g(y, sur[3], sur[1]) + g(z, sur[0], sur[2]));
// 		};
// 		process(1, 6, {2, 4, 5, 3}), process(6, 1, {2, 3, 5, 4});
// 		process(4, 3, {2, 6, 5, 1}), process(3, 4, {2, 1, 5, 6});
// 		process(2, 5, {1, 4, 6, 3}), process(5, 2, {1, 3, 6, 4});
// 	}
// }

int main() {
	// preprocess();
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &a[i][j]);
		for(int i = 0; i <= n + 1; i++) a[i][0] = a[i][m + 1] = 0;
		for(int j = 0; j <= m + 1; j++) a[0][j] = a[n + 1][j] = 0;
		LL ans = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
			ans += a[i][j] * 21LL;
			std::vector<LL> vct = {1LL, a[i][j], a[i][j] - 1, a[i - 1][j], a[i][j - 1], a[i + 1][j], a[i][j + 1]};
			std::sort(vct.begin(), vct.end()), vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
			int lasth = 0;
			for(int h : vct) if(h > 0 && a[i][j] >= h) {
				int cn = 0;
				if(h > 1 && h < a[i][j]) ans -= (h - lasth) * 7LL;
				else if(h < a[i][j] || h > 1) cn++;
				if(a[i][j - 1] >= h && a[i][j + 1] >= h) ans -= (h - lasth) * 7LL;
				else if(a[i][j - 1] >= h || a[i][j + 1] >= h) cn++;
				if(a[i - 1][j] >= h && a[i + 1][j] >= h) ans -= (h - lasth) * 7LL;
				else if(a[i + 1][j] >= h || a[i - 1][j] >= h) cn++;
				// printf("[%d, %d]: %d * (%d, %d, %d)(-%d)\n", i, j, h - lasth, x, y, z, f[hash(x, y, z)]);
				ans -= (LL)(h - lasth) * val[cn];
				lasth = h;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
3
3 4
0 2 0 1
3 1 4 0
0 2 2 5
2 2
1 2
3 4
3 4
0 2 0 1
3 1 4 0
0 2 2 5
*/