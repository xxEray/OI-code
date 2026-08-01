#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
struct Line {
	LL x, y;
	Line() {}
	Line(LL x1, LL y1, LL x2, LL y2) {
		x = x1 - x2, y = y1 - y2;
		if(x < 0) x = -x, y = -y;
		LL g = gcd(x, std::abs(y));
		x /= g, y /= g;
		if(x == 0) y = 1;
		if(y == 0) x = 1;
	}
	bool operator<(const Line &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
} a[N];
int n;

std::map<Line, int> mp;
std::vector<int> g;

int f[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		mp.clear(), g.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			LL x1, y1, x2, y2;
			scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
			a[i] = Line(x1, y1, x2, y2);
			mp[a[i]]++;
		}
		for(auto &p : mp) g.push_back(p.second);
		std::sort(g.begin(), g.end());
		// printf("g: "); for(auto x : g) { printf("%d ", x); } puts("");
		int high = 0, lastid = 1, sum = 0, ind = 0;
		while(ind < (int)g.size()) {
			while(ind < (int)g.size() && high >= g[ind]) ind++;
			if(ind == (int)g.size()) break;
			high++, sum += (int)g.size() - ind;
			for(; lastid <= sum; lastid++) f[lastid] = high;
		}
		// int now=0,sum=0,t=0;
        // for(int i=0;i<g.size();i++){
        //     while(t<g[i]){
        //         t++;sum+=g.size()-i;
        //         while(now<sum)f[++now]=t;
        //     }
        // }
		for(int i = 1; i <= n; i++) printf("%d\n", i - f[i]);
	}
	return 0;
}