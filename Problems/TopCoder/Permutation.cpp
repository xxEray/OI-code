#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

typedef long long LL;
const int N = 52 + 5;
const char table[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int n;
std::map<LL, std::pair<int, LL>> last[N];
std::vector<int> ans;
std::string str;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

void get_ans(int i, LL j) {
	if(!i && !j) return;
	get_ans(last[i][j].first, last[i][j].second);
	ans.push_back(i - last[i][j].first);
}

class Permutation {
public:
	std::string best(int n_) {
		n = n_;
		last[0][1] = {0, 0};
		for(int i = 0; i < n; i++)
			for(auto p : last[i]) {
				LL k = p.first;
				for(int j = 1; j <= n - i; j++)
					last[i + j][lcm(k, j)] = {i, k};
			}
		LL maxlcm = 0;
		for(auto p : last[n]) maxlcm = std::max(maxlcm, p.first);
		// printf("maxlen = %lld\n", maxlcm);
		get_ans(n, maxlcm);
		std::sort(ans.begin(), ans.end());
		int cnt = 0;
		for(int i : ans) {
			if(!i) continue;
			for(int j = cnt + 2; j <= cnt + i; j++) str.push_back(table[j]);
			str.push_back(table[cnt + 1]);
			cnt += i;
		}
		return str;
	}
};

int main() {
	Permutation T;
	for(int i = 1; i <= 52; i++) printf("%s\n", T.best(i).c_str());
	return 0;
}