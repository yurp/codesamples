
#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

inline std::pair<int, char> MostConsecutiveChar(const std::string& s) {
    std::pair<int, char> best(0, '\0');
    std::pair<int, char> curr = best;
    for (auto c: s) {
        if (c != curr.second) {
            best = std::max(best, curr);
            curr = { 0, c };
        }
        ++curr.first;
    }

    best = std::max(best, curr);

    return best;
}

class NumStyle {
public:
    explicit NumStyle(std::initializer_list<int> commaMap)
        : m_commaMap(std::move(commaMap)) {
    }

    bool HasComma(size_t pos) const {
        return pos < m_commaMap.size() && m_commaMap[pos] == 1;
    }
private:
    std::vector<int> m_commaMap;
};

const NumStyle UsaStyle({ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 });
const NumStyle IndiaStyle({ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 });

inline std::string FormatNum(int n, const NumStyle& style) {
    if (n == 0) {
        return "0";
    }

    std::string s;
    bool isNeg = (n < 0);
    n = std::abs(n);
    int k = 0;
    while (n > 0) {
        if (style.HasComma(k)) {
            s += ',';
        }
        s += static_cast<char>(n % 10 + '0');
        ++k;
        n /= 10;
    }
    if (isNeg) {
        s += "-";
    }
    std::reverse(s.begin(), s.end());
    return s;
}

/** Get number of possible combinations of 1s and 2s which sums are n
 *  e.g n = 3:  1 + 1 + 1
 *              2 + 1
 *              1 + 2
 *      ans = 3
 */
inline int64_t SumsCount(int num) {
    // only one possible combination when sum contains 1s only
    int64_t ans = 1;
    int64_t prevCount = 1;

    int num2 = 1; // start from one 2
    num -= 2;     // one 2 'eats' two 1s

    while (num >= 0) {
        // Lets count possible number of combinations when we have num 1s and num2 2s
        // It's in fact number of selections of 1s from 1s and 2s, formula is:
        // (n by k) = n! / (k! * (n - k)!)
        // where n = (num + num2), k = num
        // Let's consider this formula in terms of previous value:
        // 1) each time we remove two 1s and add one 2, thus if previous (num + num2) is n and
        //    previous k is (num), then current values is (n - 1) and (k - 2) in terms of previous
        //    values
        // 2) prev = n! / (k! * (n - k)!) - and we can know the value of prev
        // 3) curr = (n - 1)! / ((k - 2)! * ((n - 1) - (k - 2))!) =
        //           n! /  ((k - 2)! * (n - k + 1))! * n) =
        //           n! * k * (k - 1) /  (k! * (n - k)! * (n - k + 1) * n) =
        //           (n! / (k! * (n - k)!)) * (k * (k - 1) / ((n - k + 1) * n)) =
        //           prev * k * (k - 1) / (n * (n - k + 1)
        //  Let's use the formula:
        auto n = num + num2 + 1;
        auto k = num + 2;
        auto count = prevCount * k * (k - 1) / (n * (n - k + 1));
        ans += count;
        ++num2;
        num -= 2;
        prevCount = count;
    }

    return ans;
}

std::vector<double> AvgGroups(const std::vector<int>& ar, size_t m) {
    assert(m <= ar.size() && !ar.empty());
    std::vector<double> avgs;
    int sum = std::accumulate(ar.begin(), ar.begin() + m, 0);
    avgs.emplace_back(sum * 1.0 / m);
    for (size_t i = m; i < ar.size(); ++i) {
        sum = sum + ar[i] - ar[i - m];
        avgs.emplace_back(sum * 1.0 / m);
    }

    return avgs;
}

