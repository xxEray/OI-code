#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n");
	std::string type = opt<std::string>("type");
	if(type == "enumerate") {
		printf("%d\n", n);
		for(int i = 1; i <= n; i++) printf("%d\n", i);
	} else if(type == "random") {
		std::vector<int> data;
		int sum = 2e6;
		while(sum) {
			int val = rnd.next(1, n);
			val = std::min(val, sum);
			data.push_back(val);
			sum -= val;
		}
		printf("%d\n", (int)data.size());
		for(int x : data) printf("%d\n", x);
	} else ensure(type == "enumerate" || type == "random");
	return 0;
}