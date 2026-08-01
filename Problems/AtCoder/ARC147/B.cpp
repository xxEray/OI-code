#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 400 + 5;

int n;
int a[N];

std::vector<std::pair<char, int>> op;

void move_to(int i, int j) {
	for(int k = i - 2; k >= j; k -= 2) {
		op.emplace_back('B', k);
		std::swap(a[k], a[k + 2]);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int c0 = 1, c1 = 2;
	for(int i = 1; i <= n; i += 2) if(!(a[i] & 1)) move_to(i, c0), c0 += 2;
	for(int i = 2; i <= n; i += 2) if(a[i] & 1) move_to(i, c1), c1 += 2;
	assert(c1 == c0 + 1);
	for(int i = 1; i < c0; i += 2) op.emplace_back('A', i), std::swap(a[i], a[i + 1]);
	for(int i = 1; i <= n; i += 2) {
		int id = i;
		for(int j = i; j <= n; j += 2) if(a[j] < a[id]) id = j;
		move_to(id, i);
	}
	for(int i = 2; i <= n; i += 2) {
		int id = i;
		for(int j = i; j <= n; j += 2) if(a[j] < a[id]) id = j;
		move_to(id, i);
	}
	for(int i = 1; i <= n; i++) assert(a[i] == i);
	assert(op.size() <= 100000);
	printf("%d\n", (int)op.size());
	for(auto p : op) printf("%c %d\n", p.first, p.second);
	return 0;
} /*
6
6 1 4 3 2 5

1 6 3 4 5 2
*/