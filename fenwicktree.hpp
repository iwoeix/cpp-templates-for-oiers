#include <bit>

#define lowbit(x) 1 << countr_zero(x);

template <class int_tp, const unsigned int sz>
class fenwick_tree
{
    int_tp tr[sz + 1];

    public:
    fenwick_tree() { memset(tr, 0, sizeof tr); }
    fenwick_tree(int_tp *t) { for (int i = 1; i <= sz; i++) tr[i] = t[i - 1], i + lowbit(i) > n || tr[i + lowbit(i)] += tr[i]; }
    void add(unsigned int i, int_tp k) { while (i <= n) tr[i] += k, i += lowbit(i); }
    int_tp query(unsigned int i)
    {
        int_tp res();
        while (i) res += tr[i], i -= lowbit(i);
        return res;
    }
};