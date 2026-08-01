#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2030;

int a[N], c[N];
int n;

std::vector<int> stk;
void rev(int r) {
	stk.push_back(r);
	for(int i = 1; i <= r; i++) if(i < r - i + 1) std::swap(a[i], a[r - i + 1]), c[a[i]] = i, c[a[r - i + 1]] = r - i + 1;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		stk.clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), c[a[i]] = i;
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (c[i] & 1) == (i & 1);
		if(!flag) { puts("-1"); continue; }
		for(int i = n; i > 1; i -= 2)
			rev(c[i]), rev(c[i - 1] - 1), rev(c[i - 1] + 1), rev(3), rev(i);
		printf("%d\n", (int)stk.size());
		for(int i : stk) printf("%d ", i);
		puts("");
	}
	return 0;
}