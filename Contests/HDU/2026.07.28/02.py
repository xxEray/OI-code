import sys

def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out = []
    eps = 1e-12

    for _ in range(T):
        n = int(next(it))
        w = int(next(it))
        x = [int(next(it)) for _ in range(n)]

        sum_inv = sum(1.0 / xi for xi in x)

        if sum_inv > 1.0 + eps:
            # Need to solve L(t) = 1
            x_sorted = sorted(x, reverse=True)   # descending x -> descending c
            groups = []
            for val in x_sorted:
                if groups and groups[-1][0] == val:
                    groups[-1][1] += 1
                else:
                    groups.append([val, 1])

            n_active = n
            sum_active = sum((xi - 1.0) / xi for xi in x)
            u_prev = 0.0
            t = 1.0
            found = False

            for val, cnt in groups:
                c_val = (val - 1.0) / val
                u_curr = 1.0 / c_val
                if sum_active > 1e-15:
                    t_cand = (n_active - 1) / sum_active
                    if t_cand >= u_prev - eps and t_cand <= u_curr + eps:
                        t = t_cand
                        found = True
                        break
                n_active -= cnt
                sum_active -= cnt * c_val
                u_prev = u_curr

            if not found:   # fallback binary search, barely used
                low, high = 1.0, 200.0
                for _ in range(80):
                    mid = (low + high) * 0.5
                    L = 0.0
                    for xi in x:
                        val = 1.0 - mid * (xi - 1.0) / xi
                        if val > 0.0:
                            L += val
                    if L <= 1.0:
                        high = mid
                    else:
                        low = mid
                t = high

        elif sum_inv < 1.0 - eps:
            t = 1.0 / sum_inv
        else:
            t = 1.0

        ans = w * t
        out.append(f"{ans:.10f}")

    sys.stdout.write("\n".join(out))

solve()