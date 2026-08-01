#include <cstdio>
#include <algorithm>
#include <vector>

int a[100000];

int found, tried;

int ans[100000], cnt;
std::vector<std::pair<int, int>> final_ans;

void BinarySearch(int x, int n, int* A)
{
    int p = 0;     // Left border of the search
    int q = n - 1; // Right border of the search
    int L = 0;     // Comparison counter
    while (p <= q) {
        int i = (p + q) / 2;
		// printf("l = %d, r = %d\n", p, q);
        ++L;
        if (A[i] == x) {
			if(i == found && L == tried) ans[++cnt] = n;
            return;
        }
        if (x < A[i])
            q = i - 1;
        else
            p = i + 1;
    }
}

int main() {
	scanf("%d%d", &found, &tried);
	for(int i = 1; i <= 10000; i++) a[i] = i;
	for(int i = found + 1; i <= 10000; i++) BinarySearch(found, i, a);
	for(int i = 1; i <= cnt;) {
		int st = ans[i], ed;
		while(ans[i + 1] == ans[i] + 1) i++;
		ed = ans[i];
		final_ans.push_back({st, ed});
		i++;
	}
	printf("%d\n", (int)final_ans.size());
	for(auto p : final_ans) printf("%d %d\n", p.first, p.second);
	return 0;
}