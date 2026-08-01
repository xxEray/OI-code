#include <bits/stdc++.h>
#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n"), V = opt<int>("V");
	bool distinct = opt<bool>("distinct"), sorted = opt<bool>("sorted");
	std::cout << n << '\n';
	std::set<int> st;
	std::vector<int> vct;
	for(int i = 1; i <= n; i++) {
		int v = rnd.next(1, V);
		if(distinct) while(st.count(v)) v = rnd.next(1, V);
		vct.push_back(v);
	}
	if(sorted) std::sort(vct.begin(), vct.end());
	for(int x : vct) printf("%d ", x);
	std::cout << std::endl;
	return 0;
}
