#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n, A, B;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &A, &B);
		if(std::abs(A - B) > 1) { puts("-1"); continue; }
		bool flg = (A < B);
		if(A < B) std::swap(A, B);
		a[1] = 1;
		for(int i = 2; i <= n; i += 2) a[i] = i + 1, a[i + 1] = i;
		if(a[n] == n + 1) a[n] = n;
		int nA = (n - 1) / 2, nB = n / 2 - 1;
		nA -= A, nB -= B;
		if(nA < 0 || nB < 0) { puts("-1"); continue; }
		for(int i = 2; i <= n; i += 2) if(nA && nB) std::swap(a[i], a[i + 1]), nA--, nB--;
		if(n & 1) {
			if(nA) std::swap(a[n - 1], a[n]);
			else if(nB) std::swap(a[n - 2], a[n]);
		} else {
			if(nA) std::swap(a[n - 2], a[n]);
			else if(nB) std::swap(a[n - 1], a[n]);
		}
		if(flg) for(int i = 1; i <= n; i++) a[i] = n - a[i] + 1;
		for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		puts("");
	}
	return 0;
} /*

*/