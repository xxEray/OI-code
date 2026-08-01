#include <cstdio>
#include <algorithm>
#include <map>
#include <cassert>

const int N = 5e5 + 5;

struct Point { int x, y; } a[N];
struct Line { int v, d; };
int n;

std::map<int, int> row, col, dia1, dia2;

Line make_line(Point p, int d) {
	Line x;
	x.d = d;
	if(d == 1) x.v = p.x;
	else if(d == 2) x.v = p.y;
	else if(d == 3) x.v = p.x + p.y;
	else if(d == 4) x.v = p.x - p.y;
	return x;
}

bool is_on(Point p, Line y) {
	if(y.d == 1) return y.v == p.x;
	else if(y.d == 2) return y.v == p.y;
	else if(y.d == 3) return y.v == p.x + p.y;
	else if(y.d == 4) return y.v == p.x - p.y;
	assert(false);
	return false;
}

Point intersect(Line x, Line y) {
	if(x.d > y.d) std::swap(x, y);
	if(x.d == 1 && y.d == 2) return {x.v, y.v};
	else if(x.d == 1 && y.d == 3) return {x.v, y.v - x.v};
	else if(x.d == 1 && y.d == 4) return {x.v, x.v - y.v};
	else if(x.d == 2 && y.d == 3) return {y.v - x.v, x.v};
	else if(x.d == 2 && y.d == 4) return {x.v + y.v, x.v};
	else if(x.d == 3 && y.d == 4) return {(x.v + y.v) / 2, (x.v - y.v) / 2};
	assert(false);
	return {0, 0};
}

bool check(Point p) {
	bool flag = true;
	for(int i = 1; i <= n; i++) {
		bool fl = false;
		for(int d = 1; d <= 4; d++)
			fl |= is_on(a[i], make_line(p, d));
		flag &= fl;
	}
	return flag;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		row.clear(), col.clear(), dia1.clear(), dia2.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d%d", &a[i].x, &a[i].y);
			a[i].x *= 2, a[i].y *= 2;
			row[a[i].x]++, col[a[i].y]++, dia1[a[i].x + a[i].y]++, dia2[a[i].x - a[i].y]++;
		}
		Line x, y;
		int cnt = 0;
		for(auto v : row) if(v.second >= 4 && cnt < 2) { (cnt ? y : x) = {v.first, 1}; cnt++; }
		for(auto v : col) if(v.second >= 4 && cnt < 2) { (cnt ? y : x) = {v.first, 2}; cnt++; }
		for(auto v : dia1) if(v.second >= 4 && cnt < 2) { (cnt ? y : x) = {v.first, 3}; cnt++; }
		for(auto v : dia2) if(v.second >= 4 && cnt < 2) { (cnt ? y : x) = {v.first, 4}; cnt++; }
		if(cnt == 2) {
			if(x.d == y.d) puts("NO");
			else if(check(intersect(x, y))) puts("YES");
			else puts("NO");
		} else if(cnt == 1) {
			int ind = 0;
			for(int i = 1; i <= n; i++) if(!is_on(a[i], x)) { ind = i; break; }
			if(ind == 0) puts("YES");
			else {
				bool flag = false;
				for(int d = 1; d <= 4; d++) if(d != x.d && check(intersect(make_line(a[ind], d), x))) { puts("YES"); flag = true; break; }
				if(!flag) puts("NO");
			}
		} else {
			if(n > 12) { puts("NO"); continue; }
			bool flag = false;
			for(int i = 1; i <= n && !flag; i++) for(int j = 1; j <= n && !flag; j++)
				for(int d1 = 1; d1 <= 4 && !flag; d1++) for(int d2 = 1; d2 <= 4; d2++) if(d1 != d2)
					if(check(intersect(make_line(a[i], d1), make_line(a[j], d2)))) { puts("YES"); flag = true; break; }
			if(!flag) puts("NO");
		}
	}
	return 0;
}