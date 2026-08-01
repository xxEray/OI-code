#include <bits/stdc++.h>

typedef std::array<std::array<int, 19>, 19> State;

State now, last[2];
std::set<State> st;

int turn = 1, tot, game = 1;

int main() {
	int x, y;
	while(scanf("%d%d", &x, &y) == 2 && !(x == -1 && y == -1)) {
		tot++;
		if(x == 0 && y == 0) {
			
			turn = 3 - turn;
			continue;
		}

		turn = 3 - turn;
	}
	return 0;
}