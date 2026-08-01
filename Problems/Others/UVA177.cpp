#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using std::min;
using std::max;

const int N = (1 << 13) + 5;

int n;

std::string s, tmp;

int minr, maxr, minc, maxc;
template<typename T, int L, int R> struct Array { T data[R - L + 1]; T &operator[](int index) { return data[index - L]; } };
Array<Array<bool, -N, N>, -N, N> a;

const int dirx[4][2] = {{0, 1}, {0,  0}, { 1, 0}, {-1, -1}};
const int diry[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1,  1}};

int main() {
	// freopen("out.txt", "w", stdout);
	while(scanf("%d", &n) == 1 && n) {
		s = ">";
		for(int i = 1; i <= n; i++) {
			tmp = s, s.clear();
			for(char c : tmp)
				if(c == 'L' || c == 'R') s.push_back(c);
				else if(c == '<') s += "-R-";
				else if(c == '>') s += "-L-";
			int f = 0;
			for(char &c : s) if(c == '-') c = (f ? '<' : '>'), f ^= 1;
		}
		tmp = s, s.clear();
		for(char c : tmp) if(c == 'L' || c == 'R') s.push_back(c);
		// printf("%s\n", s.c_str());
		minr = maxr = minc = maxc = 0;
		int x = 0, y = 0, d = 0;
		for(char c : s) {
			minr = min(minr, x), maxr = max(maxr, x);
			minc = min(minc, y), maxc = max(maxc, y);
			int lr = (c == 'L' ? 0 : 1);
			x += dirx[d][lr], y += diry[d][lr];
			d = (d + (lr ? 1 : 3)) % 4;
		}
		minr = min(minr, x), maxr = max(maxr, x);
		minc = min(minc, y), maxc = max(maxc, y);
		for(int i = minr; i <= maxr; i++)
			for(int j = minc; j <= maxc; j++)
				a[i][j] = false;
		x = y = d = 0;
		for(char c : s) {
			a[x][y] = true;
			int lr = (c == 'L' ? 0 : 1);
			x += dirx[d][lr], y += diry[d][lr];
			d = (d + (lr ? 1 : 3)) % 4;
		}
		a[x][y] = true;
		for(int i = minr; i <= maxr; i++) {
			tmp.clear();
			for(int j = minc; j <= maxc; j++)
				if(!a[i][j]) tmp.push_back(' ');
				else if(j & 1) tmp.push_back('|');
				else tmp.push_back('_');
			while(!tmp.empty() && tmp.back() == ' ') tmp.pop_back();
			puts(tmp.c_str());
		}
		puts("^");
	}
	return 0;
}