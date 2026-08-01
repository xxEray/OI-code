#include <cstdio>
#include <algorithm>

typedef unsigned long long byte;

const int N = 500 + 5;

int tr[N], tc[N];
int r[N], c[N];
int n;

int cntr[2][2], cntc[2][2];
byte ans[N][N], tmp[N][2];
int t[N][N];

bool solve() {
	if(cntr[0][1] + cntr[1][0] && cntc[0][1] + cntc[1][0]) { // 1
		if((cntr[0][1] && cntr[1][0]) ||
		   (cntc[0][1] && cntc[1][0]) ||
		   (cntr[0][1] && cntc[1][0]) ||
		   (cntc[0][1] && cntr[1][0])) return false;
		else if(cntr[0][1] && cntc[0][1]) {
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					t[i][j] = ((tr[i] == 0 && r[i] == 1) || (tc[j] == 0 && c[j] == 1) ? 1 : 0);
		} else {
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					t[i][j] = ((tr[i] == 1 && r[i] == 0) || (tc[j] == 1 && c[j] == 0) ? 0 : 1);
		}
	} else if(cntr[0][1] + cntr[1][0] == 0 && cntc[0][1] + cntc[1][0] == 0) { // 4
		if(n == 1) {
			if(r[1] != c[1]) return false;
			else t[1][1] = r[1];
		} else {
			for(int i = 2; i <= n; i++) t[i][1] = r[i], t[2][i] = c[i];
			t[1][2] = r[1], t[1][1] = c[1];
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(t[i][j] == -1) t[i][j] = 0;
		}
	} else if(cntr[1][0] + cntr[0][1]) { // 2
		if(cntr[1][0] && cntr[0][1]) { // 2.1
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					t[i][j] = r[i];
		} else if(cntr[0][1]) { // 2.2
			// preprocess
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(tr[i] == 0 && r[i] == 1)
						t[i][j] = 1;
			if(!cntc[0][0] || cntr[0][0]) { // 2.2.1 & 2.2.2
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						t[i][j] = r[i];
			} else if(cntr[1][1] >= 2) { // 2.2.3
				int tmp = 1;
				for(int i = 1; i <= n; i++)
					if(tr[i] == 1 && r[i] == 1) {
						for(int j = 1; j <= n; j++) t[i][j] = (j == tmp ? 1 : 0);
						tmp++;
						if(tmp == 3) break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = r[i];
			} else if(cntr[1][1] && cntc[0][0] < n) { // 2.2.4
				for(int i = 1; i <= n; i++)
					if(tr[i] == 1 && r[i] == 1) {
						for(int j = 1; j <= n; j++) t[i][j] = (tc[j] == 0 && c[j] == 0 ? 0 : 1);
						break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = r[i];
			} else return false; // 2.2.5
		} else if(cntr[1][0]) { // 2.3
			// preprocess
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(tr[i] == 1 && r[i] == 0)
						t[i][j] = 0;
			if(!cntc[1][1] || cntr[1][1]) { // 2.3.1 & 2.3.2
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						t[i][j] = r[i];
			} else if(cntr[0][0] >= 2) { // 2.3.3
				int tmp = 1;
				for(int i = 1; i <= n; i++)
					if(tr[i] == 0 && r[i] == 0) {
						for(int j = 1; j <= n; j++) t[i][j] = (j == tmp ? 0 : 1);
						tmp++;
						if(tmp == 3) break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = r[i];
			} else if(cntr[0][0] && cntc[1][1] < n) { // 2.3.4
				for(int i = 1; i <= n; i++)
					if(tr[i] == 0 && r[i] == 0) {
						for(int j = 1; j <= n; j++) t[i][j] = (tc[j] == 1 && c[j] == 1 ? 1 : 0);
						break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = r[i];
			} else return false; // 2.3.5
		}
	} else if(cntc[1][0] + cntc[0][1]) { // 3
		if(cntc[1][0] && cntc[0][1]) { // 3.1
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					t[i][j] = c[j];
		} else if(cntc[0][1]) { // 3.2
			// preprocess
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(tc[j] == 0 && c[j] == 1)
						t[i][j] = 1;
			if(!cntr[0][0] || cntc[0][0]) { // 3.2.1 & 3.2.2
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						t[i][j] = c[j];
			} else if(cntc[1][1] >= 2) { // 3.2.3
				int tmp = 1;
				for(int j = 1; j <= n; j++)
					if(tc[j] == 1 && c[j] == 1) {
						for(int i = 1; i <= n; i++) t[i][j] = (i == tmp ? 1 : 0);
						tmp++;
						if(tmp == 3) break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = c[j];
			} else if(cntc[1][1] && cntr[0][0] < n) { // 3.2.4
				for(int j = 1; j <= n; j++)
					if(tc[j] == 1 && c[j] == 1) {
						for(int i = 1; i <= n; i++) t[i][j] = (tr[i] == 0 && r[i] == 0 ? 0 : 1);
						break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = c[j];
			} else return false; // 3.2.5
		} else if(cntc[1][0]) { // 3.3
			// preprocess
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(tc[j] == 1 && c[j] == 0)
						t[i][j] = 0;
			if(!cntr[1][1] || cntc[1][1]) { // 3.3.1 & 3.3.2
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						t[i][j] = c[j];
			} else if(cntc[0][0] >= 2) { // 3.3.3
				int tmp = 1;
				for(int j = 1; j <= n; j++)
					if(tc[j] == 0 && c[j] == 0) {
						for(int i = 1; i <= n; i++) t[i][j] = (i == tmp ? 0 : 1);
						tmp++;
						if(tmp == 3) break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = c[j];
			} else if(cntc[0][0] && cntr[1][1] < n) { // 3.3.4
				for(int j = 1; j <= n; j++)
					if(tc[j] == 0 && c[j] == 0) {
						for(int i = 1; i <= n; i++) t[i][j] = (tr[i] == 1 && r[i] == 1 ? 1 : 0);
						break;
					}
				for(int i = 1; i <= n; i++)
					for(int j = 1; j <= n; j++)
						if(t[i][j] == -1)
							t[i][j] = c[j];
			} else return false; // 3.3.5
		}
	}
	for(int i = 1; i <= n; i++)  {
		int ret = t[i][1];
		for(int j = 2; j <= n; j++) ret = (tr[i] ? ret | t[i][j] : ret & t[i][j]);
		if(ret != r[i]) return false;
	}
	for(int j = 1; j <= n; j++)  {
		int ret = t[1][j];
		for(int i = 2; i <= n; i++) ret = (tc[j] ? ret | t[i][j] : ret & t[i][j]);
		if(ret != c[j]) return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &tr[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &tc[i]);
	for(int i = 1; i <= n; i++) scanf("%llu", &tmp[i][0]);
	for(int i = 1; i <= n; i++) scanf("%llu", &tmp[i][1]);
	for(int k = 0; k <= 64; k++) {
		for(int i = 1; i <= n; i++) r[i] = (int)(tmp[i][0] >> k & 1);
		for(int j = 1; j <= n; j++) c[j] = (int)(tmp[j][1] >> k & 1);
		cntr[0][0] = cntr[0][1] = cntr[1][0] = cntr[1][1] = 0;
		cntc[0][0] = cntc[0][1] = cntc[1][0] = cntc[1][1] = 0;
		for(int i = 1; i <= n; i++) cntr[tr[i]][r[i]]++;
		for(int i = 1; i <= n; i++) cntc[tc[i]][c[i]]++;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				t[i][j] = -1;
		if(solve() == false) { puts("-1"); return 0; }
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				ans[i][j] |= (byte)t[i][j] << k;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%llu%c", ans[i][j], (j == n ? '\n' : ' '));
	return 0;
}