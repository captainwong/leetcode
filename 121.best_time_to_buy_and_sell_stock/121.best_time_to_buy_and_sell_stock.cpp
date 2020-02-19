#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

// k为最大交易次数（买入+卖出算作一次）

// k=1
namespace p121 {
int maxProfit(const vector<int>& prices) {
    int buy = 0x7FFFFFFF;
    int profit = 0;
    for (auto price : prices) {
        if (price < buy) {
            buy = price;
        } else if (price - buy > profit) {
            profit = price - buy;
        }
    }
    return profit;
}
}

// k=无穷
namespace p122 {
int maxProfit(const vector<int>& prices) {
    if (prices.empty()) { return 0; }
    int dp_i_0 = 0;
    int dp_i_1 = -prices[0];
    for (size_t i = 1; i < prices.size(); i++) {
        int t = dp_i_0;
        dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = max(dp_i_1, t - prices[i]);
    }
    return dp_i_0;
}
}

// k=2
namespace p123 {
int maxProfit(const vector<int>& prices) {
    if (prices.empty()) { return 0; }
    auto dp = new int[prices.size()][3][2];
    dp[0][2][0] = 0;
    dp[0][2][1] = -prices[0];
    dp[0][1][0] = 0;
    dp[0][1][1] = -prices[0];
    dp[0][0][0] = 0;
    dp[0][0][1] = -prices[0];
    for (int i = 1; i < prices.size(); i++) {
        for (int k = 1; k <= 2; k++) {
            /*if (i == 0) {
                dp[0][k][0] = 0;
                dp[0][k][1] = -prices[0];
                continue;
            }*/
            dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
            dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
        }
    }
    return dp[prices.size() - 1][2][0];
}
}

int main()
{
    assert(p121::maxProfit({ 7,1,5,3,6,4 }) == 5);
    assert(p121::maxProfit({ 7,6,4,3,1 }) == 0);

    assert(p122::maxProfit({ 7,1,5,3,6,4 }) == 7);
    assert(p122::maxProfit({ 1,2,3,4,5 }) == 4);
    assert(p122::maxProfit({ 7,6,4,3,1 }) == 0);


    assert(p123::maxProfit({ 1,2,1,2 }) == 2);
    assert(p123::maxProfit({ 3,3,5,0,0,3,1,4 }) == 6);
    assert(p123::maxProfit({ 1,2,3,4,5 }) == 4);
    assert(p123::maxProfit({ 7,6,4,3,1 }) == 0);
    assert(p123::maxProfit({ 2,1,2,0,1 }) == 2);
}
