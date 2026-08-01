#include <bits/stdc++.h>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

const int U = (1 << 30) - 1;

int main() {
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution rnd(0, U);
	int T; cin >> T;
	while(T--) {
		int r1 = 0, r2 = 0;
		cout << 1 << endl;
		cin >> r1;
		if(r1 > 1) {
			int x = r1 & ~1;
			x = x & -x; // lowbit
			cout << 0 << ' ' << x << endl;
			cin >> r2;
			if(r2 & x) cout << 0 << endl;
			else cout << 1 << endl;
		} else {
			int x = rnd(mt), y = rnd(mt);
			x &= ~1, y |= 1;
			cout << x << ' ' << y << endl;
			cin >> r2;
			if(r2 == x) cout << 0 << endl;
			else if(r2 == y) cout << 1 << endl;
			else {
				if((r1 & 1) == (r2 & 1)) cout << 0 << endl;
				else cout << 1 << endl;
			}
		}
	}
	return 0;
}