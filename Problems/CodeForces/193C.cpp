#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cassert>

const double eps = 1e-7;
const int INF = 0x3f3f3f3f;

int diff[5][5];

double matrix[8][9] = {{},
	{0, /* coefficient */ 0, 0, 0, 1, 1, 1, 1, /* constant */ 0},
	{0, /* coefficient */ 0, 1, 1, 0, 0, 1, 1, /* constant */ 0},
	{0, /* coefficient */ 1, 0, 1, 0, 1, 0, 1, /* constant */ 0},
	{0, /* coefficient */ 0, 1, 1, 1, 1, 0, 0, /* constant */ 0},
	{0, /* coefficient */ 1, 0, 1, 1, 0, 1, 0, /* constant */ 0},
	{0, /* coefficient */ 1, 1, 0, 0, 1, 1, 0, /* constant */ 0},
};

void print() {
		for(int j = 1; j <= 6; j++)
			for(int k = 1; k <= 8; k++)
				printf("%2.0lf%c", matrix[j][k], " \n"[k == 8]);
		puts(" =>");
}

std::string seq[5];

int main() {
	for(int i = 1; i <= 4; i++) for(int j = i + 1; j <= 4; j++) scanf("%d", &diff[i][j]), diff[j][i] = diff[i][j];
	matrix[1][8] = diff[1][2], matrix[2][8] = diff[1][3], matrix[3][8] = diff[1][4], matrix[4][8] = diff[2][3], matrix[5][8] = diff[2][4], matrix[6][8] = diff[3][4];
	// print();
	for(int i = 1; i <= 6; i++) {
		for(int j = i; j <= 6; j++) if(fabs(matrix[j][i]) > eps) { for(int k = 1; k <= 8; k++) std::swap(matrix[i][k], matrix[j][k]); break; }
		for(int j = 8; j >= i; j--) matrix[i][j] /= matrix[i][i];
		for(int j = i + 1; j <= 6; j++) {
			double coe = matrix[j][i] / matrix[i][i];
			for(int k = i; k <= 8; k++)
				matrix[j][k] -= matrix[i][k] * coe;
		}
		// print();
	}
	for(int i = 6; i >= 1; i--) {
		for(int j = 1; j < i; j++) {
			double coe = matrix[j][i] / matrix[i][i];
			for(int k = i; k <= 8; k++)
				matrix[j][k] -= matrix[i][k] * coe;
		}
		// print();
	}
	int ans = INF, ansid = -1;
	for(int i = 0; i <= 100000; i++) {
		int sum = i;
		for(int j = 1; j <= 6; j++) {
			double ret = matrix[j][8] - matrix[j][7] * i;
			if(ret < -eps || fabs(ret - round(ret)) > eps) { sum = INF; break; }
			sum += round(ret);
		}
		if(sum < ans) ans = sum, ansid = i;
	}
	if(ans == INF) { puts("-1"); return 0; }
	printf("%d\n", ans);
	for(int i = 1; i <= 7; i++) {
		int ret;
		if(i == 7) ret = ansid;
		else ret = matrix[i][8] - matrix[i][7] * ansid;
		while(ret--)
			switch(i) {
			case 1: seq[1].push_back('a'), seq[2].push_back('a'), seq[3].push_back('a'), seq[4].push_back('b'); break;
			case 2: seq[1].push_back('a'), seq[2].push_back('a'), seq[3].push_back('b'), seq[4].push_back('a'); break;
			case 3: seq[1].push_back('a'), seq[2].push_back('a'), seq[3].push_back('b'), seq[4].push_back('b'); break;
			case 4: seq[1].push_back('a'), seq[2].push_back('b'), seq[3].push_back('a'), seq[4].push_back('a'); break;
			case 5: seq[1].push_back('a'), seq[2].push_back('b'), seq[3].push_back('a'), seq[4].push_back('b'); break;
			case 6: seq[1].push_back('a'), seq[2].push_back('b'), seq[3].push_back('b'), seq[4].push_back('a'); break;
			case 7: seq[1].push_back('a'), seq[2].push_back('b'), seq[3].push_back('b'), seq[4].push_back('b'); break;
			default: assert(false);
			}
	}
	std::printf("%s\n%s\n%s\n%s\n", seq[1].c_str(), seq[2].c_str(), seq[3].c_str(), seq[4].c_str());
	return 0;
} /*
      12 13 14 23 24 34 |
      a  b  c  d  e  f  |
aaab  0  0  1  0  1  1  | x1
aaba  0  1  0  1  0  1  | x2
aabb  0  1  1  1  1  0  | x3
abaa  1  0  0  1  1  0  | x4
abab  1  0  1  1  0  1  | x5
abba  1  1  0  0  1  1  | x6
abbb  1  1  1  0  0  0  | x7
 =>
x1 x2 x3 x4 x5 x6 x7 const
0  0  0  1  1  1  1  a  (12)
0  1  1  0  0  1  1  b  (13)
1  0  1  0  1  0  1  c  (14)
0  1  1  1  1  0  0  d  (23)
1  0  1  1  0  1  0  e  (24)
1  1  0  0  1  1  0  f  (34)
*/