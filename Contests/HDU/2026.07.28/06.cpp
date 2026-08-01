#include <bits/stdc++.h>
#include <cassert>

const int N = 1500 + 5;

bool a[N];

std::vector<int> factor[N];
void prepare(int mx) {
	for(int i = 1; i <= mx; i++)
		for(int j = i + i; j <= mx; j += i)
			factor[j].emplace_back(i);
}

void add(int x) {
	// printf("add %d\n", x);
	assert(!a[x]);
	for(int d : factor[x]) if(a[d]) a[d] = false, add(2 * d);
	a[x] = true;
}

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	prepare(1500);
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) a[i] = false;
		for(int i = 1; i <= n; i += 2) {
			add(i);
			// for(int j = 1; j <= n; j++) if(a[j]) printf("%d ", j);
			// puts("");
		}
		printf("%d\n", (n + 1) / 2);
		for(int i = 1; i <= n; i++) if(a[i]) printf("%d ", i);
		puts("");
	}
	return 0;
}