#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL a[N];

int cnt[20];

std::vector<std::vector<LL>> f[2][N][N][N];

void chkmin(LL &x, LL y) { if(x > y) x = y; }
void chkmax(LL &x, LL y) { if(x < y) x = y; }

int main() {
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	LL sum = 0, sum2 = 0, total = 0;
	for(int i = 1; i <= n; i++) total += a[i];
	for(int i = 1; i <= n; i++)
		if(a[i] <= 7) cnt[a[i]]++;
		else sum += a[i] - 4, sum2 += 4;
	sum += 4, sum2 -= 4;
	for(int i3 = 0; i3 <= cnt[3]; i3++) for(int i4 = 0; i4 <= cnt[4]; i4++)
		for(int i5 = 0; i5 <= cnt[5]; i5++) {
			f[0][i3][i4][i5].resize(cnt[6] + 1, std::vector<LL>(cnt[7] + 1));
			f[1][i3][i4][i5].resize(cnt[6] + 1, std::vector<LL>(cnt[7] + 1));
			for(int i6 = 0; i6 <= cnt[6]; i6++) for(int i7 = 0; i7 <= cnt[7]; i7++)
				f[0][i3][i4][i5][i6][i7] = -LLINF, f[1][i3][i4][i5][i6][i7] = LLINF;
		}
	f[0][0][0][0][0][0] = sum2, f[1][0][0][0][0][0] = sum;
	for(int i3 = 0; i3 <= cnt[3]; i3++) for(int i4 = 0; i4 <= cnt[4]; i4++)
		for(int i5 = 0; i5 <= cnt[5]; i5++) for(int i6 = 0; i6 <= cnt[6]; i6++)
			for(int i7 = 0; i7 <= cnt[7]; i7++) {
				if(i3) chkmax(f[0][i3][i4][i5][i6][i7], f[1][i3 - 1][i4][i5][i6][i7]);
				if(i4) chkmax(f[0][i3][i4][i5][i6][i7], std::min(f[1][i3][i4 - 1][i5][i6][i7], f[0][i3][i4 - 1][i5][i6][i7] + 4));
				if(i5) chkmax(f[0][i3][i4][i5][i6][i7], std::min(f[1][i3][i4][i5 - 1][i6][i7], f[0][i3][i4][i5 - 1][i6][i7] + 4));
				if(i6) chkmax(f[0][i3][i4][i5][i6][i7], std::min(f[1][i3][i4][i5][i6 - 1][i7], f[0][i3][i4][i5][i6 - 1][i7] + 4));
				if(i7) chkmax(f[0][i3][i4][i5][i6][i7], std::min(f[1][i3][i4][i5][i6][i7 - 1], f[0][i3][i4][i5][i6][i7 - 1] + 4));
				if(i3) chkmin(f[1][i3][i4][i5][i6][i7], f[0][i3 - 1][i4][i5][i6][i7] + 3);
				if(i4) chkmin(f[1][i3][i4][i5][i6][i7], std::max(f[0][i3][i4 - 1][i5][i6][i7] + 4, f[1][i3][i4 - 1][i5][i6][i7] + 0));
				if(i5) chkmin(f[1][i3][i4][i5][i6][i7], std::max(f[0][i3][i4][i5 - 1][i6][i7] + 5, f[1][i3][i4][i5 - 1][i6][i7] + 1));
				if(i6) chkmin(f[1][i3][i4][i5][i6][i7], std::max(f[0][i3][i4][i5][i6 - 1][i7] + 6, f[1][i3][i4][i5][i6 - 1][i7] + 2));
				if(i7) chkmin(f[1][i3][i4][i5][i6][i7], std::max(f[0][i3][i4][i5][i6][i7 - 1] + 7, f[1][i3][i4][i5][i6][i7 - 1] + 3));
				// printf("f[%d][%d][%d][%d][%d] = %d, %d\n", i3, i4, i5, i6, i7, f[0][i3][i4][i5][i6][i7], f[1][i3][i4][i5][i6][i7]);
			}
	LL val = f[0][cnt[3]][cnt[4]][cnt[5]][cnt[6]][cnt[7]];
	printf("%lld %lld\n", val, total - val);
	return 0;
}