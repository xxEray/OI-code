#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int N = opt<int>("n"), C = opt<int>("C"), L = opt<int>("L"), S = opt<int>("S"), T = opt<int>("T");
	if(C == -1) C = 250000 / N;
	printf("%d\n", C);
	while(C--) {
		int n = rnd.wnext(3, N, 3), s = rnd.next(1, std::min(S, n - 1)), t = rnd.next(1, std::min(T, n));
		printf("%d %d %d\n", n, s, t);
		for(int i = 2; i <= n; i++) printf("%d %d %d\n", rnd.next(1, i - 1), i, rnd.next(0, L));
		std::set<int> st;
		while((int)st.size() < s) st.insert(rnd.next(2, n));
		for(int x : st) printf("%d ", x);
		puts("");
		st.clear();
		while((int)st.size() < t) st.insert(rnd.next(1, n));
		for(int x : st) printf("%d ", x);
		puts("");
	}
	return 0;
}