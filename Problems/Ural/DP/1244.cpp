#include <cstdio>

const int N = 100 + 5;
const int S = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n, s;

int f[N][S];
bool pre[N][S], appear[N];

int main() {
	scanf("%d%d", &s, &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i <= n; i++) f[i][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= s; j++) {
			f[i][j] = f[i - 1][j] + (j >= a[i] ? f[i - 1][j - a[i]] : 0);
			if(f[i - 1][j]) pre[i][j] = 0;
			if(j >= a[i] && f[i - 1][j - a[i]]) pre[i][j] = 1;
		}
		if(f[i][s] >= 2) { puts("-1"); return 0; }
	}
	if(f[n][s] == 0) { puts("0"); return 0; }
	for(int i = n, j = s; i >= 1; i--)
		if(pre[i][j]) appear[i] = true, j -= a[i];
	for(int i = 1; i <= n; i++) if(!appear[i]) printf("%d ", i);
	return 0;
} /*
270
4
100
110
170
200
*/