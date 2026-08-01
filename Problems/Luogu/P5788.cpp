#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 3e6 + 5;

int a[N];
int n;

std::vector<int> stk;

int out[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::reverse(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
		out[n - i + 1] = stk.empty() ? 0 : n - stk.back() + 1;
		stk.push_back(i);
	}
	for(int i = 1; i <= n; i++) printf("%d ", out[i]);
	return 0;
}