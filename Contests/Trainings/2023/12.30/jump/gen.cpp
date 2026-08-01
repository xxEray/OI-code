#include <bits/stdc++.h>

const int N = 5e4;
const int V = (1 << 10);
const int Q = 50;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main() {
	freopen("jump.in", "w", stdout);
	srand(time(0));
	int n = N, A = rand(n / Q, n / Q + 10), B = rand(A, A + 30);
	printf("%d %d %d\n", n, A, B);
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, V));
	puts("");
	return 0;
}