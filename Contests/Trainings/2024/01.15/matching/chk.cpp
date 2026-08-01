#include "testlib.h"

const int N = 1000 + 5;

int match[N];
std::vector<std::array<int, 3>> edge;

int n, m;

int t;
bool check(InStream &stream) {
	std::vector<int> ret;
	ret.emplace_back(stream.readInt(-1, m));
	if(ret[0] == -1) return false;
	else if(ret[0] == 0) stream.quitf(_wa, "Invalid format in test #%d.", t);
	for(int i = 1; i < n; i++) ret.emplace_back(stream.readInt(1, m));
	std::sort(ret.begin(), ret.end());
	for(int i = 1; i <= 2 * n; i++) match[i] = 0;
	int cnt = 0;
	for(int i : ret) {
		auto [u, v, w] = edge[i - 1];
		if(match[u] || match[v]) stream.quitf(_wa, "Invalid match in test #%d.", t);
		match[u] = v, match[v] = u;
		cnt += w;
	}
	if(cnt & 1) stream.quitf(_wa, "The number of black edges is odd in test #%d.", t);
	return true;
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	int T = inf.readInt();
	for(t = 1; t <= T; t++) {
		n = inf.readInt(), m = inf.readInt();
		edge.clear();
		for(int i = 1; i <= m; i++) {
			int u = inf.readInt(), v = inf.readInt(), w = inf.readInt();
			edge.push_back({u, v, w});
		}
		int par = check(ouf), jury = check(ans);
		if(par > jury) quitf(_fail, "Participant has better answer!");
		else if(jury > par) quitf(_wa, "Jury has an answer but participant has not.");
	}
	quitf(_ok, "correct.");
	return 0;
}