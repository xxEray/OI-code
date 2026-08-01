#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
using std::string;
using std::cin;
using std::cout;

const int N = 1000 + 5;
const int CS = 13;

string s[N];
int n;

int count(string str) {
	int cnt[20] = {};
	for(char c : str) cnt[c]++;
	int tot = 0;
	for(int i = 1; i <= CS; i++) tot += cnt[i] > 0;
	return tot;
}

char char_of[] = " 0123456789+*=";

int p[20], q[20];
bool digit(char c) { return '0' <= c && c <= '9'; }
bool calc(int id) {
	if(!q[CS]) return false;
	char str[20] = {};
	int len = s[id].size();
	for(int i = 1; i <= len; i++) str[i] = char_of[p[s[id][i - 1]]];
	int last = 0, now = 1, current = 0;
	int i;
	for(i = 1; i <= len; i++) {
		if(str[i] == '+') {
			if(!digit(str[i - 1])) return false;
			last += now * current, now = 1, current = 0;
		} else if(str[i] == '*') {
			if(!digit(str[i - 1])) return false;
			now *= current, current = 0;
		} else if(str[i] == '=') {
			if(!digit(str[i - 1])) return false;
			break;
		} else {
			if(str[i] == '0' && !digit(str[i - 1]) && digit(str[i + 1])) return false;
			current = current * 10 + str[i] - '0';
		}
	}
	int lvalue = last + now * current;
	last = 0, now = 1, current = 0;
	for(i++; i <= len; i++) {
		if(str[i] == '+') {
			if(!digit(str[i - 1])) return false;
			last += now * current, now = 1, current = 0;
		} else if(str[i] == '*') {
			if(!digit(str[i - 1])) return false;
			now *= current, current = 0;
		} else if(str[i] == '=') return false;
		else {
			if(str[i] == '0' && !digit(str[i - 1]) && digit(str[i + 1])) return false;
			current = current * 10 + str[i] - '0';
		}
	}
	if(!digit(str[len])) return false;
	int rvalue = last + now * current;
	// if(lvalue == rvalue)
	// 	printf("Correct: %s\n", str + 1);
	return lvalue == rvalue;
}

void print() {
	puts("");
	for(int i = 1; i <= n; i++) {
		for(char c : s[i])
			printf("%c", char_of[p[c]]);
		puts("");
	}
}

int ans[20];

bool appear[20];
bool exist[N][20], can_equal[20], can_op[20];
void dfs(int id, int t) {
	if(id == n + 1) {
		int cnt = 0;
		for(int i = 1; i <= CS; i++) cnt += (p[i] == 0);
		int tp = 0, tq = 0;
		if(cnt == 1) {
			for(int i = 1; i <= CS; i++) if(p[i] == 0) tp = i;
			for(int i = 1; i <= CS; i++) if(q[i] == 0) tq = i;
			p[tp] = tq, q[tq] = tp;
		}
		// print();
		for(int i = 1; i <= CS; i++)
			if(ans[i] > 0 && ans[i] != p[i]) ans[i] = -1;
			else if(ans[i] != -1) ans[i] = p[i];
		if(cnt == 1) p[tp] = 0, q[tq] = 0;
		return;
	}
	// assert(p[5] != 13 || p[9] <= 3);
	for(int i = t; i <= CS; i++) if(exist[id][i] && !p[i]) {
		for(int j = 1; j <= CS; j++) if(!q[j] && (j != 13 || can_equal[i]) && ((j != 11 && j != 12) || can_op[i])) {
			p[i] = j, q[j] = i;
			dfs(id, i + 1);
			p[i] = 0, q[j] = 0;
			if(id <= n - 1) {
				bool flag = false;
				// for(int k = 1; k <= CS; k++) printf("ans[%d] = %d, p[%d] = %d\n", k, ans[k], k, p[k]);
				for(int k = 1; k <= CS; k++) flag |= !(ans[k] == -1 || (ans[k] && ans[k] == p[k]) || !appear[k]);
				if(!flag) return;
			}
		}
		return;
	}
	if(!calc(id)) return;
	dfs(id + 1, 1);
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> s[i];
	for(int i = 1; i <= n; i++) for(char &c : s[i]) c -= 'a' - 1;
	std::sort(s + 1, s + n + 1, [&](string a, string b) { return count(a) < count(b); });
	for(int i = 1; i <= n; i++) for(char c : s[i]) exist[i][c] = true;
	for(int i = 1; i <= CS; i++) {
		bool flag = true;
		for(int j = 1; j <= n; j++) {
			int tot = 0;
			for(char c : s[j]) tot += c == i;
			flag &= tot == 1 && s[j].front() != i && s[j].back() != i;
		}
		can_equal[i] = flag;
	}
	for(int i = 1; i <= CS; i++) {
		bool flag = true;
		for(int j = 1; j <= n; j++) {
			for(int k = 0; k < (int)s[j].size() - 1; k++)
				flag &= (s[j][k] != i || s[j][k + 1] != i);
			flag &= s[j].front() != i && s[j].back() != i;
		}
		can_op[i] = flag;
	}
	for(int i = 1; i <= n; i++) for(char c : s[i]) appear[c] = true;
	int cnt = 0;
	for(int i = 1; i <= CS; i++) cnt += appear[i];
	if(cnt == 12) for(int i = 1; i <= CS; i++) appear[i] = true;
	dfs(1, 1);
	bool any = false;
	for(int i = 1; i <= CS; i++) if(ans[i] > 0) printf("%c%c\n", (char)(i + 'a' - 1), char_of[ans[i]]), any = true;
	if(!any) puts("noway");
	return 0;
}