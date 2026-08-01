#include <cstdio>
#include <algorithm>

const int N = 2000 + 5;

int main() {
	int T;
	std::scanf("%d", &T);
	while(T--) {
		int tot1, tot2, cnt1, cnt2, w1, w2;
		std::scanf("%d%d%d%d%d%d", &tot1, &tot2, &cnt1, &cnt2, &w1, &w2);
		if(w1 > w2) std::swap(tot1, tot2), std::swap(cnt1, cnt2), std::swap(w1, w2);
		int ans = 0;
		for(int i = 0; i <= std::min(tot1 / w1, cnt1); i++) {
			int j = std::min(cnt2, (tot1 - i * w1) / w2);
			int k = std::min(cnt1 - i, (tot2 / w1));
			int l = std::min(cnt2 - j, (tot2 - k * w1) / w2);
			ans = std::max(ans, i + j + k + l);
		}
		std::printf("%d\n", ans);
	}
	return 0;
} /*
3
33 27
6 10
5 6
100 200
10 10
5 5
1 19
1 3
19 5
*/