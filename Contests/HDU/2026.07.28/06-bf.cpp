#include <bits/stdc++.h>

void calc(int n) {
	auto bit = [n](int s, int i) -> bool { return s >> (n - i) & 1; };
	int ans = 0;
	for(int s = (1 << n) - 1; s >= 0; s--) {
		if(__builtin_popcount(s) <= __builtin_popcount(ans)) continue;
		bool flag = true;
		for(int i = 1; i <= n && flag; i++) if(bit(s, i))
			for(int j = i + i; j <= n && flag; j += i)
				flag &= !bit(s, j);
		if(!flag) continue;
		ans = s;
	}
	printf("n=%2d: [len=%2d] ", n, __builtin_popcount(ans));
	for(int i = 1; i <= n; i++)
		if(i < 10) {
			if(bit(ans, i)) printf("%d ", i);
			else printf("  ");
		} else {
			if(bit(ans, i)) printf("%d ", i);
			else printf("   ");
		}
	puts("");
}

int main() {
	for(int i = 1; i <= 30; i++) calc(i);
	return 0;
}