#include <bits/stdc++.h>

const int N = 1000 + 5;
const int M = 1e6 + 5;

int n, m;
int a[N], b[M];

int main() {
	FILE *fin = fopen("../yacolorful.in", "r");
	FILE *fout = fopen("../yacolorful.out", "r");
	fscanf(fin, "%d", &n);
	for(int i = 1; i <= n; i++) fscanf(fin, "%d", &a[i]);
	fscanf(fout, "%d", &m);
	if(m > 550000) { printf("Wrong Answer L = %d which is greater than 5.5e5!\n", m); return 1; }
	for(int i = 1; i <= m; i++) fscanf(fout, "%d", &b[i]);
	for(int i = 1; i <= n; i++) if(b[i] != i) { printf("Wrong Answer b[%d] = %d which is not equal to %d!\n", i, b[i], i); return 1; }
	for(int i = 1; i <= n; i++) if(b[m - n + i] != a[i]) { printf("Wrong Answer b[L - n + %d] = %d which is not equal to a[%d]!\n", i, b[n - m + i], a[i]); return 1; }
	std::multiset<int> st;
	for(int i = 1; i <= n - 1; i++) st.insert(b[i]);
	for(int i = n; i <= m; i++) {
		st.erase(st.find(b[i - n + 1]));
		if(st.find(b[i]) != st.end()) { printf("Wrong Answer b[%d] appears in b[%d .. %d]!\n", i, i - n + 2, i - 1); return 1; }
		st.insert(b[i]);
	}
	printf("Accepted correct.\n");
	return 0;
}