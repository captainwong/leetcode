#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>

using namespace std;

/*
执行用时：76 ms, 在所有 C++ 提交中击败了99.87%的用户
内存消耗：36.1 MB, 在所有 C++ 提交中击败了72.02%的用户
*/
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
    unordered_map<std::string, size_t> us;
    for (size_t i = 0; i < list1.size(); i++) {
        us[list1[i]] = i;
    }
    vector<string> ret;
    size_t min_idx_sum = 999999;
    for (size_t i = 0; i < list2.size(); i++) {
        auto iter = us.find(list2[i]);
        if (iter == us.end()) { continue; }
        iter->second += i;
        if (iter->second < min_idx_sum) {
            min_idx_sum = iter->second;
            ret.clear();
            ret.push_back(list2[i]);
        } else if (iter->second == min_idx_sum) {
            ret.push_back(list2[i]);
        }
    }
    return ret;
}

int main()
{
    vector<string> list1 = { "Shogun", "Tapioca Express", "Burger King", "KFC" };
    vector<string> list2 = { "Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun" };
    vector<string> out = { "Shogun" };

    assert(findRestaurant(list1, list2) == out);    
}
