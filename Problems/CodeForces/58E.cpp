#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <array>

const int N = 20 + 5;
const int INF = 0x3f3f3f3f;

char a[N], b[N], c[N];
int la, lb, lc;
int f[N][N][N][2];
std::array<int, 7> last[N][N][N][2];

#define updt(xx, yy) f xx > f yy + ret ? (f xx = f yy + ret, last xx = {i, j, k, o, da, db, dc}, 1) : 0

std::vector<int> ansa, ansb, ansc;
void get_answer(int i, int j, int k, int o) {
	// printf("get_answer(%d, %d, %d, %d)\n", i, j, k, o);
	if(!i && !j && !k && !o) return;
	auto l = last[i][j][k][o];
	ansa.push_back(l[4] == -1 ? (a[i] == '1' ? 2 : 1) : l[4]);
	ansb.push_back(l[5] == -1 ? (b[i] == '1' ? 2 : 1) : l[5]);
	ansc.push_back(l[6] == -1 ? (c[i] == '1' ? 2 : 1) : l[6]);
	get_answer(l[0], l[1], l[2], l[3]);
}

int main() {
	scanf("%[0-9]+%[0-9]=%[0-9]", a + 1, b + 1, c + 1);
	la = strlen(a + 1), lb = strlen(b + 1), lc = strlen(c + 1);
	std::reverse(a + 1, a + la + 1), std::reverse(b + 1, b + lb + 1), std::reverse(c + 1, c + lc + 1);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0][0] = 0;
	for(int i = 0; i <= la + 1; i++)
		for(int j = 0; j <= lb + 1; j++)
			for(int k = 0; k <= lc; k++) {
				int ret = (i <= la) + (j <= lb) + (k <= lc);
				for(int o = 0; o <= 1; o++)
					if(f[i][j][k][!o] > f[i][j][k][o] + ret)
						f[i][j][k][!o] = f[i][j][k][o] + ret, last[i][j][k][!o] = {i, j, k, o, -1, -1, -1};
				for(int o = 0; o <= 1; o++) {
					for(int da = 0; da <= 9; da++) if(!da || i <= la)
						for(int db = 0; db <= 9; db++) if(!db || j <= lb) {
							int dc = (da + db + o) % 10, o_ = (da + db + o) / 10;
							int i_ = i + (i < la && a[i + 1] == da + '0');
							int j_ = j + (j < lb && b[j + 1] == db + '0');
							int k_ = k + (k < lc && c[k + 1] == dc + '0');
							if(i == i_ && j == j_ && k == k_) continue;
							updt([i_][j_][k_][o_], [i][j][k][o]);
							if(i_ == la) updt([la + 1][j_][k_][o_], [i][j][k][o]);
							if(j_ == lb) updt([i_][lb + 1][k_][o_], [i][j][k][o]);
							if(i_ == la && j_ == lb) updt([la + 1][lb + 1][k_][o_], [i][j][k][o]);
						}
					// auto l = last[i][j][k][o];
					// printf("f[%d][%d][%d][%d] = %d, %d %d %d %d %d %d %d\n", i, j, k, o, f[i][j][k][o], l[0], l[1], l[2], l[3], l[4], l[5], l[6]);
				}
			}
	int ansi = la, ansj = lb;
	for(int i = la; i <= la + 1; i++)
		for(int j = lb; j <= lb + 1; j++)
			if(f[i][j][lc][0] < f[ansi][ansj][lc][0])
				ansi = i, ansj = j;
	get_answer(ansi, ansj, lc, 0);
	bool flag;
	flag = false; for(int x : ansa) flag |= x, flag ? putchar(x + '0') : 0;
	putchar('+');
	flag = false; for(int x : ansb) flag |= x, flag ? putchar(x + '0') : 0;
	putchar('=');
	flag = false; for(int x : ansc) flag |= x, flag ? putchar(x + '0') : 0;
	return 0;
}