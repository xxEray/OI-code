// TopCoder 1684 Posters
// 676 ms  https://vjudge.net/solution/37566473
#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

const int N = 5 + 2;
const int M = 100 + 5;

int n, m, K;
struct Node { int r, c; } a[M], tmp[M]; // tmp 输入矩形，a 按照排列重排后的矩形

// up bound, down bound, left bound, right bound（原谅我英语不好）
// 分别记录第 i 个矩形的上下左右边界（i=0 时记录网格边框）
int ub[N], db[N], lb[N], rb[N];

int p[N], sum[N]; // p 排列，sum 面积后缀和

int ans = 0; // 答案
void dfs(int id, int ret) {
	if(id == K + 1) { ans = std::max(ans, ret); return; } // 更新答案
	if(ret + sum[id] <= ans) return; // 可行性剪枝
	for(int i = 0; i < id; i++) for(int ki = 0; ki <= 1; ki++) { // ki=0 贴着矩形 i 的下面；ki=1 贴着矩形 i 的上面
		// 计算 id 的上下边界
		if(ki == 0) ub[id] = db[i] + 1;
		else ub[id] = ub[i] - a[id].r;
		db[id] = ub[id] + a[id].r - 1;
		if(ub[id] < 1 || db[id] > n) continue;
		for(int j = 0; j < id; j++)  for(int kj = 0; kj <= 1; kj++) { // kj=0 贴着矩形 i 的右边；kj=1 贴着矩形 i 的左边
			// 计算 id 的左右边界
			if(kj == 0) lb[id] = rb[j] + 1;
			else lb[id] = lb[j] - a[id].c;
			rb[id] = lb[id] + a[id].c - 1;
			if(lb[id] < 1 || rb[id] > m) continue;
			// 容斥原理计算答案
			int oldret = ret, U = (1 << (id - 1)) - 1; // U 全集
			for(int s = 0; s <= U; s++) {
				int l = lb[id], r = rb[id], u = ub[id], d = db[id];
				for(int o = 1; o < id; o++) if(s >> (o - 1) & 1)
					l = std::max(l, lb[o]), r = std::min(r, rb[o]), u = std::max(u, ub[o]), d = std::min(d, db[o]); // 求交集的上下左右边界
				ret += (__builtin_popcount(s) & 1 ? -1 : 1) * std::max(r - l + 1, 0) * std::max(d - u + 1, 0);
			}
			// 递归搜索
			dfs(id + 1, ret);
			ret = oldret;
		}
	}
}

class Posters {
public:
	int maxCover(int width, int height, vector<int> pWidth, vector<int> pHeight) {
		n = height, m = width, K = pWidth.size();
		for(int i = 1; i <= K; i++) tmp[i].r = pHeight[i - 1], tmp[i].c = pWidth[i - 1];
		// 特判 K<=1
		if(K == 0) return 0;
		if(K == 1) return tmp[1].r * tmp[1].c;
		// 特殊处理网格边框，这里的初值与上面「计算 id 上下/左右边界」部分对应
		ub[0] = n + 1, db[0] = 0, lb[0] = m + 1, rb[0] = 0;
		// 枚举排列
		for(int i = 1; i <= K; i++) p[i] = i;
		do {
			if(p[1] > p[2]) continue; // 对称性剪枝
			for(int i = 1; i <= K; i++) a[i] = tmp[p[i]]; // 处理重排后的矩形
			for(int i = K; i >= 1; i--) sum[i] = sum[i + 1] + a[i].r * a[i].c; // 计算面积后缀和
			ub[1] = 1, db[1] = a[1].r, lb[1] = 1, rb[1] = a[1].c; // 放置第一个矩形
			ub[2] = n - a[2].r + 1, db[2] = n, lb[2] = m - a[2].c + 1, rb[2] = m; // 放置第二个矩形
			dfs(3, a[1].r * a[1].c + a[2].r * a[2].c -  std::max(db[1] - ub[2] + 1, 0) * std::max(rb[1] - lb[2] + 1, 0)); // 计算前两个矩形覆盖的面积，并递归
		} while(std::next_permutation(p + 1, p + K + 1));
		return ans; // 完结撒花~
	}
};