#include <vector>
#include <assert.h>

using namespace std;

/*
ִ����ʱ��12 ms, ������ C++ �ύ�л�����99.51%���û�
�ڴ����ģ�19.7 MB, ������ C++ �ύ�л�����93.35%���û�
*/
bool canPlaceFlowers(const vector<int>& flowerbed, int n) {

    /*
    ���취����һ�¹��ɣ�

    1. һ�����˻�һ���Ǳ߽���������������0�ĸ���
    ��̳ ����0���� �����ֵĻ���
    01 1 0
    001 2 1
    0001 3 1
    00001 4 2
    000001 5 2
    0000001 6 3
    ......

    ���Ե�֪��������0�ĸ���n������ֵĻ���h��ϵΪ h = n/2

    2. ���඼���˻����������������0�ĸ���
    ��̳ ����0���� �����ֵĻ���
    101 1 0
    1001 2 0
    10001 3 1
    100001 4 1
    1000001 5 2
    10000001 6 2
    ......
    ���Ե�֪��������0�ĸ���n������ֵĻ���h��ϵΪ h = (n-1)/2

    3. ��ˣ�ֻҪͳ�Ƴ���������0�ĸ������Ϳ�����ÿ����ֵĻ��� h
    */


    int zs = 0; // ������0�ĸ���
    if (!flowerbed.empty() && flowerbed[0] == 0) { // Ҫ���Ǳ߽����
        zs = 1;
    }
    int h = 0;
    for (auto i : flowerbed) {
        if (i == 0) {
            zs++;
        } else { // ����1�˾ͼ���һ��h
            if (zs > 0) {
                h += (zs - 1) / 2;
            }
            zs = 0;
        }
    }
    if (zs > 0) { // Ҫ���Ǳ߽����
        h += (zs) / 2;
    }
    return n <= h;
}

int main()
{
    assert(canPlaceFlowers({ 1,0,0,0,1 }, 1));
    assert(!canPlaceFlowers({ 1,0,0,0,1 }, 2));

}