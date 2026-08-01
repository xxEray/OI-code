#include <bits/stdc++.h>

const int N = 1000 + 5;

int n;
struct Node { int v, id; } b[N];
int a[N], p[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].v), b[i].id = i;
	std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.v == y.v ? x.id < y.id : x.v < y.v; });
	for(int i = 1; i <= n; i++) a[b[i].id] = i;
	int cnt = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) cnt += (a[i] > a[j]);
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) p[a[i]] = i;
	for(int i = 1; i <= n; i++)
		for(int j = a[i] - 1; j >= i; j--) {
			int t = p[j];
			printf("%d %d\n", i, t);
			std::swap(a[i], a[t]), p[a[i]] = i, p[a[t]] = t;
		}
	return 0;
}