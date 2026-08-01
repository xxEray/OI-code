#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>

const int N = 1e5 + 5;

int n;
std::bitset<1000> a[N];

std::vector<std::bitset<1000>> stk;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x / gcd(x, y) * y; }

int main() {
#ifndef DEBUG
	freopen("cai.in", "r", stdin);
	freopen("cai.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		for(int j = 2; j <= 700; j++) if(x % j == 0) a[i][j] = 1;
	}
	for(int i = 1; i <= n; i++) {
		stk.push_back(a[i]);
		while(stk.size() >= 2 && (stk.back() & stk.end()[-2]).any()) {
			auto x = stk.back(); stk.pop_back();
			auto y = stk.back(); stk.pop_back();
			stk.push_back(x | y);
		}
	}
	puts(stk.size() > 1 ? "No" : "Yes");
	return 0;
}
