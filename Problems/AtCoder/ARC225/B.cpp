#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::vector<int> vct;
		int cnt = 0;
		for(int i = 1; i <= n; i++)
			if(a[i]) cnt++;
			else {
				if(cnt) vct.emplace_back(cnt);
				cnt = 0;
			}
		if(cnt) vct.emplace_back(cnt);
		bool flag = true;
		for(int x : vct)
			flag &= (x == 2);
		if(flag) puts("Bob");
		else puts("Alice");
	}
	return 0;
}