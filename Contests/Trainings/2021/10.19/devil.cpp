#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>

const int N = 5000 + 5;

int a[N];
int n, m;

struct Node { int v, id; } tmp[N];
bool operator<(Node x, Node y) { return x.v < y.v; }

int b[N], ind[N];
std::vector<std::pair<int, int>> q;
void add(int l, int r) {
	if(l > r) std::swap(l, r);
	l--;
	if(r - l <= 1) return;
	for(int i = 1; i <= n; i++) b[i] = a[i];
	std::reverse(a + l + 1, a + r + 1);
	for(int i = 1; i <= n; i++) if(a[i] != b[i]) { q.push_back({l, r}); return; }
}

int main() {
	srand(time(NULL));
	scanf("%d%d", &n, &m); m++;
	for(int i = 1; i <= n; i++) scanf("%d", &tmp[i].v), tmp[i].id = i;
	std::sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; i++) a[tmp[i].id] = i;
	if(tmp[m].v != tmp[a[m]].v) { puts("-1"); return 0; }
//	for(int i = 1; i <= n; i++) printf("%d: a=%d, ind=%d\n", i, a[i], ind[i]);
	bool swp = false;
	while(true) {
		q.clear();
		for(int i = 1; i <= n; i++) a[tmp[i].id] = i;
		for(int i = 1; i <= n; i++) ind[a[i]] = i;
		if(swp) {
			int l, r;
			while(true) {
				if(rand() & 1) l = rand() % (m - 1) + 1, r = rand() % (m - 1) + 1;
				else l = rand() % (n - m) + m + 1, r = rand() % (n - m) + m + 1;
				if(l > r) std::swap(l, r);
				if(l == r) continue; 
				std::reverse(a + l, a + r + 1);
				q.push_back({l - 1, r});
				break;
			}
		}
		for(int i = 1; i <= n; i++) ind[a[i]] = i;
		for(int i = 1; i <= n; i++) {
			int x = ind[i], y = i;
			if(y <= m && m <= x) {
				if(m * 2 - x >= i) add(x, m * 2 - x), add(m * 2 - x, y);
				else add(x, m * 2 - y), add(m * 2 - y, y);
			} else if(x <= m && m <= y) {
				if(m * 2 - x <= n) add(x, m * 2 - x), add(m * 2 - x, y);
				else add(x, m * 2 - y), add(m * 2 - y, y);
			} else add(x, y);
			for(int j = 1; j <= n; j++) ind[a[j]] = j;
		}
		if((int)q.size() <= n * 3 / 2) {
			printf("%d\n", (int)q.size());
			for(auto p : q) printf("%d %d\n", p.first, p.second);
			return 0;
		} else swp = true;
	}
	return 0;
} /*
50 48
3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 50 48 46 44 42 40 38 36 34 32 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 49 1
*/
