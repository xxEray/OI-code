#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 6e5 + 5;

char s[N];
int n, Q;

struct Node {
	std::vector<int> sons;
	std::vector<LL> presum;
	int l, r;
	LL ret;
} t[N << 2];
int nw_node() { static int cn = 1; return ++cn; }

int infol[N][2], infor[N][2];
LL Cn2(LL x) { return x * (x - 1) / 2; }
int st;
void build(int fa) {
	while(st <= n && s[st] == ')') st++;
	if(st > n) return;
	int now = nw_node();
	t[fa].sons.push_back(now);
	t[now].presum.push_back(0);
	t[now].l = st, st++;
	infol[t[now].l][0] = fa, infol[t[now].l][1] = t[fa].sons.size();
	while(st <= n && s[st] == '(') build(now);
	t[now].r = st, st++;
	infor[t[now].r][0] = fa, infor[t[now].r][1] = t[fa].sons.size();
	t[now].ret += Cn2(t[now].sons.size() + 1);
	t[fa].ret += t[now].ret;
	t[fa].presum.push_back(t[fa].presum.back() + t[now].ret);
}

void print(int x) { putchar('('); for(int y : t[x].sons) print(y); putchar(')'); }

LL calc(int l, int r) {
	int x = infol[l][0];
	int id1 = infol[l][1] - 1, id2 = infor[r][1] - 1;
	return Cn2(id2 - id1 + 2) + t[x].presum[id2 + 1] - t[x].presum[id1];
}

int main() {
	scanf("%d%d%s", &n, &Q, s + 1);
	st = 1, t[1].l = 0, t[1].r = n + 1, t[1].presum.push_back(0);
	while(st <= n) build(1);
	// print(1); puts("");
	while(Q--) {
		int l, r;
		scanf("%*d%d%d", &l, &r);
		printf("%lld\n", calc(l, r));
	}
	return 0;
} /*
9 4
)(()())()
2 3 6
2 2 7
2 8 9
2 2 9
*/