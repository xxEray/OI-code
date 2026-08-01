#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e3 + 5;

int sg[N];

int main() {
	int n, l, r;
	scanf("%d%d%d", &n, &l, &r);
	sg[0] = 0;
	for(int i = 1; i <= n; i++) {
		std::vector<int> vct;
		for(int j = l; j <= r; j++) if(i - j >= 0) vct.push_back(sg[i - j]);
		std::sort(vct.begin(), vct.end());
		vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
		if(vct.empty() || vct[0]) sg[i] = 0;
		else {
			for(int j = 1; j < (int)vct.size(); j++) if(vct[j] - vct[j - 1] > 1) { sg[i] = vct[j - 1] + 1; break; }
			if(sg[i] == 0) sg[i] = vct.back() + 1;
		}
	}
	for(int i = 0; i <= n; i++) printf("%d ", sg[i]);
	puts("");
	return 0;
}