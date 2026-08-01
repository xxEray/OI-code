#include <bits/stdc++.h>

int main() {
	std::map<std::multiset<int>, std::vector<int>> mp;
	for(int i = 1; i <= 100000; i++) {
		std::string s = std::to_string(i * i);
		if(s.size() != 7) continue;
		std::multiset<int> st;
		for(char c : s) st.emplace(c - '0');
		mp[st].emplace_back(i);
	}
	for(auto [st, vct] : mp) if(vct.size() >= 7) {
		printf("{");
		for(int x : st) printf("%d ", x);
		printf("}: [");
		for(int x : vct) printf("%d(%d) ", x * x, x);
		printf("]\n");
	}
	return 0;
}