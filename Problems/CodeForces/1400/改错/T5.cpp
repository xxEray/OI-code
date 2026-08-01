#include <cstdio>
#include <algorithm>
 
const int N = 5000 + 5;
 
int a[N];
int n;
 
int f(int l, int r, int del) {
	if(l > r) return 0;
	int mnid = std::min_element(a + l, a + r + 1) - a;
	return std::min(f(l, mnid - 1, a[mnid]) + f(mnid + 1, r, a[mnid]) + a[mnid] - del, r - l + 1);
}
 
int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]);
	std::printf("%d\n", f(1, n, 0));
	return 0;
}