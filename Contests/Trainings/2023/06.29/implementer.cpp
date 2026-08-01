#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "D.h"
namespace panole
{
	const int N = 5005;
	int n, i, j, x, y;
	std::vector<int>e[N];
	int f[20][N], eucnt, lo[N], id[N], ri[N];
	void dfs(int u, int fa)
	{
		f[0][id[u] = ++eucnt] = u;
		for (int i = 0; i < e[u].size(); ++i)if (e[u][i] != fa)dfs(e[u][i], u), f[0][++eucnt] = u; ri[u] = eucnt;
	}
	inline int cmp(int x, int y) {return id[x] < id[y] ? x : y;}
	inline int lca(int x, int y)
	{
		x = id[x]; y = id[y]; int l = lo[y - x + 1];
		return cmp(f[l][x], f[l][y - (1 << l) + 1]);
	}
	std::vector<std::pair<int, int> >E;
	inline void ini()
	{
		for (i = 2; i < N; ++i)lo[i] = lo[i >> 1] + 1;
		scanf("%d", &n);
		for (i = 1; i < n; ++i)scanf("%d%d", &x, &y), e[x].push_back(y), e[y].push_back(x),
				E.push_back(std::make_pair(x, y));
		dfs(1, 0);
		for (i = 1; 1 << i <= eucnt; ++i)
			for (j = 1; j + (1 << i) - 1 <= eucnt; ++j)f[i][j] = cmp(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
	}
	inline bool isanc(int x, int y) {return id[x] <= id[y] && id[y] <= ri[x];}
	int S1, S2;
	inline bool ask(std::vector<int>a, int x)
	{
		S1++; S2 += a.size();
		if (a.empty())
		{
			// puts("anjfsfnksdf");
			puts("a");
			exit(0);
		}
		int i, u = a[0], v = a[0];
		bool flag = 0;
		if (x < 1 || x > n)
		{
			// puts("anjfsfnksdf");
			puts("b");
			exit(0);
		}
		for (i = 0; i < a.size(); ++i)
		{
			if (a[i] < 1 || a[i] > n)
			{
				// puts("anjfsfnksdf");
				puts("c");
				exit(0);
			}
			if (id[a[i]] < id[u])u = a[i];
			if (id[v] < id[a[i]])v = a[i];
			if (isanc(x, a[i]))flag = 1;
		}
		u = lca(u, v);
		return !isanc(u, x) ? 0 : flag;
	}
	inline void check(std::vector<std::pair<int, int> >a)
	{
		int i;
		if (a.size() != n - 1)
		{
			// puts("anjfsfnksdf");
			puts("d");
			exit(0);
		}
		// puts("User out:");
		// for(auto &p : a) printf("%d %d\n", p.first, p.second);
		for (i = 0; i < n - 1; ++i)
		{
			if (a[i].first > a[i].second)std::swap(a[i].first, a[i].second);
			if (E[i].first > E[i].second)std::swap(E[i].first, E[i].second);
		}
		std::sort(a.begin(), a.end());
		std::sort(E.begin(), E.end());
		for (i = 0; i < n - 1; ++i)if (a[i] != E[i])
			{
				// puts("anjfsfnksdf");
				puts("e");
				exit(0);
			}
		// puts("anjfsfnksdf");
		printf("f %d %d (%d)\n", S1, S2, std::min(n * 2200 / S1, 100));
	}
}
bool ask(std::vector<int>a, int x) {return panole::ask(a, x);}
std::vector<std::pair<int, int> >work(int n);

int main()
{
	panole::ini();
	panole::check(work(panole::n));
	return 0;
}
