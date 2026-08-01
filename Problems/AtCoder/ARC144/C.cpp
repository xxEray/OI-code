#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 3e5 + 5;

std::vector<int> solve1(int n, int K) {
	std::vector<int> v;
	for(int i = 1; i <= n; i++) v.push_back(i);
	std::vector<int> ans{n + 1};
	do {
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (std::abs(v[i - 1] - i) >= K);
		if(flag) ans = std::min(ans, v);
	} while(std::next_permutation(v.begin(), v.end()));
	return ans == (std::vector<int>){n + 1} ? (std::vector<int>){-1} : ans;
}

std::vector<int> solve2(int n, int K) {
	std::vector<int> a;
	for(int i = K + 1; i <= n; i++) a.push_back(i);
	for(int i = 1; i <= K; i++) a.push_back(i);
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= (std::abs(a[i - 1] - i) >= K);
	return flag ? a : (std::vector<int>){-1};
}

int main() {
	// for(int n = 1; n <= 10; n++) for(int K = 1; K <= n - 1; K++)
	// 	if(solve1(n, K) != solve2(n, K)) printf("n = %d, K = %d\n", n, K);
	// return 0;
	int n = 9, K = 3;
	auto v1 = solve1(n, K), v2 = solve2(n, K);
	printf("n = %d, K = %d\n", n, K);
	for(auto x : v1) printf("%d ", x);
	puts("");
	for(auto x : v2) printf("%d ", x);
	return 0;
} /*
1 2 3 4 5 6  7 8 9 10
4 5 6 1 8 9 10 2 3  7

1 2 3 4 5 6 7 8 9 10
      1             |

1 2 3 5 6 7 8 9 10
4 5 6 8 9 10 2 3 7

n = 4, K = 1
n = 5, K = 1
n = 6, K = 1
n = 7, K = 1
n = 7, K = 2
n = 8, K = 1
n = 8, K = 2
n = 9, K = 1
n = 9, K = 2
n = 10, K = 1
n = 10, K = 2
n = 10, K = 3
*/