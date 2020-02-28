#include <vector>
#include <unordered_map>
#include <assert.h>

using namespace std;

int distance(const vector<int>& p1, const vector<int>& p2) {
    int dx = p2[0] - p1[0];
    int dy = p2[1] - p1[1];
    return dx * dx + dy * dy;
}

int numberOfBoomerangs(const vector<vector<int>>& points) {
    unordered_map<int, int> m;
    int r = 0;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < points.size(); j++) {
            if (i == j) { continue; }
            int d = distance(points[i], points[j]);
            m[d]++;
        }
        for (const auto& k : m) {
            if (k.second > 1) {
                r += k.second * (k.second - 1);
            }
        }
        m.clear();
    }
    return r;
}

int main()
{
    assert(numberOfBoomerangs({{0, 0}, {1, 0}, {2, 0}} ) == 2);
}