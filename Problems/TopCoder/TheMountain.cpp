#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

const int N = 200 + 5;
const int INF = 0x3f3f3f3f;

int a[N][N];
int b[5][N][N], sum[4][N][N];

inline void trim(int &x) { if(x > INF) x = INF; }
inline int trim2(const long long &x) { return x >= INF ? INF : x; }
// #define trim(x) ({ int val = (x); if(val > INF) (x) = INF; if(x < 0) printf("Error on line %d\n", __LINE__); })

class TheMountain {
public:
	int minSum(int n, int m, vector<int> rowIndex, vector<int> columnIndex, vector<int> element) {
		for(int i = 0; i < (int)element.size(); i++) a[rowIndex[i] + 1][columnIndex[i] + 1] = element[i];
		int ans = INF;
		// preprocess #1
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++) b[0][i][j] = a[i][j];
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
			int v = std::max(b[0][i - 1][j], b[0][i][j - 1]) + 1;
			trim(v);
			if(b[0][i][j]) { if(b[0][i][j] < v) b[0][i][j] = INF; }
			else b[0][i][j] = v;
			sum[0][i][j] = trim2((long long)sum[0][i - 1][j] + sum[0][i][j - 1] - sum[0][i - 1][j - 1] + b[0][i][j]);
		}
		// preprocess #2
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++) b[1][i][j] = a[i][j];
		for(int i = n; i >= 1; i--) for(int j = 1; j <= m; j++) {
			int v = std::max(b[1][i + 1][j], b[1][i][j - 1]) + 1;
			trim(v);
			if(b[1][i][j]) { if(b[1][i][j] < v) b[1][i][j] = INF; }
			else b[1][i][j] = v;
			sum[1][i][j] = trim2((long long)sum[1][i + 1][j] + sum[1][i][j - 1] - sum[1][i + 1][j - 1] + b[1][i][j]);
		}
		// preprocess #3
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++) b[2][i][j] = a[i][j];
		for(int i = 1; i <= n; i++) for(int j = m; j >= 1; j--) {
			int v = std::max(b[2][i - 1][j], b[2][i][j + 1]) + 1;
			trim(v);
			if(b[2][i][j]) { if(b[2][i][j] < v) b[2][i][j] = INF; }
			else b[2][i][j] = v;
			sum[2][i][j] = trim2((long long)sum[2][i - 1][j] + sum[2][i][j + 1] - sum[2][i - 1][j + 1] + b[2][i][j]);
		}
		// preprocess #4
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++) b[3][i][j] = a[i][j];
		for(int i = n; i >= 1; i--) for(int j = m; j >= 1; j--) {
			int v = std::max(b[3][i + 1][j], b[3][i][j + 1]) + 1;
			trim(v);
			if(b[3][i][j]) { if(b[3][i][j] < v) b[3][i][j] = INF; }
			else b[3][i][j] = v;
			sum[3][i][j] = trim2((long long)sum[3][i + 1][j] + sum[3][i][j + 1] - sum[3][i + 1][j + 1] + b[3][i][j]);
		}
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
			int ret = 0;
			for(int k = 1; k <= m; k++) b[4][i][k] = a[i][k];
			for(int k = 1; k <= n; k++) b[4][k][j] = a[k][j];
			// process #1
			for(int k = 1; k < j; k++) {
				int v = std::max({b[0][i - 1][k], b[1][i + 1][k], b[4][i][k - 1]}) + 1;
				trim(v);
				if(b[4][i][k]) { if(b[4][i][k] < v) ret = INF; }
				else b[4][i][k] = v;
			}
			// process #2
			for(int k = m; k > j; k--) {
				int v = std::max({b[2][i - 1][k], b[3][i + 1][k], b[4][i][k + 1]}) + 1;
				trim(v);
				if(b[4][i][k]) { if(b[4][i][k] < v) ret = INF; }
				else b[4][i][k] = v;
			}
			// process #3
			for(int k = 1; k < i; k++) {
				int v = std::max({b[0][k][j - 1], b[2][k][j + 1], b[4][k - 1][j]}) + 1;
				trim(v);
				if(b[4][k][j]) { if(b[4][k][j] < v) ret = INF; }
				else b[4][k][j] = v;
			}
			// process #4
			for(int k = n; k > i; k--) {
				int v = std::max({b[1][k][j - 1], b[3][k][j + 1], b[4][k + 1][j]}) + 1;
				trim(v);
				if(b[4][k][j]) { if(b[4][k][j] < v) ret = INF; }
				else b[4][k][j] = v;
			}
			// process #5
			{
				int v = std::max({b[4][i - 1][j], b[4][i][j - 1], b[4][i + 1][j], b[4][i][j + 1]}) + 1;
				trim(v);
				if(b[4][i][j]) { if(b[4][i][j] < v) ret = INF; }
				else b[4][i][j] = v;
			}
			// get answer
			if(ret < INF) {
				for(int k = 1; k <= m; k++) if(k != j) trim(ret += b[4][i][k]);
				for(int k = 1; k <= n; k++) if(k != i) trim(ret += b[4][k][j]);
				trim(ret += b[4][i][j]);
				trim(ret += sum[0][i - 1][j - 1]);
				trim(ret += sum[1][i + 1][j - 1]);
				trim(ret += sum[2][i - 1][j + 1]);
				trim(ret += sum[3][i + 1][j + 1]);
				ans = std::min(ans, ret);
			}
		}
		return ans == INF ? -1 : ans;
	}
};