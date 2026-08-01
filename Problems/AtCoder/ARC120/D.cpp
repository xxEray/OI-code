#include <bits/stdc++.h>

typedef long long LL;

const int N = 4e5 + 5;

int n;
struct Node { int v, id; } a[N];
bool b[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= 2 * n; i++) scanf("%d", &a[i].v), a[i].id = i;
	std::sort(a + 1, a + 2 * n + 1, [&](Node x, Node y) { return x.v < y.v; });
	for(int i = n + 1; i <= 2 * n; i++) b[a[i].id] = true;
	std::vector<int> stk;
	for(int i = 1; i <= 2 * n; i++)
		if(stk.empty() || stk.back() == b[i]) putchar('('), stk.push_back(b[i]);
		else putchar(')'), stk.pop_back();
	assert(stk.empty());
	return 0;
}