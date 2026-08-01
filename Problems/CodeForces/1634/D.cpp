#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 1000 + 5;

struct Node { int val, id; };
bool operator<(Node x, Node y) { return x.val < y.val; }
std::vector<Node> vct;
int n;

inline int query(int x, int y, int z) { int ret; printf("? %d %d %d\n", x, y, z); fflush(stdout); scanf("%d", &ret); return ret; }
inline void answer(int x, int y) { printf("! %d %d\n", x, y); fflush(stdout); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		if(n == 4) {
			int a[5] = {0, query(1, 2, 3), query(1, 2, 4), query(1, 3, 4), query(2, 3, 4)};
			int mx1 = -1, mx2 = -1;
			for(int i = 1; i <= 4; i++) {
				if(mx1 == -1 || a[i] > a[mx1]) mx1 = i;
				if(mx2 == -1 || a[i] >= a[mx2]) mx2 = i;
			}
			assert(mx1 != -1 && mx2 != -1 && mx1 < mx2);
			int t = mx1 * 10 + mx2;
			switch(t) {
				case 12: answer(1, 2); break;
				case 13: answer(1, 3); break;
				case 14: answer(2, 3); break;
				case 23: answer(1, 4); break;
				case 24: answer(2, 4); break;
				case 34: answer(3, 4); break;
				default: assert(false);
			}
			continue;
		}
		vct.clear();
		for(int i = 3; i <= n; i++) vct.push_back({query(1, 2, i), i});
		std::sort(vct.begin(), vct.end());
		if(vct.front().val == vct.back().val) {
			int v = -1, flag = true, id = -1, same = false;
			for(int i = 5; i <= n; i++) {
				int r = query(3, 4, i);
				if(r == 0) same = true;
				else if(v == -1) v = r, id = i;
				else if(v != r) flag = false;
			}
			if(!flag || v <= vct.front().val) answer(1, 2);
			else if(same) answer(3, id);
			else if(query(1, 3, id) == v) answer(3, id);
			else assert(query(1, 4, id) == v), answer(4, id);
			continue;
		}
		int most = vct.back().id;
		// printf("most = %d\n", most);
		vct.clear();
		for(int i = 2; i <= n; i++) if(i != most) vct.push_back({query(1, most, i), i});
		std::sort(vct.begin(), vct.end());
		if(vct.front().val == vct.back().val) {
			int x = 2, y = 3;
			if(most == 2) x = 3, y = 4;
			else if(most == 3) y = 4;
			if(query(x, y, most) == vct.front().val) answer(x, most);
			else answer(1, most);
			continue;
		}
		int another_most = vct.back().id;
		answer(another_most, most);
	}
	return 0;
}