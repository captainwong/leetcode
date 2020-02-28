#include <vector>
#include <string>

using namespace std;


//// 依次右移
//struct watch {
//    bool led[11] = { false };
//    int left = 0; // 剩余未移位数量
//    int right = 0; // 当前最右侧可移动的灯
//
//    watch(int num) {
//        led[10] = true; // 哨兵
//        for (int i = 0; i < num; i++) {
//            led[i] = true;
//        }
//        left = num - 1;
//        right = num - 1;
//    }
//
//    bool shift() {
//        if (led[right + 1] && left) {
//            right = left--;
//        }
//        if (!led[right + 1]) {
//            led[right] = false;
//            led[++right] = true;
//            return true;
//        } else {
//            return false;
//
//        }
//    }
//
//    string read() const {
//        int h = led[0] ? 8 : 0;
//        h += led[1] ? 4 : 0;
//        h += led[2] ? 2 : 0;
//        h += led[3] ? 1 : 0;
//        int m = led[4] ? 32 : 0;
//        m += led[5] ? 16 : 0;
//        m += led[6] ? 8 : 0;
//        m += led[7] ? 4 : 0;
//        m += led[8] ? 2 : 0;
//        m += led[9] ? 1 : 0;
//        return to_string(h) + ":" + (m < 10 ? ("0" + to_string(m)) : to_string(m));
//    }
//};
//
//vector<string> readBinaryWatch(int num) {
//    vector<string> v;
//    if (num == 0) { v.emplace_back("0:00"); return v; } else if (num >= 10) { v.emplace_back("11:59"); return v; }
//    watch w(num); v.emplace_back(w.read());
//    while (w.shift()) {
//        v.emplace_back(w.read());
//    }
//    return v;
//}

int count1(int n) {
	int c = 0;
	while (n) {
		if (n & 1) { c++; }
		n >>= 1;
	}
	return c;
}

vector<string> readBinaryWatch(int num) {
	vector<string> r;
	for (int h = 0; h < 12; h++) {
		for (int m = 0; m < 60; m++) {
			if (count1(h) + count1(m) == num) {
				r.push_back(to_string(h) + ":" + (m < 10 ? "0" + to_string(m) : to_string(m)));
			}
		}
	}
	return r;
}

int main()
{

}