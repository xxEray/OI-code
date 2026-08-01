#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n, m;

bool ok[N];
int g[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) ok[i] = true;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; (long long)j * j <= a[i]; j++)
			if(a[i] % j == 0)
				ok[j] = ok[a[i] / j] = false;
	ok[1] = true;
	int cnt = 0;
	for(int i = 1; i <= m; i++) {
		bool flag = true;
		for(int j = 1; (long long)j * j <= i; j++)
			if(i % j == 0 && (!ok[j] || !ok[i / j])) { flag = false; break; }
		if(flag) g[++cnt] = i;
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++) printf("%d\n", g[i]);
	return 0;
}