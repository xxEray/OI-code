#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x;
		scanf("%d", &x);
		std::vector<int> ans = {x};
		for(int i = 0; i <= 31; i++)
			if((x >> i & 1) && x > (1 << i))
				ans.push_back(x - (1 << i)), x ^= 1 << i;
		while(x > 1) ans.push_back(x >> 1), x >>= 1;
		printf("%d\n", (int)ans.size());
		for(int v : ans) printf("%d ", v);
		puts("");
	}
	return 0;
}