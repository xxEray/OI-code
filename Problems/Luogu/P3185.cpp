#include <bits/stdc++.h>

const int N = 39;

int n;
int a[N];

int sg[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		sg[n] = 0;
		for(int i = n - 1; i >= 1; i--) {
			std::vector<int> vct;
			for(int j = i + 1; j <= n; j++)
				for(int k = j; k <= n; k++)
					vct.emplace_back(sg[j] ^ sg[k]);
			// calc mex
			std::sort(vct.begin(), vct.end());
			vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
			for(int j = 0; j <= (int)vct.size(); j++)
				if(j == (int)vct.size() || vct[j] != j) {
					sg[i] = j;
					break;
				}
		}
		int nim = 0; // nim sum (xor sum)
		for(int i = 1; i <= n; i++) if(a[i] & 1) nim ^= sg[i];
		if(nim == 0) { puts("-1 -1 -1\n0"); continue; }
		bool flag = false; // 是否找到一个解
		int ans = 0;
		for(int i = 1; i <= n; i++) if(a[i])
			for(int j = i + 1; j <= n; j++)
				for(int k = j; k <= n; k++)
					if((nim ^ sg[i] ^ sg[j] ^ sg[k]) == 0) {
						if(!flag) printf("%d %d %d\n", i - 1, j - 1, k - 1), flag = true;
						ans++;
					}
		printf("%d\n", ans);
	}
	return 0;
}