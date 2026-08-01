// Completed by DeepSeek

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 100005;

struct Job {
    int d, p;
} a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].d >> a[i].p;

    // 按利润降序排序
    sort(a, a + n, [](const Job &x, const Job &y) {
        return x.p > y.p;
    });

    // 并查集：fa[x] 记录 <= x 的最大空闲时间（若 x 未被占用，则为 x 本身）
    unordered_map<int, int> fa;

    function<int(int)> find = [&](int x) -> int {
        // 如果 x 未被记录，说明空闲，直接返回 x
        if (!fa.count(x)) return x;
        // 否则路径压缩
        return fa[x] = find(fa[x]);
    };

    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        // 可用的最晚时刻为 d - 1（因为完成时刻 t 必须 < d）
        int t = find(a[i].d - 1);
        if (t >= 0) {               // t >= 0 表示存在空闲时刻
            ans += a[i].p;
            // 占用 t，将其父亲设为 t-1（下次查询 ≤ t 时会自动跳过）
            fa[t] = t - 1;
        }
        // 若 t < 0（即 find 返回 -1），说明无法安排，跳过
    }

    cout << ans << '\n';
    return 0;
}