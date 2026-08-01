## transport

首先考虑方差最小这个限制。设 $s=\sum a_i$，那么这个限制就等价于让 $k$ 个城市的松果数为 $\lfloor \frac sn \rfloor$，其它 $n - k$ 个城市的松果数为 $\lfloor \frac sn \rfloor + 1$。证明也比较简单，考虑调整法。 对于一个 $i$ 满足 $a_i<\lfloor \frac sn \rfloor$，必然存在另一个 $j\ne i$，满足 $a_j>\lfloor \frac sn \rfloor + 1$。那么此时将 $a_i$ 加一，将 $a_j$ 减一，由于方差的式子 $\sum (\bar a-a_i)^2$ 可得答案一定不会变劣。

然后考虑这个 $x\times dist(u, v)$ 的代价，可以拆到边上。具体的，考虑一个方案，如果有 $x$ 个松果经过了边 $(u, v, w)$ （显然这些松果都应该是同一个方向），则对这个方案的代价产生 $w\times x$ 的贡献。最后的答案就是每个方案的代价取最小值。

现在就可以 DP 了。我们设 $f(u,i)$ 表示考虑 $u$ 子树，有 $i$ 个点的松果数为 $\lfloor \frac sn \rfloor + 1$，另外 $sz_u - i$ 个点的松果数为 $\lfloor \frac sn \rfloor$，此时 **$u$ 子树内的所有边** 的代价之和的最小值。

转移就是类似一个树上背包。考虑 $u$ 子树的转移，我们以此加入 $u$ 的每个儿子 $v$。转移式子就是 $f'(u, i+j)=\max\{f(u, i) + f(v, j) + cost(v)\}$，其中 $cost(v)$ 是 $(u, v, w)$ 这条边的贡献。设 $u$ 子树内所有点 **原来** 的松果数之和为 $sum_u$。对于 $f(v, j)$ 这个状态来说，最开始 $v$ 子树内有 $sum_v$ 个松果，而最终应该有 $sz_v \times \lfloor \frac sn \rfloor + j$ 个松果，所以有 $|sum_v - (sz_v \times \lfloor \frac sn \rfloor + j)|$ 个松果经过 $(u, v, w)$ 这条边，所以 $cost(v)$ 应该等于 $|sum_v - (sz_v \times \lfloor \frac sn \rfloor + j)| \times w$。

然后分析复杂度。乍一看这个是 $O(n^3)$ 的，但是我们发现对于 $f(u,i)$，只有在 $i\le sz_u$ 的时候才是有意义的，于是有一个经典的结论说明这个是 $O(n^2)$ 的。因为我们发现对于 $\{f(u, i)\}_{i\le x}$ 和 $\{f(v, j)\}_{j\le y}$，我们转移的时候相当于花费 $x\times y$ 的时间将他们合并成 $f(r, k)_{k\le x+y}$。换句话说，刚开始每个点处有一个大小为 $1$ 的集合，我们每次转移就是选择两个集合（设大小分别为 $x,y$），并用 $x\times y$ 的代价将其合并，那么最终的复杂度就是合并成一个集合时的代价之和。我们可以把 $x\times y$ 看成是两个集合中各选一个点组成的点对数量，那么对于任意两个点，我们只会在它们所在的集合被合并时统计一次，所以总复杂度是点对个数，也就是 $O(n^2)$ 的。
