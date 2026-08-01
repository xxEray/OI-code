#include <cstdio>
#include <map>

const int MAXNUM = 1e3 + 5;

int gcd(int a, int b) { return a % b ? gcd(b, a % b) : b; }
std::pair<int, int> trim(int x, int y) {
	int g = gcd(std::abs(x), std::abs(y));
	x /= g, y /= g;
	return std::make_pair(x, y);
}

std::map<std::pair<int, int>, int> mp;

int main() {
	int n;
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x, y;
		std::scanf("%d%d", &x, &y);
		if(mp.find(trim(x, y)) != mp.end() && mp[trim(x, y)] == 2) { std::puts("Yes"); return 0; }
		else mp[trim(x, y)]++;
	}
	std::printf("No");
	return 0;
} /*
1 0
2 2
3 4
*/