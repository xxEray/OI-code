#include <bits/stdc++.h>

#define SZ(x) ((int)((x).size()))
// #define NO_SOLUTION "Ikaros"
#define NO_SOLUTION "yyb is our red sun and zsy is our blue moon"

const int N = (1 << 17) + 5;
const int B = 350;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N];

int mp[N];
std::vector<int> st[N], ans[N];
std::vector<int> big;
bool isbig[N];

void update(int b) {
	ans[b].resize((1 << 17) + 1);
	memset(ans[b].data(), 0x3f, sizeof(int) * ((1 << 17) + 1));
	ans[b][b] = 0;
	int last = -INF;
	for(int i = 1; i <= n; i++)
		if(a[i] != b) ans[b][a[i]] = std::min(ans[b][a[i]], i - last);
		else last = i;
	last = INF;
	for(int i = n; i >= 1; i--)
		if(a[i] != b) ans[b][a[i]] = std::min(ans[b][a[i]], last - i);
		else last = i;
	for(int i : big) ans[i][b] = std::min(ans[i][b], ans[b][i]);
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), st[a[i]].emplace_back(i);
	for(int i = 1; i <= (1 << 17) + 1; i++) if(!st[i].empty()) mp[i] = i;
	for(int i = 1; i <= (1 << 17) + 1; i++) if(SZ(st[i]) >= B) {
		st[i].clear();
		isbig[i] = true, big.emplace_back(i);
		update(i);
	}
	int lastans = 0;
	while(Q--) {
		int t, x_, y_;
		scanf("%d%d%d", &t, &x_, &y_);
		x_ ^= lastans, y_ ^= lastans;
		int &x = mp[x_], &y = mp[y_];
		// printf("x = %d, y = %d\n", x, y);
		if(t == 1) {
			if(x == y || !x) continue;
			if(!y) { std::swap(x, y); continue; }
			if(isbig[x]) std::swap(x, y);
			for(int z : big) ans[z][y] = std::min(ans[z][y], ans[z][x]);
			if(isbig[x]) {
				for(int i = 1; i <= n; i++) if(a[i] == x) a[i] = y;
				st[y].clear();
				if(!isbig[y]) big.emplace_back(y), isbig[y] = true;
				update(y);
				big.erase(std::find(big.begin(), big.end(), x)), isbig[x] = false;
			} else {
				for(int i : st[x]) a[i] = y;
				if(SZ(st[x]) + SZ(st[y]) >= B) {
					st[y].clear();
					if(!isbig[y]) big.emplace_back(y), isbig[y] = true;
					update(y);
				} else {
					std::vector<int> vct(SZ(st[x]) + SZ(st[y]));
					std::merge(st[x].begin(), st[x].end(), st[y].begin(), st[y].end(), vct.begin());
					vct.swap(st[y]);
				}
			}
			st[x].clear(), x = 0;
		} else {
			if(!x || !y) { puts(NO_SOLUTION), lastans = 0; continue; }
			if(x == y) { puts("0"), lastans = 0; continue; }
			int ret = INF;
			for(int i = 0, j = -1; i < SZ(st[y]); i++) {
				while(j < SZ(st[x]) - 1 && st[x][j + 1] < st[y][i]) j++;
				if(j >= 0) ret = std::min(ret, st[y][i] - st[x][j]);
			}
			for(int i = 0, j = -1; i < SZ(st[x]); i++) {
				while(j < SZ(st[y]) - 1 && st[y][j + 1] < st[x][i]) j++;
				if(j >= 0) ret = std::min(ret, st[x][i] - st[y][j]);
			}
			// printf("ret = %d\n", ret);
			if(isbig[x]) ret = std::min(ret, ans[x][y]);
			if(isbig[y]) ret = std::min(ret, ans[y][x]);
			printf("%d\n", ret), lastans = ret;
		}
	}
	return 0;
}