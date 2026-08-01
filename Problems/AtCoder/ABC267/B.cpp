#include <cstdio>
#include <algorithm>

const int N = 10 + 5;

const int col[N] = {0, 4, 3, 5, 2, 4, 6, 1, 3, 5, 7};

int a[N], b[N];
int n;

int main() {
	for(int i = 1; i <= 10; i++) { int x; scanf("%1d", &x); a[col[i]] += x; b[i] = x; }
	bool ans = false;
	for(int i = 1; i <= 10; i++) for(int j = i + 1; j <= 10; j++) {
		bool flag = false;
		for(int k = i + 1; k <= j - 1; k++) flag |= !a[k];
		ans |= a[i] && a[j] && flag;
	}
	puts(!b[1] && ans ? "Yes" : "No");
	return 0;
}