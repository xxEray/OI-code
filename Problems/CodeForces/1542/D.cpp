#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const int MOD = 998244353;

int n;

int f[N][N][2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char s[2];
		int t, x;
		scanf("%s", s);
		if(s[0] == '-') t = 0;
		else t = 1, scanf("%d", &x);
		for(int j = 0; j < i; j++)
			for(int k = 0; k <= 1; k++)
				if(t == 0)
					f[i][j][k] += 
	}
	return 0;
}