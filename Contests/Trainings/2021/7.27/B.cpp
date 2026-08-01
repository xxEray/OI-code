#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

const int powers[] = {1, 2, 4, 8, 16, 32, 3, 6, 12, 24, 48, 9, 18, 36, 27}; // 2^p * 3^q

int n;

int out[N];

bool ok;
void dfs(int i, int x) {
	if(x > n) return;
	if(x == n) {
		printf("%d", out[1]);
		for(int j = 2; j < i; j++) printf(" %d", out[j]);
		puts("");
		ok = true;
		return;
	}
	for(int j = 0; j < 15; j++) {
		bool flag = true;
		for(int k = 1; k < i; k++) if(powers[j] % out[k] == 0 || out[k] % powers[j] == 0) { flag = false; break; }
		if(flag) out[i] = powers[j], dfs(i + 1, x + powers[j]);
		if(ok) break;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		ok = false;
		dfs(1, 0);
	}
	return 0;
}