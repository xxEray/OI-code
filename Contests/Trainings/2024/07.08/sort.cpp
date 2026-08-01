#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n;
int a[N];

namespace Solve_baoli {

	void main() {

	}
}

namespace Solve_luangao {
	std::vector<int> vcta, vctb;
	bool vis[N];
	int pivot;
	void pop(int x) {
		vis[x] = true;
		while(pivot < n && vis[pivot + 1]) pivot++;
	}
	void main() {
		vcta.clear(), vctb.clear();
		for(int i = 1; i <= n; i++) vis[i] = false;
		pivot = 0;
		std::vector<char> ans;
		bool flag = true;
		for(int i = 1; i <= n; i++) {
			int x = a[i];
			if(vcta.empty() || vcta.back() > x) {
				ans.emplace_back('a');
				vcta.emplace_back(x);
				while(!vcta.empty() && vcta.back() - 1 <= pivot) pop(vcta.back()), vcta.pop_back(), ans.emplace_back('b');
			} else {
				while(!vctb.empty() && vctb.back() - 1 <= pivot) pop(vctb.back()), vctb.pop_back(), ans.emplace_back('d');
				while(!vcta.empty() && vcta.back() - 1 <= pivot) pop(vcta.back()), vcta.pop_back(), ans.emplace_back('b');
				if(vcta.empty() || vcta.back() > x) {
					ans.emplace_back('a');
					vcta.emplace_back(x);
					while(!vcta.empty() && vcta.back() - 1 <= pivot) pop(vcta.back()), vcta.pop_back(), ans.emplace_back('b');
				} else if(vctb.empty() || vctb.back() > x) {
					ans.emplace_back('c'), vctb.emplace_back(x);
				} else {
					// printf("i = %d\nnow: ", i);
					// for(char c : ans) printf("%c ", c);
					// puts("");
					flag = false;
					break;
				}
			}
		}
		while(!vctb.empty() && vctb.back() - 1 <= pivot) pop(vctb.back()), vctb.pop_back(), ans.emplace_back('d');
		while(!vcta.empty() && vcta.back() - 1 <= pivot) pop(vcta.back()), vcta.pop_back(), ans.emplace_back('b');
		if(!flag) puts("0");
		else {
			for(char c : ans) putchar(c), putchar(' ');
			puts("");
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if(n <= -1) Solve_baoli::main();
		else Solve_luangao::main();
	}
	return 0;
} /*
1
6
2 3 1 4 5 6
7
5 7 2 4 1 6 3
*/