#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int N = 2e5 + 5;

int n;
string a[N];

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, [](string x, string y) { return x.size() > y.size(); });
	int p = 0, q = 1;
	for(int j = 1; j <= 3; j++) {
		while(q <= n && a[q].size() >= a[j].size()) q++;
		if(q - 1 <= 3) p = q - 1;
		else break;
	}
	std::sort(a + p + 1, a + q, [](string x, string y) { return x + y > y + x; });
	std::sort(a + 1, a + 3 + 1, [](string x, string y) { return x + y > y + x; });
	for(int i = 1; i <= 3; i++) cout << a[i];
	cout << '\n';
	return 0;
}