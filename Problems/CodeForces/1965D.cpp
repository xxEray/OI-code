#include <bits/stdc++.h>

#undef assert
#define assert(condition) ((condition) ? (void)0 : (printf("Line #%d, Assertion '" #condition "' failed.", __LINE__), exit(0)))

const int N = 1000 + 5;

int n;

void substract(const std::vector<int> &vct, const std::vector<int> &nvct, std::vector<int> &to_return) {
	std::vector<int> result;
	for(int i = 0, j = 0; i < (int)vct.size(); i++) {
		if(j < (int)nvct.size() && vct[i] == nvct[j]) j++;
		else result.emplace_back(vct[i]);
	}
	to_return.swap(result);
}

inline int div2(int x) { assert(~x & 1); return x >> 1;}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		std::vector<int> vct;
		std::set<int> tin;
		for(int i = 1; i <= n * (n + 1) / 2 - 1; i++) {
			int x;
			scanf("%d", &x);
			x <<= 1;
			vct.emplace_back(x);
			if(tin.count(x)) tin.erase(x);
			else tin.emplace(x);
		}
		assert((int)tin.size() == (n + 1) / 2 - 1 || (int)tin.size() == (n + 1) / 2 + 1);
		std::sort(vct.begin(), vct.end());
		std::vector<int> vtin;
		for(int x : tin) vtin.emplace_back(x);
		std::deque<int> a;
		if(n & 1) a.emplace_back(vtin.front());
		else a.emplace_front(vtin.front() >> 1), a.emplace_back(vtin.front() >> 1);
		for(int i = 1; i < (int)vtin.size(); i++)
			a.emplace_front((vtin[i] - vtin[i - 1]) >> 1), a.emplace_back((vtin[i] - vtin[i - 1]) >> 1);
		int sz = a.size();
		// printf("a: "); for(int x : a) printf("%d ", x); puts("");
		// printf("vtin: "); for(int x : vtin) printf("%d ", x); puts("");
		std::vector<int> nvct;
		for(int i = 0; i < sz; i++) {
			int sum = 0;
			for(int j = i; j < sz; j++) sum += a[j], nvct.emplace_back(sum);
		}
		std::sort(nvct.begin(), nvct.end());
		if((int)vtin.size() < (n + 1) / 2) {
			substract(vct, nvct, nvct);
			assert(!nvct.empty());
			int val = nvct.back(), id = -1;
			for(int i = 0; i < sz; i++) {
				assert(val != a[i]);
				if(val > a[i]) val -= a[i];
				else { id = i; break; }
			}
			if(id == -1) {
				a.emplace_front(val), a.emplace_back(val);
				for(int x : a) printf("%d ", div2(x));
				puts("");
			} else {
				for(int i = 0; i < sz; i++)
					if(i == sz - id - 1 && i == id) {
						assert(a[i] > 2 * (a[i] - val));
						printf("%d %d %d ", div2(a[i] - val), div2(a[i] - 2 * (a[i] - val)), div2(a[i] - val));
					} else if(i == sz - id - 1) printf("%d %d ", div2(a[i] - val), div2(val));
					else if(i == id) printf("%d %d ", div2(val), div2(a[i] - val));
					else printf("%d ", div2(a[i]));
				puts("");
			}
		} else {
			int id = -1;
			substract(nvct, vct, nvct);
			assert(!nvct.empty());
			int val = nvct.back();
			for(int i = 0; i < sz; i++) {
				assert(val > 0);
				if(val == a[i]) { id = i; break; }
				else val -= a[i];
			}
			assert(id != -1);
			for(int i = 0; i < sz;)
				if(i + 1 == sz - id - 1 && i + 1 == id) printf("%d ", div2(a[i] + a[i + 1] + a[i + 2])), i += 3;
				else if(i + 1 == sz - id - 1 && i + 2 == id) printf("%d %d ", div2(a[i] + a[i + 1]), div2(a[i + 2] + a[i + 3])), i += 4;
				else if(i + 1 == sz - id - 1) printf("%d ", div2(a[i] + a[i + 1])), i += 2;
				else if(i == id) printf("%d ", div2(a[i] + a[i + 1])), i += 2;
				else printf("%d ", div2(a[i])), i++;
			puts("");
		}
	}
	return 0;
} /*
1
5
465676959 131136462 317693363 139560029 139560029 131136462 326116930 317693363 186556901 8423567 448829825 326116930 457253392 457253392
*/