// Don't kill monsters, you dolphin!
// Authored by black_trees from team CDoutLS: OPJ BLOCK

#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long

using namespace std;
using i64 = long long;

const int si = 2e5 + 10;

int n, k;
int a[si], b[si], d[si];

std::multiset<std::pair<int, int>> in;
std::multiset<std::pair<int, int>> out;

bool valid(int mid) {
	out.clear(), in.clear();
	for(int i = 1; i <= n; ++i) {
		a[i] = b[i];
	}

	for(int i = 1; i <= n; ++i) {
		while(a[i] > 0) {
			auto it = out.lower_bound(make_pair(i - d[i], -114514ll));
			if(it == out.end()) break;
			auto pir = *it;
			out.erase(it);
			int sub = min(a[i], pir.second);
			a[i] -= sub, pir.second -= sub;
			if(pir.second) {
				out.insert(pir);
			}
		}
		
		int tt = a[i];
		while(a[i] < mid && !in.empty()) {
			auto pir = *(in.begin());
			if(pir.first < i) return false;
			in.erase(pir);
			int sub = min(mid - a[i], pir.second);
			a[i] += sub, pir.second -= sub;
			if(pir.second) {
				in.insert(pir);
			}
		}

		tt = mid - a[i] + tt;
		while(tt && !in.empty()) {
			auto pir = *(in.begin());
			if(pir.first < i) return false;
			if(pir.first >= i + d[i]) break;
			in.erase(pir);
			int sub = min(pir.second, tt);
			pir.second -= sub, tt -= sub, a[i] += sub;
			if(pir.second) {
				in.insert(pir);
			}
		}

		if(a[i] < mid) {
			out.insert(make_pair(i, mid - a[i]));
		}	
		if(a[i] > mid) {
			in.insert(make_pair(i + d[i], a[i] - mid));
		}
	}
	return in.empty();
}

signed main() {

	cin.tie(0) -> sync_with_stdio(false);
	cin.exceptions(cin.failbit | cin.badbit);

	cin >> n; int mx = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i], b[i] = a[i], mx = max(mx, a[i]);
	}
	for(int i = 1; i <= n; ++i) {
		cin >> d[i];	
	}

	int l = 0, r = mx;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(valid(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;

	return 0;
}

