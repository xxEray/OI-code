#include <cstdio>
#include <algorithm>
#include <atcoder/segtree>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

const int N = 2e5 + 5;

mint multiply(mint x, mint y) { return x * y; }
mint initial() { return mint::raw(1); }
atcoder::segtree<mint, multiply, initial> seg;
struct Node { int a, b; } a[N];
bool operator<(Node x, Node y) { return x.a < y.a; }
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].a, &a[i].b);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		
	}
	return 0;
}