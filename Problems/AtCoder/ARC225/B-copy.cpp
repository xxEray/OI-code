#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;

bool win[N];

int main() {
	win[0] = false;
	for(int i = 1; i <= 20; i++) {
		for(int s = 0; s < (1 << i) - 1; s++) {
			int cnt = 0;
			bool ret = true;
			bool flag = true;
			for(int j = 0; j < i; j++)
				if(s >> j & 1) cnt++;
				else {
					if(j && cnt == 0) { flag = false; break; }
					ret &= !win[cnt];
					cnt = 0;
				}
			ret &= !win[cnt];
			if(flag) win[i] |= ret;
			// if(flag) printf("s = %d\n", s);
		}
		printf("win[%d] = %d\n", i, (int)win[i]);
	}
	// int T; scanf("%d", &T);
	// while(T--) {
		
	// }
	return 0;
}