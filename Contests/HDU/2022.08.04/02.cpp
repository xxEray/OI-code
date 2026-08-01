#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector<string> ans = {
		"42535295865117307932921825928971026433",
		"85070591730234615865843651857942052865",
		"85070591730234615865843651857942052864"
	};
	cout << ans.size() << '\n';
	for(auto &v : ans) cout << v << ' ';
	return 0;
}