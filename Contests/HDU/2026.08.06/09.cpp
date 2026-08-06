// auto input
#include <bits/stdc++.h>
// #include "stl_printer.h"
using std::cin;
using std::cout;

const int N = (1 << 18) + 5;

int n;
int a[N];

int nil;
int nxt[N];
int f(int bit, int hd) { // [bg, ed) 左闭右开链表
	if(hd == nil) return 0;
	if(bit == -1) return 1;
	int hdl[2] = {nil, nil}, tll[2] = {nil, nil}, hdr[2] = {nil, nil}, tlr[2] = {nil, nil};
	// std::vector<int> tmp;
	for(int i = hd; i != nil; i = nxt[i]) {
		// tmp.emplace_back(i);
		if(~i >> bit & 1) { // left segment
			int high = a[i] >> bit & 1;
			if(hdl[high] == nil) hdl[high] = tll[high] = i;
			else nxt[tll[high]] = i, tll[high] = i;
		} else {
			int high = a[i] >> bit & 1;
			if(hdr[high] == nil) hdr[high] = tlr[high] = i;
			else nxt[tlr[high]] = i, tlr[high] = i;
		}
	}
	nxt[tll[0]] = nil, nxt[tll[1]] = nil;
	nxt[tlr[0]] = nil, nxt[tlr[1]] = nil;
	int ans = std::max(f(bit - 1, hdl[0]) + f(bit - 1, hdr[1]), f(bit - 1, hdl[1]) + f(bit - 1, hdr[0]));
	// printf("f(%d, [%s]) = %d\n", bit, tostring(tmp).c_str(), ans);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 0; i < (1 << n); i++) cin >> a[i];
		for(int i = 0; i < (1 << n); i++) nxt[i] = i + 1;
		nil = (1 << n), nxt[(1 << n)] = nil;
		cout << f(n - 1, 0) << '\n';
	}
	return 0;
} /*
3
3
0 1 2 3 7 6 5 4
3
5 7 4 3 1 0 6 2
4
9 11 13 7 5 14 8 4 6 0 12 15 1 3 10 2
*/