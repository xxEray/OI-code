#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using std::string;
using std::vector;

const int N = 15 + 4;

char a[N][N];
int t[N][N];
int n, m;

bool common = true;
char more, winner;

bool check_count() {
	int cntO = 0, cntX = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i][j] == 'O') cntO++;
			else if(a[i][j] == 'X') cntX++;
	if(std::abs(cntO - cntX) > 1) return false;
	if(std::abs(cntO - cntX) == 1) more = (cntO > cntX ? 'O' : 'X');
	return true;
}

bool chk(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
const int dir[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
bool both_win() {
	bool winO = false, winX = false;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '.') continue;
			for(int r = 0; r < 4; r++) {
				int di = dir[r][0], dj = dir[r][1];
				bool flag = true;
				for(int k = 1; k <= 4; k++) flag &= (!chk(i + di * k, j + dj * k) ? false : a[i][j] == a[i + di * k][j + dj * k]);
				if(flag) a[i][j] == 'X' ? winX = true : winO = true;
			}
		}
	return winO && winX;
}

bool check_repeat() {
	int cnt = 0;
	int cnt6_9 = 0, x6_9 = 0, y6_9 = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '.') continue;
			for(int r = 0; r < 4; r++) {
				int di = dir[r][0], dj = dir[r][1], k;
				if(a[i - di][j - dj] == a[i][j]) continue;
				for(k = 1; chk(i + di * k, j + dj * k); k++) if(a[i + di * k][j + dj * k] != a[i][j]) break;
				int c = k;
				if(c < 5) continue;
				if(c > 9) return false;
				if(c != 5) cnt6_9++, x6_9 = i + di * 4, y6_9 = j + dj * 4;
				winner = a[i][j];
				for(k = 0; k <= c; k++) cnt += (++t[i + di * k][j + dj * k] == 2);
			}
		}
	if(cnt > 1) return false;
	else if(cnt == 1) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(t[i][j] > 1)
					a[i][j] = '.';
	} else if(cnt6_9 == 1) {
		a[x6_9][y6_9] = '.';
	} else common = false;
	return true;
}

bool check_five() {
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '.') continue;
			for(int r = 0; r < 4; r++) {
				int di = dir[r][0], dj = dir[r][1];
				bool flag = true;
				for(int k = 1; k <= 4; k++) flag &= (!chk(i + di * k, j + dj * k) ? false : a[i][j] == a[i + di * k][j + dj * k]);
				if(flag) cnt++;
			}
		}
	return common ? cnt <= 0 : cnt <= 1;
}

bool full() {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i][j] == '.')
				return false;
	return true;
}

class GomokuBoardChecker {
public:
	string check(vector<string> board) {
		n = board.size(), m = board[0].size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = board[i - 1][j - 1];
		if(!check_count()) return "INVALID";
		if(both_win()) return "INVALID";
		if(!check_repeat()) return "INVALID";
		if(!check_five()) return "INVALID";
		if(winner) return more && winner != more ? "INVALID" : (winner == 'O' ? "O WON" : "X WON");
		if(full()) return "DRAW";
		return "IN PROGRESS";
	}
};