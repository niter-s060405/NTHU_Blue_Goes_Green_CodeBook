/*
Tested: https://judge.yosupo.jp/submission/406253
Write by : temmie
Last modified by : niter
*/
const int MOD = (119 << 23) + 1, ROOT = 62; // = 998244353
// For p < 2^30 there is also 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

// 9b3df6
void NTT(vector<int> &a, int flag = false) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<int> rt(2, 1);
    static int last_n = 0;
    if (last_n < n) {
        last_n = n;
        rt.resize(n);
        for (int k = 2, s = 2; k < n; k += k, s++) {
            int z[] = {1, fpow(ROOT, MOD >> s, MOD)};
            for (int i = k; i < 2 * k; i++)
                rt[i] = rt[i / 2] * z[i & 1] % MOD;
        }
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i]=(rev[i/2]|(i&1)<<L)/2;
    for (int i = 0; i < n; i++) if (i < rev[i]) {
        swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k += k) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int z = rt[j+k]*a[i+j+k]%MOD, &ai = a[i+j];
                a[i+j+k] = ai-z+(z>ai ? MOD : 0);
                ai += (ai+z>=MOD ? z-MOD : z);
            }
        }
    }

    if (flag) {
        reverse(a.begin() + 1, a.end());
        int n_inv = fpow(n, MOD - 2, MOD);
        for (int i = 0; i < n; i++) (a[i] *= n_inv) %= MOD;
    }
}

// 75e55e, If too slow, consider using global array
vector<int> polyMul(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    int s = a.size() + b.size() - 1;
    int B = 32 - __builtin_clz(s), n = 1 << B;
    a.resize(n); NTT(a);
    b.resize(n); NTT(b);
    for (int i = 0; i < n; i++) (a[i] *= b[i]) %= MOD;
    NTT(a, true);
    a.resize(s);
    return a;
}
