#include <cstdio>
#include <algorithm>
#include <string>

#define SZ(x) ((int)(x).size())

typedef long long LL;
const int N = 40 + 5;
const int S = (1 << 22) + 5;

char str[N];
int n;
LL f[N][S];

int length(int s) { return 31 - __builtin_clz(s); }
class SPartition {
public:
	LL getCount(std::string ss) {
		n = ss.size();
		f[0][1] = 1;
		for(int i = 1; i <= n; i++) str[i] = ss[i - 1] == 'x' ? 1 : 0;
		for(int i = 0; i <= n / 2; i++) for(int s = 1; s < (1 << 21); s++) {
			int j = length(s);
			if(j > n / 2) continue;
			if(i < j && str[i + j + 1] == (s >> i & 1)) f[i + 1][s] += f[i][s];
			if(j < n / 2) {
				int t = s;
				t &= ~(1 << j);
				t |= 1 << (j + 1);
				t |= str[i + j + 1] << j;
				f[i][t] += f[i][s] * (i == j ? 2 : 1);
			}
		}
		LL ans = 0;
		for(int s = 1; s < (1 << 21); s++) if(length(s) == n / 2) ans += f[n / 2][s];
		return ans;
	}
};

// int main() {
// 	SPartition T;
// 	printf("%lld\n", T.getCount("oxox"));
// 	return 0;
// }