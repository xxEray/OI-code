#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;

int a[N], b[N];
int n, A, B;

bool check(int x) {
	for(int i = 1; i <= n; i++) b[i] = a[i];
	int i = 1, j = n;
	while(i < j) {
		int k = (x - b[i] + A - 1) / A;
		if(k < 0) { i++; continue; }
		b[i] += k * A;
		while(k && i < j) {
			int t = (b[j] - x) / B;
			if(t < 0) { j--; continue; }
			if(t <= k) b[j] -= t * B, j--, k -= t;
			else b[j] -= k * B, k = 0;
		}
		if(k) return false;
		i++;
		// for(int r = 1; r <= n; r++) printf("%d ", b[r]);
		// puts("");
	}
	bool flag = true;
	for(i = 1; i <= n; i++) flag &= (b[i] >= x);
	// printf("check %d: %d\n", x, flag);
	return flag;
}

int main() {
	scanf("%d%d%d", &n, &A, &B);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	// check(6);
	// return 0;
	int l = 0, r = 2e9;
	while(l < r) {
		int mid = l + ((r - l) >> 1);
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%d\n", l - 1);
	return 0;
} /*
3 2 2
1 5 9

*/