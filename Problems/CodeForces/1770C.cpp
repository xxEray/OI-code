#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

typedef long long LL;

const int N = 100 + 5;

int n;
LL a[N];

std::map<LL, std::set<LL>> mp;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		bool flag = false;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++)
			if(a[i] == a[j]) flag = true;
			else {
				LL g = std::abs(a[i] - a[j]);
				for(LL k = 2; k <= n; k++) if(g % k == 0) mp[k].insert((k - a[i] % k) % k);
			}
		for(auto &p : mp) if((int)p.second.size() == p.first) flag = true;
		puts(flag ? "NO" : "YES");
	}
	return 0;
}