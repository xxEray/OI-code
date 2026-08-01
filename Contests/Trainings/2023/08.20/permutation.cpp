#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 998244353;

int n;
int a[N];

bool used[N];

// < -1
// > 1
void trans(LL *x, LL *y, int cnt, int w) {
	cnt++;
	if(w == 1) {
		LL sum = 0;
		for(int i = cnt; i >= 1; i--) (sum += x[i]) %= MOD, (y[i] += sum) %= MOD;
	} else {
		LL sum = 0;
		for(int i = 1; i <= cnt; i++) (y[i] += sum) %= MOD, (sum += x[i]) %= MOD;
	}
}

LL f[4][N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) if(a[i]) used[a[i]] = true;
	for(int i = 1; i <= n; i++) {
		// 0
		if(a[i] && a[i] - i >= 2) {

		}
	}
	return 0;
}