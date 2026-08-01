#include <bits/stdc++.h>

const int N = 5e4 + 5;

int n;
std::string s;

std::map<std::string, int> mp, mp2;

int main() {
#ifndef DEBUG
	freopen("rec.in", "r", stdin);
	freopen("rec.out", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	std::cin >> n;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		std::cin >> s;
		mp2.clear();
		int last = 0, sum = 0;
		for(int j = 0; j < (int)s.size(); j++) {
			sum += (s[j] == '(' ? 1 : -1);
			if(!sum) {
				mp2[s.substr(last, j - last + 1)]++;
				last = j + 1;
			}
		}
		for(const auto &[str, c] : mp2) {
			cnt -= (mp[str] != 0);
			mp[str] ^= c;
			cnt += (mp[str] != 0);
		}
		std::cout << (cnt ? 1 : 0) << '\n';
	}
	return 0;
}