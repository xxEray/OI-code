#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

typedef long long LL;

const int CBRT_N = 1e6 + 5;

LL n, m;

std::map<LL, int> mp;
std::vector<int> g;
void sieve(int mx) {
	for(int i = 1; i <= mx; i++)
		if(m % i == 0) {
			mp[i] = 0;
			while(m % i == 0) m /= i, mp[i]++;
		}
}



int main() {
	scanf("%lld", &n);
	m = n, sieve(ceil(pow(n, 1.0 / 3)));
	LL sqm = sqrt(m);
	if(sqm * sqm == m) mp[sqm] += 2;
	for(auto &p : mp) if(m % p.first == 0) { mp[p.first]++, mp[m / p.first]++; break; }
	for(auto &p : mp) g.push_back(p.second);
	printf("%lld\n", dfs(1, ))
	return 0;
}