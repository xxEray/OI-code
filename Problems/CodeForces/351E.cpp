#include <bits/stdc++.h>

const int N = 2000 + 5;
const int MAXV = 1e5 + 5;

int n;
int a[N];

std::vector<int> occ[MAXV];
int cnt[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] = std::abs(a[i]), occ[a[i]].emplace_back(i);
	for(int v = 0; v <= 100000; v++) {
		for(int i : occ[v]) {
			int cntl = 0, cntr = 0;
			for(int j = 1; j < i; j++) cntl += cnt[j];
			for(int j = i + 1; j <= n; j++) cntr += cnt[j];
			if(cntl < cntr) a[i] = -a[i];
		}
		for(int i : occ[v]) cnt[i] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) ans += (a[i] > a[j]);
	printf("%d\n", ans);
	return 0;
}