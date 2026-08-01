#include <cstdio>
#include <algorithm>
#include <vector>

std::vector<int> t;

int gcd(int a, int b) {
	if(a < b) std::swap(a, b);
	if(b == 0) return a;
	int r = a % b;
	if(r > 0) t.push_back(r);
	return gcd(b, r);
}

int main() {
	// int n;
	// scanf("%d", &n);
	// for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); gcd(x, y); }
	// std::sort(t.begin(), t.end());
	// for(int x : t) printf("%d ", x);
	// puts("");
	while(true) {
		int x, y;
		scanf("%d%d", &x, &y);
		t.clear();
		gcd(x, y);
		for(int v : t) printf("%d ", v);
		puts("");
	}
	return 0;
}