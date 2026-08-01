#include <cstdio>

const int N = 2e5 + 5;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ans = 0;
	for(int i = 0; i < 31; i++) {
		int cnt = 0;
		for(int j = 2; j <= n; j++) cnt ^= ((a[1] ^ a[j]) >> i & 1);
		if(cnt != (a[1] >> i & 1)) ans |= (1 << i);
	}
	printf("%d ", ans);
	for(int i = 2; i <= n; i++) printf("%d ", (ans ^ a[1] ^ a[i]));
	return 0;
}