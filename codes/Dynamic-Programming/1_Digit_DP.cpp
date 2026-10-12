#include <bits/stdc++.h>
using namespace std;

/**
 * 換題需要修改 3 個地方：
 *    - [# 處 1] 狀態定義與 memo 表大小 (pre/sum/mask)
 *    - [# 處 2] 合法性剪枝條件 (相鄰差/禁用數字等)
 *    - [# 處 3] 轉移至下一位的狀態計算
 */

// ----------------------------------------------------------
// [# 處 1] 狀態與快取陣列定義
// 題目：計算 [l, r] 中相鄰位數皆不相同的數字數量
// memo[pos][pre]：在「正要填第 pos 位（無上界限制）」
//         且「前一位為 pre」狀態下，填完後續位數的合法方法數
// ----------------------------------------------------------
long long memo[20][11];
string num_str;

/**
 * @param pos       當前處理位數 (最高位 0 到 n-1)
 * @param pre       前一位數字 (10 表示無前驅/前導零)
 * @param is_limit  是否受上界限制 (true: 最大填到 s[pos])
 * @param is_num    是否已填有效數字 (false: 前導零)
 * @return 符合條件的填法總數
 */
long long dfs(int pos, int pre, bool is_limit, bool is_num) {
    // 終止條件：所有位數都已填完
    if (pos == (int)num_str.size()) {
        // 成功構造出 1 個合法數字 (若求正整數則回傳 is_num)
        return 1;
    }

    // 記憶化讀取：只有無上界限制且已填數字時才查表
    if (!is_limit && is_num && memo[pos][pre] != -1) {
        return memo[pos][pre];
    }

    long long res = 0;
    int up = is_limit ? (num_str[pos] - '0') : 9;

    // 【分支 1】這位繼續放前導零
    if (!is_num) {
        res += dfs(pos + 1, 10, false, false);
    }

    // 【分支 2】這位填入有效數字
    // 若前面是前導零本位從 1 起跳，已在數字中則從 0 起跳
    int start_digit = is_num ? 0 : 1;
    for (int d = start_digit; d <= up; ++d) {
        if (is_num && d == pre) { // [# 處 2] 約束檢查
            continue; // 相鄰數字不能相同
        }
        // [# 處 3] 狀態轉移至下一位
        res += dfs(pos + 1, d, is_limit && (d == up), true);
    }

    // 記憶化寫入：無上界限制且已填有效數字時存入快取
    if (!is_limit && is_num) {
        memo[pos][pre] = res;
    }

    return res;
}

// 計算 [0, n] 區間內符合條件的數字數量
long long count_le(long long n) {
    if (n < 0) return 0;
    num_str = to_string(n);
    memset(memo, -1, sizeof(memo));
    return dfs(0, 10, true, false);
}

// 計算 [l, r] 區間內的答案
long long solve(long long l, long long r) {
    return count_le(r) - count_le(l - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    long long l, r;
    if (cin >> l >> r) {
        cout << solve(l, r) << "\n";
    }

    return 0;
}
