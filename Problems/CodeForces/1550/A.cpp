#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int ans[N];

int main() {
	for(int i = 1; i <= 71; i++)
		for(int j = (i - 1) * (i - 1) + 1; j <= i * i; j++)
			ans[j] = i;
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}