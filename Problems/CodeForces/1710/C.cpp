#include <cstdio>
#include <algorithm>
#include <cstring>

#define forbit(x) for(int x = 0; x <= 1; x++)

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

char s[N];
int n;

LL f[N][2][2][2][2][2][2][2][2][2];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) s[i] -= '0';
	f[0][1][1][1][0][0][0][1][1][1] = 1;
	for(int i = 0; i < n; i++)
		forbit(ta) forbit(tb) forbit(tc) // 贴边
			forbit(va) forbit(vb) forbit(vc) { // 值
				// if((ta && va != s[i]) || (tb && vb != s[i]) || (tc && vc != s[i])) continue; // ta 和 va 矛盾
				int vx = vb ^ vc, vy = va ^ vc, vz = va ^ vb; // 值
				forbit(nva) forbit(nvb) forbit(nvc) {
					// if((ta && nva > s[i + 1]) || (tb && nvb > s[i + 1]) || (tc && nvc > s[i + 1])) continue;
					int nvx = nvb ^ nvc, nvy = nva ^ nvc, nvz = nva ^ nvb;
					int nta = (ta && nva == s[i + 1]), ntb = (tb && nvb == s[i + 1]), ntc = (tc && nvc == s[i + 1]);
					forbit(njx) forbit(njy) forbit(njz) { // 进位
						int jx = (njx + vy + vz >= 2), jy = (njy + vx + vz >= 2), jz = (njz + vx + vy >= 2); // 进位
						forbit(tx) forbit(ty) forbit(tz) { // 贴边
							// if((tx && (vy + vz + njx) % 2 != vx) || (ty && (vx + vz + njy) % 2 != vy) || (tz && (vx + vy + njz) % 2 != vz)) continue;
							int ntx = (tx && nvx == (nvy + nvz + njx) % 2), nty = (ty && nvy == (nvx + nvz + njy) % 2), ntz = (tz && nvz == (nvx + nvy + njz) % 2);
							(f[i + 1][nta][ntb][ntc][njx][njy][njz][ntx][nty][ntz] += f[i][ta][tb][tc][jx][jy][jz][tx][ty][tz]) %= MOD;
						}
					}
				}
			}
	for(int i = 0; i <= n; i++) forbit(ta) forbit(tb) forbit(tc) forbit(jx) forbit(jy) forbit(jz) forbit(tx) forbit(ty) forbit(tz)
		if(f[i][ta][tb][tc][jx][jy][jz][tx][ty][tz])
			printf("f[%d][%d][%d][%d][%d][%d][%d][%d][%d][%d] = %lld\n", i, ta, tb, tc, jx, jy, jz, tx, ty, tz, f[i][ta][tb][tc][jx][jy][jz][tx][ty][tz]);
	LL ans = 0;
	forbit(oa) forbit(ob) forbit(oc) (ans += f[n][oa][ob][oc][0][0][0][0][0][0]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
101

*/