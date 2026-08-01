#include <bits/stdc++.h>

int n, m;
int a[100005][7], b[7];

bool vis[100005];

bool check(int i) {
	int cnt = 0;
	for(int j = 1; j <= 5; j++) cnt += (a[i][j] != b[j]);
	if(cnt == 1) return true;
	else if(cnt != 2) return false;
	for(int j = 1; j < 5; j++)
		if(a[i][j] != b[j] && a[i][j + 1] != b[j + 1] && (b[j] - a[i][j] + 10) % 10 == (b[j + 1] - a[i][j + 1] + 10) % 10) return true;
	return false;
}
bool check() {
	for(int i = 1; i <= n; i++) if(!check(i)) return false;
	return true;
}

int main() {
	scanf("%d", &m);
	while(m--) {
		int w = 0;
		for(int i = 1; i <= 5; i++) scanf("%d", &b[i]), w = w * 10 + b[i];
		if(!vis[w]) {
			vis[w] = true;
			n++;
			for(int i = 1; i <= 5; i++) a[n][i] = b[i];
		}
	}
	if(n > 81) { puts("0"); return 0; }
	int ans = 0;
	for(b[1] = 0; b[1] <= 9; b[1]++)
		for(b[2] = 0; b[2] <= 9; b[2]++)
			for(b[3] = 0; b[3] <= 9; b[3]++)
				for(b[4] = 0; b[4] <= 9; b[4]++)
					for(b[5] = 0; b[5] <= 9; b[5]++)
						ans += check();
	printf("%d\n", ans);
	return 0;
}
