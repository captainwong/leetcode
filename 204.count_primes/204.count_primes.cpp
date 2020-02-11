#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <queue>

using namespace std;

class Bitmap
{
private:
    //! ����ͼ����ŵĿռ�M[]
    char* M = nullptr;
    //! �ռ�M������Ϊ (N * sizeof(char) * 8) ���أ��� N ���ֽ�
    int N = 0;


public:
    Bitmap(int n = 8) { init(n); }
    ~Bitmap() { destroy(); }

    void init(int n) {
        M = new char[N = (n + 7) / 8];
        memset(M, 0, N);
    }

    void destroy() { if (M) { delete[] M; M = nullptr; } N = 0; }

    void expand(int k) {
        if (k < 8 * N) { return; }
        auto oldN = N;
        auto oldM = M;
        init(2 * k);
        memcpy(M, oldM, oldN);
        delete[] oldM;
    }

    // O(1)
    void set(int k) {
        expand(k);
        M[k >> 3] |= (0x80 >> (k & 0x07));
    }

    // O(1)
    void clear(int k) {
        expand(k);
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
    }

    // O(1)
    bool test(int k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }


    //! ��λ��ӡ
    void print(int n) {
        expand(n);
        for (int i = 0; i < n; i++) { printf(test(i) ? "1" : "0"); }
    }

    /**
    * @brief ��ǰnλת��Ϊ�ַ���
    * @return �ַ���ָ�룬�ɵ����߸����ͷ�
    */
    char* toString(int n) {
        expand(n - 1);
        char* s = new char[n + 1]; s[n] = 0;
        for (int i = 0; i < n; i++) { s[i] = test(i) ? '1' : '0'; }
        return s;
    }
};
int countPrimes(int n) {
    if (n < 3) { return 0; }
    int count = n - 2;
    Bitmap not_primes(n);
    not_primes.set(0);
    not_primes.set(1);
    for (int i = 2; i < n; i++) {
        if (!not_primes.test(i)) {
            for (int j = min(i, 46340) * min(i, 46340); j < n; j += i) {
                if (!not_primes.test(j)) {
                    not_primes.set(j);
                    count--;
                }
            }
        }
    }
    return count;
}

int main()
{
    assert(countPrimes(13) == 5);

}