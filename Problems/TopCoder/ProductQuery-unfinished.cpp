#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

typedef long long LL;

const int N = 100 + 5;

struct Node { int l, r, v; } a[N];
int n, m;

struct Data { int num, id; } b[N];
bool zero[N];
LL f[N];
int llim[N], fa[N];
LL w[N];
int find(int x) {
	if(x == fa[x]) return x;
	else {
		int y = find(fa[x]);
		w[x] *= w[fa[x]];
		fa[x] = y;
	}
}

LL qpow(LL x, int y) { LL ret = 1; while(y--) ret *= x; return ret; }
LL inv(LL x, LL mod) { return qpow(x, mod - 2); }
template<typename T> void chkmin(T &x, T y) { x > y ? x = y : 0; }
template<typename T> void chkmax(T &x, T y) { x < y ? x = y : 0; }
bool check() {
	for(int i = 0; i <= n; i++) fa[i] = i, w[i] = 0;
	for(int i = 1; i <= m; i++) 
}
LL calc(int mod) {
	std::sort(a + 1, a + m + 1, [](Node x, Node y) { return x.l != y.l ? x.r < y.r : x.l < y.l; });
	for(int i = 2; i <= m; i++) if(a[i].l == a[i - 1].l) a[i].l = a[i - 1].r, a[i].v = a[i].v * inv(a[i - 1].v, mod) % mod;
	std::sort(a + 1, a + m + 1, [](Node x, Node y) { return x.r != y.r ? x.l > y.l : x.r > y.r; });
	for(int i = 2; i <= m; i++) if(a[i].r == a[i - 1].r) a[i].r = a[i - 1].l, a[i].v = a[i].v * inv(a[i - 1].v, mod) % mod;
	if(!check()) return 0;
	b[0] = {1, -1};
	for(int i = 1; i <= n + 1; i++) b[i] = {-1, -1}, zero[i] = true, f[i] = 0;
	for(int i = 1; i <= m; i++) if(a[i].v && b[a[i].r].id == -1) b[a[i].r] = {a[i].v, a[i - 1].l};
	for(int i = 1; i <= n; i++) {
		int j = b[i].id;
		if(j != -1 && b[j].id != -1) (b[i].num *= b[j].num) %= mod, b[i].id = b[j].id;
	}
	for(int i = 1; i <= m; i++) if(a[i].v)
		for(int j = a[i].l; j <= a[i].r; j++)
			zero[j] = false;
	for(int i = 1; i <= m; i++) if(!a[i].v) chkmax(llim[a[i].r], a[i].l);
	for(int i = 1; i <= n + 1; i++) chkmax(llim[i], llim[i - 1]);
	f[0] = 1;
	for(int i = 1; i <= n + 1; i++)
		if(zero[i]) {
			for(int j = llim[i - 1]; j < i; j++) {
				LL ret = 1;
				for(int k = j + 1; k < i; k++) ret *= mod - 1;
				f[i] += f[j] * ret;
			}
		}
	// for(int i = 1; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
	LL ret1 = f[n + 1], ret2 = 1;
	// if(!ret1) ret1 = 1;
	for(int i = 1; i <= n; i++) if(zero[i] == false && b[i].num == -1) ret2 *= mod - 1;
	printf("zero:     ans = %lld\n", ret1);
	printf("non-zero: ans = %lld\n", ret2);
	return ret1 * ret2;
}

class ProductQuery {
public:
	int theInput(int n_, vector<int> Qfrom, vector<int> Qto, vector<int> output) {
		n = n_, m = output.size();
		for(int i = 0; i < m; i++) a[i + 1] = (Node){Qfrom[i] + 1, Qto[i] + 1, output[i] % 2};
		LL ans2 = calc(2);
		printf("mod 2: ans = %lld\n", ans2);
		for(int i = 0; i < m; i++) a[i + 1] = (Node){Qfrom[i] + 1, Qto[i] + 1, output[i] % 5};
		LL ans5 = calc(5);
		printf("mod 5: ans = %lld\n", ans5);
		return ans2 * ans5;
	}
};

int main() {
	ProductQuery T;
	printf("%d\n", T.theInput(	
5,
{0, 2, 0},
{1, 4, 4},
{3, 4, 6}

));
	return 0;
}