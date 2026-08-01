#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>

const int N = 5e5 + 5;

int a[N], b[N];
int n, Q;

std::vector<int> stk;
int left[N];
bool smaller(int x, int y) { return a[x] == a[y] || b[x] <= b[y]; }

struct Query { int r, v, id, op; } q[N << 1];
bool operator<(Query x, Query y) { return x.r < y.r; }
int out[N];

inline char nc(){
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline int readint(){
    char ch = nc(); int sum = 0;
    while(!(ch >= '0' && ch <= '9')) ch = nc();
    while(ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
    return sum;
}

struct FHQ {
	int c[N][2], v[N], w[N], sz[N];
	int tot, rt;
	void init() { tot = 0; }
	int nw(int key) { tot++, w[tot] = rand() << 15 | rand(), v[tot] = key, sz[tot] = 1; return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	void split(int root, int key, int &x, int &y) {
		if(!root) x = y = 0;
		else if(v[root] <= key) x = root, split(c[root][1], key, c[x][1], y), pushup(x);
		else y = root, split(c[root][0], key, x, c[y][0]), pushup(y);
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		else if(w[x] > w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x;}
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void insert(int key) {
		int x, y;
		split(rt, key - 1, x, y);
		rt = merge(merge(x, nw(key)), y);
	}
	int size(int key) { // order_of_key
		int x, y, ans;
		split(rt, key, x, y);
		ans = sz[x];
		rt = merge(x, y);
		return ans;
	}
} treap;

int main() {
// #ifndef DEBUG
	// freopen("stack.in", "r", stdin);
	// freopen("stack.out", "w", stdout);
// #endif
	n = readint(), Q = readint();
	for(int i = 1; i <= n; i++) a[i] = readint();
	for(int i = 1; i <= n; i++) b[i] = readint();
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && smaller(stk.back(), i)) stk.pop_back();
		left[i] = (stk.empty() ? 1 : stk.back() + 1);
		stk.push_back(i);
	}
	// for(int i = 1; i <= n; i++) printf("%d ", left[i]);
	// puts("");
	int cnt = 0;
	for(int o = 1; o <= Q; o++) {
		int l, r;
		l = readint(), r = readint();
		q[++cnt] = {l - 1, l, o, -1};
		q[++cnt] = {r, l, o, 1};
	}
	std::sort(q + 1, q + cnt + 1);
	int j = 1;
	while(j <= cnt && q[j].r == 0) j++;
	for(int i = 1; i <= n; i++) {
		treap.insert(left[i]);
		while(j <= cnt && q[j].r == i) out[q[j].id] += treap.size(q[j].v) * q[j].op, j++;
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i]);
	return 0;
} /*
1 1 3 1 5 6 6 5 9 9
*/