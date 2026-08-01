#include <assert.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>

std::set<std::string> st;
std::string s, t;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		st.clear();
		int n;
		std::cin >> n;
		bool ok = false;
		for(int i = 1; i <= n; i++) {
			std::cin >> s;
			t = "";
			if(s.size() == 1) ok = true;
			else if(s.size() == 2) {
				if(s[0] == s[1]) ok = true;
				t += s[1]; if(st.find(t) != st.end()) ok = true;
				t += s[0]; if(st.find(t) != st.end()) ok = true;
				for(char c = 'a'; c <= 'z'; c++) if(st.find(t + c) != st.end()) ok = true;
			} else if(s.size() == 3) {
				if(s[0] == s[2]) ok = true;
				t += s[2]; if(st.find(t) != st.end() && s[0] == s[1]) ok = true;
				t += s[1]; if(st.find(t) != st.end()) ok = true;
				t += s[0]; if(st.find(t) != st.end()) ok = true;
			} else assert(false);
			st.insert(s);
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}