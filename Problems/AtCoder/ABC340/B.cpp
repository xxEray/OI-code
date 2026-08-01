#include <bits/stdc++.h>

int main() {
	int Q;
	scanf("%d", &Q);
	std::vector<int> vct;
	while(Q--) {
		int t, x;
		scanf("%d%d", &t, &x);
		if(t == 1) vct.emplace_back(x);
		else printf("%d\n", vct.end()[-x]);
	}
	return 0;
}