#include <cstdio>

const int N = 100 + 5;
const int M = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Dish { char name[31]; int w, v; } a[N];
int n, m;

int f[N][M], g[N][M], last[N][M];

void print(int i, int j) {
	if(i == 0) return;
	else if(last[i][j] == -1) print(i - 1, j);
	else {
		int cnt = 0;
		while(last[i][j] == -2 || last[i][j] >= 0) j = (last[i][j] == -2 ? j - a[i].w : last[i][j]), cnt++;
		print(i - 1, j);
		printf("%s %d\n", a[i].name, cnt);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	m *= 1000;
	for(int i = 1; i <= n; i++) {
		double x;
		scanf("%s%d%lf", a[i].name, &a[i].v, &x);
		a[i].w = x * 1000;
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			f[i][j] = INF;
	f[0][0] = last[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
 			int way;
			int f1 = f[i - 1][j], g1 = g[i - 1][j];
			if(j < a[i].w) { f[i][j] = f1, g[i][j] = g1, last[i][j] = -1; continue; }
			int f2 = f[i][j - a[i].w] + a[i].v, g2 = g[i][j - a[i].w] + (last[i][j - a[i].w] == -1);
			if(f1 < f2 || (f1 == f2 && g1 >= g2)) way = 1;
			else way = 2;
			if(way == 1) f[i][j] = f1, g[i][j] = g1, last[i][j] = -1;
			else f[i][j] = f2, g[i][j] = g2, last[i][j] = -2;
		}
		for(int j = m + 1; j <= m + a[i].w; j++)  {
			int f1 = f[i][m], g1 = g[i][m];
			int f2 = f[i][j - a[i].w] + a[i].v, g2 = g[i][j - a[i].w] + (last[i][j - a[i].w] == -1);
			if(!(f1 < f2 || (f1 == f2 && g1 >= g2))) f[i][m] = f2, g[i][m] = g2, last[i][m] = j - a[i].w;
		}
	}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 0; j <= m; j++)
	// 		if((!j || f[i][j] != f[i][j - 1] || g[i][j] != g[i][j - 1]) && f[i][j] < INF)
	// 			printf("[%d][%d]: f = %d, g = %d, last = %d\n", i, j, f[i][j], g[i][j], last[i][j]);
	printf("%d\n", f[n][m]);
	print(n, m);
	return 0;
} /*
2 9
a 7274 2.116
b 138 9.038
*/