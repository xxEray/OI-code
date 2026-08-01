#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <unordered_map>

typedef long long LL;

const int N = 3e5 + 5;
const LL H = 97;
const LL MOD = 1e9 + 7;

int n, Q;
char s[N];
LL power[N];
LL h[N];

std::unordered_map<int, int> mp;
std::set<int> st;

int main() {
	scanf("%d", &Q);
	power[0] = 1;
	for(int i = 1; i <= 300000; i++) power[i] = power[i - 1] * H % MOD;
	while(Q--) {
		int t;
		scanf("%d%s", &t, s + 1);
		int sz = strlen(s + 1);
		if(t == 1) {
			st.insert(sz);
			LL now = 0;
			for(int i = 1; i <= sz; i++) now = (now * H + s[i]) % MOD;
			mp[now]++;
		} else if(t == 2) {
			LL now = 0;
			for(int i = 1; i <= sz; i++) now = (now * H + s[i]) % MOD;
			mp[now]--;
		} else if(t == 3) {
			LL ans = 0;
			LL now = 0;
			for(int i = 1; i <= sz; i++) {
				now = (now * H + s[i]) % MOD;
				h[i] = now;
			}
			for(int l : st)
				for(int i = 1; i + l - 1 <= sz; i++) {
					LL now = (h[i + l - 1] - h[i - 1] * power[l] % MOD + MOD) % MOD;
					ans += mp[now];
				}
			printf("%lld\n", ans);
			fflush(stdout);
		}
	}
	return 0;
}