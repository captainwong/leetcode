#include <vector>

using namespace std;

vector<int> constructRectangle(int area) {
    int w, l;
    w = l = sqrt(area);
    int sq = w * l;
    if (sq == area) { return vector<int>{l, w}; }
    while (sq != area) {
        if (sq < area) {
            l++;
        } else {
            w--;
        }
        sq = w * l;
    }
    return vector<int>{l, w};
}

int main()
{
    constructRectangle(2);
}