#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
int a[N];
int cnt[N], used[N];
bool vis[N];

int f[N];

int main() {
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= 2 * n - 2; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + (2 * n - 2) + 1);
	for(int i = 1; i <= 2 * n - 2; i++) if(a[i] > i) {
		for(int j = 1; j <= n - 1; j++) printf("-1 ");
		puts("");
		return 0;
	}
	for(int i = 1; i <= 2 * n - 2; i++) cnt[a[i]]++;
	for(int i = 1; i <= n; i++) f[i] = -1;
	int base = 0;
	for(int i = 1; i <= n - 1; i++) if(a[i] == i) base++, cnt[a[i]]--, vis[i] = true;
	LL sum = 0;
	int p = 1, q = n - 1;
	for(int _ = 1; _ <= base; _++) {
		while(q >= 1 && used[q] >= cnt[q]) q--;
		if(q < 1) { sum = -1; break; }
		used[q]++, sum += q;
	}
	f[base] = sum;
	for(int i = 1; sum >= 0; i++) {
		while(p <= n - 1 && (!cnt[p] || vis[p])) p++;
		if(p > n - 1) break;
		int need = 1;
		if(used[p] == cnt[p]) need++, sum -= p;
		cnt[p]--, p++;
		while(q >= 1 && used[q] >= cnt[q]) q--;
		if(q < 1) break;
		used[q]++, sum += q;
		if(need == 2) {
			while(q >= 1 && used[q] >= cnt[q]) q--;
			if(q < 1) break;
			used[q]++, sum += q;
		}
		f[base + i] = sum;
	}
	for(int i = 1; i <= n - 1; i++) printf("%d ", f[i]);
	puts("");
	return 0;
}