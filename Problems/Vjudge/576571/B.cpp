#include <bits/stdc++.h>

const int N = 2000 + 5;

int n;
int a[N];

std::bitset<N * N> bs;

int main() {
	scanf("%d", &n);
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
	bs[0] = 1;
	for(int i = 1; i <= n; i++) bs |= bs << a[i];
	sum = (sum + 1) / 2;
	for(int i = sum; ; i++) if(bs[i]) {
		printf("%d\n", i);
		break;
	}
	return 0;
}