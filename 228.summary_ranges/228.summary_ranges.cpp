#include <vector>
#include <string>
#include <assert.h>

using namespace std;

/*
执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
内存消耗：6.7 MB, 在所有 C++ 提交中击败了96.22%的用户
*/
vector<string> summaryRanges(vector<int>& nums) {
	vector<string> ret;
	if (nums.empty()) { return ret; }
	int prev_first = nums[0];
	int prev = prev_first;
	std::string str;
	for (size_t i = 1; i < nums.size(); i++) {
		int val = nums[i];
		if (prev + 1 == val) {
			prev = val;
		} else {
			str = std::to_string(prev_first);
			if (prev_first < prev) {
				str += "->" + std::to_string(prev);
			}
			ret.push_back(str);
			prev_first = prev = val;
		}
	}
	str = std::to_string(prev_first);
	if (prev_first < prev) {
		str += "->" + std::to_string(prev);
	}
	ret.push_back(str);

	return ret;
}

int main()
{
	auto in = vector<int>({ 0,1,2,4,5,7 });
	assert(summaryRanges(in) == vector<string>({"0->2", "4->5", "7"}));
}
