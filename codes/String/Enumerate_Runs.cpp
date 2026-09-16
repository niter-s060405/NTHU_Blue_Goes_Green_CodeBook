/*
Tested : https://judge.yosupo.jp/submission/402738
AI generated code
*/
// returns [minimum_period, ans_l, ans_r] (閉區間, 0-based)
// (ans_r - ans_l + 1) >= minimum_period * 2
vector<array<int, 3>> enumerate_run(string s) {
    int n = s.size();
    if (n <= 1) return {};
    vector<vector<pair<int, int>>> stor(n + 1);

    auto sub = [&](string l, string r) {
        int a = l.size(), b = r.size();
        auto zl = z_function(string(l.rbegin(), l.rend()));
        auto zr = z_function(r + l + r); // Z_Algorithm.cpp
        vector<array<int, 3>> res;
        for (int p = 1; p <= a; p++) {
            int x = (p == a) ? p : min(zl[p] + p, a);
            int y = min(zr[a + b - p], b);
            if (x + y >= 2 * p) res.push_back({p, x, y});
        }
        return res;
    };

    auto dfs = [&](auto self, int l, int r) -> void {
        if (r - l <= 1) return;
        int m = (l + r) >> 1;
        self(self, l, m); self(self, m, r);
        auto sl = s.substr(l, m-l), sr = s.substr(m, r-m);
        for (auto [p, a, b] : sub(sl, sr))
            stor[p].push_back({m - a, m + b});
        reverse(sl.begin(), sl.end());
        reverse(sr.begin(), sr.end());
        for (auto [p, a, b] : sub(sr, sl))
            stor[p].push_back({m - b, m + a});
    };
    dfs(dfs, 0, n);

    vector<array<int, 3>> runs;
    set<pair<int, int>> done;
    for (int p = 1; p <= n; p++) {
        auto& v = stor[p];
        sort(v.begin(), v.end(), [](auto& x, auto& y) {
            return (x.first != y.first) ? (x < y)
                                : (x.second > y.second);
        });
        int mx = -1;
        for (auto &[l, r] : v) if (r > mx) {
            mx = r;
            if (done.insert({l, r}).second)
                runs.push_back({p, l, r - 1});
        }
    }
    sort(runs.begin(), runs.end());
    return runs;
}
