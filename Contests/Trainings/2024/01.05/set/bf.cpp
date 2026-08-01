#include <bits/stdc++.h>

const int N = 100 + 5;

int V, n;

std::vector<int> vct;

int calc(int x, int y, int w) {
	int mn = x ^ y;
	for(int i = 0; i <= w; i++) mn = std::min(mn, (x + i) ^ (y + i));
	return mn;
}

int main() {
	scanf("%d%d", &V, &n);
	while(n--) {
		int op, x;
		scanf("%d%d", &op, &x);
		if(op == 1) vct.emplace_back(x);
		else {
			if(vct.size() < 2) { puts("oh"); continue; }
			int mn = (1 << V);
			for(int i = 0; i < (int)vct.size(); i++)
				for(int j = i + 1; j < (int)vct.size(); j++)
					mn = std::min(mn, calc(vct[i], vct[j], x));
			printf("%d\n", mn);
		}
	}
	return 0;
}