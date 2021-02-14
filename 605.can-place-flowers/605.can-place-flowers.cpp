#include <vector>
#include <assert.h>

using namespace std;

/*
执行用时：12 ms, 在所有 C++ 提交中击败了99.51%的用户
内存消耗：19.7 MB, 在所有 C++ 提交中击败了93.35%的用户
*/
bool canPlaceFlowers(const vector<int>& flowerbed, int n) {

    /*
    笨办法归纳一下规律：

    1. 一侧种了花一侧是边界的情况，数连续的0的个数
    花坛 连续0个数 可以种的花数
    01 1 0
    001 2 1
    0001 3 1
    00001 4 2
    000001 5 2
    0000001 6 3
    ......

    可以得知，连续的0的个数n与可以种的花数h关系为 h = n/2

    2. 两侧都种了花的情况，数连续的0的个数
    花坛 连续0个数 可以种的花数
    101 1 0
    1001 2 0
    10001 3 1
    100001 4 1
    1000001 5 2
    10000001 6 2
    ......
    可以得知，连续的0的个数n与可以种的花数h关系为 h = (n-1)/2

    3. 因此，只要统计出来连续的0的个数，就可以求得可以种的花数 h
    */


    int zs = 0; // 连续的0的个数
    if (!flowerbed.empty() && flowerbed[0] == 0) { // 要考虑边界情况
        zs = 1;
    }
    int h = 0;
    for (auto i : flowerbed) {
        if (i == 0) {
            zs++;
        } else { // 遇到1了就计算一下h
            if (zs > 0) {
                h += (zs - 1) / 2;
            }
            zs = 0;
        }
    }
    if (zs > 0) { // 要考虑边界情况
        h += (zs) / 2;
    }
    return n <= h;
}

int main()
{
    assert(canPlaceFlowers({ 1,0,0,0,1 }, 1));
    assert(!canPlaceFlowers({ 1,0,0,0,1 }, 2));

}
