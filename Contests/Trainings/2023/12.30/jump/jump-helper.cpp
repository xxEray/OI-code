#include <bits/stdc++.h>

const int N = 5e4 + 5;

int n, A, B;
std::bitset<N> bs;

int main() {
	scanf("%d%d%d", &n, &A, &B);
	bs[0] = 1;
	for(int _  = 0; _ <= 1000; _++) bs |= bs << A;
	for(int _  = 0; _ <= 1000; _++) bs |= bs << B;
	int cnt = 0;
	// for(int i = 0; i < n; i++) printf("%d", (int)bs[i]);
	for(int i = 0; i < n; i++) cnt += bs[i];
	printf("\ncnt = %d\n", cnt);
	return 0;
}