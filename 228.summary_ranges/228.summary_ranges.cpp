#include <vector>
#include <string>
#include <assert.h>

using namespace std;

/*
ִ����ʱ��0 ms, ������ C++ �ύ�л�����100.00%���û�
�ڴ����ģ�6.7 MB, ������ C++ �ύ�л�����96.22%���û�
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
