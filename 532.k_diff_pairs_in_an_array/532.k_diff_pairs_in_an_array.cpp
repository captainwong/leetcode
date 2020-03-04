#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

int findPairs(vector<int>& nums, int k) {
    int n = 0;
    if (nums.empty()) { return 0; }
    sort(nums.begin(), nums.end());
    if (k == 0) {
        int prev = nums[0];
        bool eqPrev = false;
        for (int i = 1; i < nums.size(); i++) {
            if (prev == nums[i]) { eqPrev = true; } 
            else if (eqPrev) { n++; eqPrev = false; }
            prev = nums[i];
        }
        if (eqPrev) { n++; }
        return n;
    }
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 0; i < nums.size() - 1; i++) {
        for (int j = i + 1; j < nums.size(); ) {
            if (nums[j] - nums[i] < k) { j++; }
            else {
                if (nums[j] - nums[i] == k) {
                    n++;
                }
                break;
            }
        }        
    }
    return n;
}

int main()
{
    {
        vector<int> v = { 1, 1, 1, 1, 1 };
        assert(findPairs(v, 0) == 1);
    }
    {
        vector<int> v = { 6,2,9,3,9,6,7,7,6,4 };
        assert(findPairs(v, 3) == 3);
    }
}