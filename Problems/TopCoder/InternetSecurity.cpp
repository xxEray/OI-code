#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using std::vector;
using std::string;

const int N = 50 + 5;

struct Site {
	string name;
	vector<string> keyword;
} a[N];
int n;
std::set<string> dangerous;
bool vis[N];

class InternetSecurity {
public:
	vector<string> count(vector<string> site, vector<string> keywords_str, vector<string> dangerous_vec, int least) {
		n = site.size();
		for(int i = 1; i <= n; i++) a[i].name = site[i - 1];
		for(int i = 1; i <= n; i++) {
			std::istringstream sin(keywords_str[i - 1]);
			string tmp;
			while(sin >> tmp) a[i].keyword.push_back(tmp);
		}
		for(string &s : dangerous_vec) dangerous.insert(s);
		for(int i = 1; i <= n; i++) {
			bool flag = false;
			for(int j = 1; j <= n; j++) {
				if(vis[j]) continue;
				int cnt = 0;
				for(string &s : a[j].keyword) cnt += (dangerous.find(s) != dangerous.end());
				if(cnt >= least) {
					flag = true, vis[j] = true;
					for(string &s : a[j].keyword) dangerous.insert(s);
				}
			}
			if(!flag) break;
		}
		vector<string> ans;
		for(int i = 1; i <= n; i++) if(vis[i]) ans.push_back(a[i].name);
		return ans;
	}
};

int main() {
	InternetSecurity T;
	vector<string> vct = T.count({""}, {""}, {""}, 0);
	for(string &s : vct) std::cout << s << std::endl;
	return 0;
}