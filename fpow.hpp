template <class base, class exp>
base fpow(base a, exp b)
{
    base res = 1;
    for (; b; b & 1 && (res *= a), a *= a, b >>= 1);
    return res;
}

template <class base, class exp, class mod>
base fpow(base a, exp b, mod p)
{
    base res = 1 % p;
    for (; b; b & 1 && ((res *= a) %= p), (a *= a) %= p, b >>= 1);
    return res;
}
