#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

typedef long long LL;

char s[N];
LL n, m, K;

std::vector<LL> total;
LL ret[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		total.clear();
		scanf("%lld%lld%lld%s", &n, &m, &K, s + 1);
		LL t = 0;
		for(int i = n; i >= 1; i--)
			if(s[i] == '*') t++;
			else if(t) total.push_back(t * m + 1), t = 0;
		if(t) total.push_back(t * m + 1);
		LL prod = 1;
		// for(int x : total) printf("%d ", x);
		// puts("");
		for(int i = 0; i < (int)total.size(); i++) {
			if(prod > K) total[i] = K + 1;
			else if((double)prod * total[i] > K + 1) total[i] = prod = K + 1;
			else prod *= total[i], total[i] = prod;
		}
		std::reverse(total.begin(), total.end());
		total.push_back(1);
		// for(int x : total) printf("%d ", x);
		for(int i = 1, j = 0; i <= n; i++)
			if(s[i] == 'a') ret[i] = -1;
			else if(s[i - 1] != '*') {
				// if(total[j + 1] == 1) ret[i] = K;
				if(K % total[j + 1] == 0) ret[i] = K / total[j + 1];
				else ret[i] = K / total[j + 1] + 1;
				K -= (ret[i] - 1) * total[j + 1];
				j++;
			} else ret[i] = 0;
		for(int i = 1; i <= n; i++)
			if(ret[i] == -1) putchar('a');
			else for(int j = 1; j < ret[i]; j++) putchar('b');
		puts("");
	}
	return 0;
} /*
3
2 4 3
a*
4 1 3
a**a
6 3 21
**a***

*/