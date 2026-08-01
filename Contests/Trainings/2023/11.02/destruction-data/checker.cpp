#include "testlib.h"

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	int T = inf.readInt(0, 2000000);
	while(T--) {
		int n = inf.readInt(1, 2000000);
		std::vector<int> vct(n), vis(n);
		vct[0] = ouf.readInt(-1, n);
		if(vct[0] == -1) {
			if(n % 4 >= 2) continue;
			else quitf(_wa, "Jury has an answer while participant has not.");
		} else if(vct[0] == 0) quitf(_wa, "Participant's answer is not a permutation.");
		for(int i = 1; i < n; i++) vct[i] = ouf.readInt(1, n);
		for(int i = 0; i < n; i++) vis[vct[i] - 1]++;
		for(int i = 0; i < n; i++) if(vis[i] != 1) quitf(_wa, "Participant's answer is not a permutation.");
		for(int i = 0; i < n; i++) vis[i] = 0;
		for(int i = 0; i < n; i++) vis[std::abs(vct[i] - (i + 1))]++;
		for(int i = 0; i < n; i++) if(vis[i] != 1) quitf(_wa, "Participant's answer is wrong - {|a_i - i|} is not a permutation.");
	}
	quitf(_ok, "correct.");
	return 0;
}