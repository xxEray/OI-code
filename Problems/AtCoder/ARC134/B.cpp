#include <cstdio>
#include <algorithm>
#include <deque>
#include <cassert>

const int N = 2e5 + 5;

char s[N];
int n;

std::deque<int> pos[300];

int main() {
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; i++) pos[s[i]].push_back(i);
	int first = 0, last = n + 1;
	int j = 'a';
	while(first < last) {
		do {
			while(j <= 'z' && pos[j].empty()) {
				j++;
				while(!pos[j].empty() && pos[j].back() > last) assert(pos[j].back() != last), pos[j].pop_back();
				while(!pos[j].empty() && pos[j].front() <= first) pos[j].pop_front();
			}
			if(j > 'z') break;
			while(!pos[j].empty() && s[++first] == j) assert(first <= pos[j].back() && s[first] >= j), pos[j].pop_front();
		} while(j <= 'z' && pos[j].empty());
		if(j > 'z') break;
		last = pos[j].back();
		if(first >= last) break;
		std::swap(s[first], s[last]);
		pos[j].pop_back();
		// printf("swap([%d], [%d])\n", first, last);
		assert(pos[j].empty() || pos[j].back() < last);
	}
	for(int i = 1; i <= n; i++) putchar(s[i]);
	return 0;
} /*

5
cceda
*/