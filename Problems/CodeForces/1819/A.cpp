#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i <= n + 1; i++) a[i] = b[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
		std::sort(b + 1, b + n + 1);
		int m = std::unique(b + 1, b + n + 1) - b - 1;
		int mex = 1;
		if(b[1]) mex = 0;
		else
			for(int i = 2; i <= m; i++)
				if(b[i] == b[i - 1] + 1) mex = b[i] + 1;
				else break;
		// printf("mex = %d\n", mex);
		int l = 0, r = 0;
		for(int i = n; i >= 1; i--) if(a[i] == mex + 1) l = i;
		for(int i = 1; i <= n; i++) if(a[i] == mex + 1) r = i;
		// printf("l = %d, r = %d\n", l, r);
		if(l == 0) { puts(mex == n ? "No" : "Yes"); continue; }
		for(int i = l; i <= r; i++) a[i] = mex;
		// for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		// puts("");
		for(int i = 1; i <= n; i++) b[i] = a[i];
		std::sort(b + 1, b + n + 1);
		m = std::unique(b + 1, b + n + 1) - b - 1;
		// for(int i = 1; i <= m; i++) printf("%d ", b[i]);
		// puts("");
		int mex2 = 1;
		if(b[1]) mex2 = 0;
		else
			for(int i = 2; i <= m; i++)
				if(b[i] == b[i - 1] + 1) mex2 = b[i] + 1;
				else break;
		// printf("mex2 = %d\n", mex2);
		puts(mex2 == mex + 1 ? "Yes" : "No");
	}
	return 0;
}