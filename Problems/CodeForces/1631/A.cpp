#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N], b[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for(int i = 1; i <= n; i++) if(a[i] < b[i]) std::swap(a[i], b[i]);
		int mxa = 0, mxb = 0;
		for(int i = 1; i <= n; i++) mxa = std::max(mxa, a[i]), mxb = std::max(mxb, b[i]);
		printf("%d\n", mxa * mxb);
	}
	return 0;
}