#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

typedef long long LL;

const int N = 50 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N], sm[N];
int rb[N];
int n, m;

LL sum(int l, int r) { return sm[r] - sm[l - 1]; }

struct State { LL step, score; State(LL st = 0, LL sc = 0) : step(st), score(sc) {} } f[N];
bool operator<(State x, State y) { return x.step == y.step ? x.score < y.score : x.step > y.step; }
int last[N];
LL div_ceil(LL x, LL y) { return y == 0 ? (x ? -1 : 0) : std::max((x + y - 1) / y, 0LL); }

class RowGame {
public:
	LL score(std::vector<int> board, int m_) {
		n = board.size(), m = m_;
		for(int i = 1; i <= n; i++) a[i] = board[i - 1];
		for(int i = 1; i <= n; i++) sm[i] = sm[i - 1] + a[i];
		for(int i = 1; i <= n; i++)
			for(int j = i; j <= n; j++)
				if(!rb[i] || sum(i, rb[i]) < sum(i, j)) rb[i] = j;
		for(int i = 2; i <= n; i++) f[i] = {LLINF, -LLINF};
		for(int i = 1; i <= n; i++)
			for(int j = 1; j < i; j++) if(sum(j, rb[j]) >= 0) {
				LL need = div_ceil(-sum(j, rb[i]) - f[j].score + std::max(-sum(i, rb[i]), 0LL), sum(j, rb[j]) * 2) * 2;
				if(need == -2) continue; // -1 * 2 => -2
				f[i] = std::max(f[i], State(f[j].step + need + 2, f[j].score + need * sum(j, rb[j]) + sum(j, rb[i]) + sum(i, rb[i])));
			}
		// for(int i = 1; i <= n; i++) printf("sum(%d .. r[%d]=%d) = %lld\n", i, i, rb[i], sum(i, rb[i]));
		// for(int i = 1; i <= n; i++) printf("%d -> %lld, %lld (rb=%d)\n", i, f[i].step, f[i].score, rb[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) if(m >= f[i].step /* maybe error */) ans = std::max(ans, f[i].score + (m - f[i].step) * sum(i, rb[i]));
		return ans;
	}
};

// int main() {
// 	RowGame T;
// 	printf("%lld\n", T.score({-54945964, 908839, 62705995, 55120191, -336736715, 120475581, -72768326, -103351585, -263998456, -250247796, -111221170, -77205336, 59380984, 81416226, -263109899, 187092452, -168172381, -259741880, -179325231, 189771228, -24959787, -252522500, -158616334, -354364761, 12231419, 145106713, -224422733, -62538051, 246538333, -290935871, -55853583, 44108721, 109972969, -393147588, -300771087, -374247394, 379844346, 26460587, -77598979, -284154110, -371270857, -336303797, 38640554, 88110128, 145112429, -371952993, 127718932, 376940048, -231694873, 348393702}, 400000000));
// 	return 0;
// }

int main() {
	RowGame T;
	if(!(T.score({5, 10, 11, -164942654, -30348831, -62344703, -85537520, -326580357, 12, -393409012, -91188257, -50421598, 18, 10, -268821898, -344231296, 10, 6, 6, 16, -224602813, -357769990, -126144452, -139463867, -43307509, 14, 16, 16, -63863116, 11, -383876121, 15, 19, 3, 14, 2, -202016549, -356562464, -146974656, -341480415, 13, 14, 19, 7, 2, -123262487, -17379454, -68449616, -8107488, 3}, 397540517) == (int)15694355702))
		return 1;
	else return 0;
}