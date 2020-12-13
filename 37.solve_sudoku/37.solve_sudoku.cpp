#include "../common/leetcode.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdint.h>

/*
执行用时：176 ms, 在所有 C++ 提交中击败了5.62%的用户
内存消耗：16.9 MB, 在所有 C++ 提交中击败了5.62%的用户
*/

namespace leetcode {
class Solution {
public:

    struct Item {
        int i = 0;
        int j = 0;
        int val = 0;
        int start = 0;
    };

    unordered_set<int> rows[9]{}, cols[9]{}, blocks[9]{};

    Item items[81]{};
    int spaces = 81;
    Item firstSpace;
    bool foundFirstSpace = false;
    uint64_t count = 0;
    bool enable_print = false;


    void print() {
        if (!enable_print) { return; }
        printf("spaces=%d--------------------------\n", spaces);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d ", items[i * 9 + j].val/*, items[i * 9 + j].start*/);
            }
            printf("\n");
        }
        printf("count=%zd---------------------------\n\n", ++count);
    }

    bool readBoard(vector<vector<char>>& board) {
        if (board.size() != 9) { return false; }
        for (const auto& line : board) { if (line.size() != 9) return false; }

        memset(items, 0, sizeof(items));
        spaces = 81;
        foundFirstSpace = false;
        count = 0;
        for (auto& i : rows) { i.clear(); }
        for (auto& i : cols) { i.clear(); }
        for (auto& i : blocks) { i.clear(); }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    if (!foundFirstSpace) {
                        firstSpace.i = i;
                        firstSpace.j = j;
                        firstSpace.start = 1;
                        foundFirstSpace = true;
                    }
                    continue;
                }

                int val = board[i][j] - '0';

                Item item;
                item.i = i;
                item.j = j;
                item.val = val;
                items[i * 9 + j] = item;
                spaces--;

                rows[i].insert(val);
                cols[j].insert(val);
                int k = j / 3 + i / 3 * 3;
                blocks[k].insert(val);
            }
        }
        return true;
    }

    Item& find_next_space(int i, int j) {
        j++;
        for (; i < 9; i++) {
            for (; j < 9; j++) {
                if (items[i * 9 + j].val == 0) {
                    auto& item = items[i * 9 + j];
                    item.i = i;
                    item.j = j;
                    //item.start = 0;
                    return item;
                }
            }
            j = 0;
        }
        abort();
    }

    int find_available_val(int i, int j, int start = 1) {
        int k = j / 3 + i / 3 * 3;
        // if (start > 9) { start = 1; }
        for (int val = start; val < 10; val++) {
            if (rows[i].find(val) == rows[i].end()
                && cols[j].find(val) == cols[j].end()
                && blocks[k].find(val) == blocks[k].end()) {
                return val;
            }
        }
        return 0;
    }

    void place(Item item) {
        item.start = item.val;
        items[item.i * 9 + item.j] = item;
        rows[item.i].insert(item.val);
        cols[item.j].insert(item.val);
        int k = item.j / 3 + item.i / 3 * 3;
        blocks[k].insert(item.val);
        spaces--;

        if (spaces > 0) {
            find_next_space(item.i, item.j).start = 0;
        }
    }

    void remove(Item item) {
        items[item.i * 9 + item.j].val = 0;
        //items[item.i * 9 + item.j].start = 0;
        rows[item.i].erase(item.val);
        cols[item.j].erase(item.val);
        int k = item.j / 3 + item.i / 3 * 3;
        blocks[k].erase(item.val);
        spaces++;
    }

    void solveSudoku(vector<vector<char>>& board) {
        if (!readBoard(board)) { return; }

        //print();

        list<Item> tried;
        firstSpace.val = find_available_val(0, 0, 1);
        place(firstSpace);
        tried.push_back(firstSpace);

        //print();
        while (spaces > 0) {
            auto& last = tried.back();
            auto& item = find_next_space(last.i, last.j);
            item.val = find_available_val(item.i, item.j, item.start + 1);
            if (item.val == 0) {
                remove(last);
                if (tried.size() == 1) { // 回溯到第一个空位了
                    last.val = find_available_val(last.i, last.j, ++last.start); // 这里不用考虑失败因为题目保证有解
                    place(last);
                } else {
                    tried.pop_back();
                }
            } else {
                place(item);
                tried.push_back(item);
            }
            //print();
        }

        print();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = items[i * 9 + j].val + '0';
            }
        }
    }
};

void test() {
    vector<vector<char>> input1 = {
        {'5', '3', '.',  '.', '7', '.',  '.', '.', '.'},
        {'6', '.', '.',  '1', '9', '5',  '.', '.', '.'},
        {'.', '9', '8',  '.', '.', '.',  '.', '6', '.'},

        {'8', '.', '.',  '.', '6', '.',  '.', '.', '3'},
        {'4', '.', '.',  '8', '.', '3',  '.', '.', '1'},
        {'7', '.', '.',  '.', '2', '.',  '.', '.', '6'},

        {'.', '6', '.',  '.', '.', '.',  '2', '8', '.'},
        {'.', '.', '.',  '4', '1', '9',  '.', '.', '5'},
        {'.', '.', '.',  '.', '8', '.',  '.', '7', '9'}
    };

    vector<vector<char>> output1 = {
        {'5', '3', '4',  '6', '7', '8',  '9', '1', '2'},
        {'6', '7', '2',  '1', '9', '5',  '3', '4', '8'},
        {'1', '9', '8',  '3', '4', '2',  '5', '6', '7'},

        {'8', '5', '9',  '7', '6', '1',  '4', '2', '3'},
        {'4', '2', '6',  '8', '5', '3',  '7', '9', '1'},
        {'7', '1', '3',  '9', '2', '4',  '8', '5', '6'},

        {'9', '6', '1',  '5', '3', '7',  '2', '8', '4'},
        {'2', '8', '7',  '4', '1', '9',  '6', '3', '5'},
        {'3', '4', '5',  '2', '8', '6',  '1', '7', '9'}
    };

    Solution sln;
    sln.solveSudoku(input1);
    assert(input1 == output1);
}
}

// puzzles from http://norvig.com/sudoku.html
namespace norvig {

class Solution {
public:

    struct Item {
        int i = 0;
        int j = 0;
        int val = 0;
        int start = 0;
    };

    unordered_set<int> rows[9]{}, cols[9]{}, blocks[9]{};

    Item items[81]{};
    int spaces = 81;
    Item firstSpace;
    bool foundFirstSpace = false;
    uint64_t count = 0;
    bool enable_print = false;


    void print(bool force_print = false) {
        ++count;
        if (!enable_print && !force_print) { return; }
        printf("spaces=%d--------------------------\n", spaces);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d ", items[i * 9 + j].val/*, items[i * 9 + j].start*/);
            }
            printf("\n");
        }
        printf("count=%zd---------------------------\n\n", count);
    }

    bool readBoard(vector<vector<int>>& board) {
        if (board.size() != 9) { return false; }
        for (const auto& line : board) { if (line.size() != 9) return false; }

        memset(items, 0, sizeof(items));
        spaces = 81;
        foundFirstSpace = false;
        count = 0;
        for (auto& i : rows) { i.clear(); }
        for (auto& i : cols) { i.clear(); }
        for (auto& i : blocks) { i.clear(); }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    if (!foundFirstSpace) {
                        firstSpace.i = i;
                        firstSpace.j = j;
                        firstSpace.start = 1;
                        foundFirstSpace = true;
                    }
                    continue;
                }

                int val = board[i][j];

                Item item;
                item.i = i;
                item.j = j;
                item.val = val;
                items[i * 9 + j] = item;
                spaces--;

                rows[i].insert(val);
                cols[j].insert(val);
                int k = j / 3 + i / 3 * 3;
                blocks[k].insert(val);
            }
        }
        return true;
    }

    Item& find_next_space(int i, int j) {
        j++;
        for (; i < 9; i++) {
            for (; j < 9; j++) {
                if (items[i * 9 + j].val == 0) {
                    auto& item = items[i * 9 + j];
                    item.i = i;
                    item.j = j;
                    //item.start = 0;
                    return item;
                }
            }
            j = 0;
        }
        abort();
    }

    int find_available_val(int i, int j, int start = 1) {
        int k = j / 3 + i / 3 * 3;
        // if (start > 9) { start = 1; }
        for (int val = start; val < 10; val++) {
            if (rows[i].find(val) == rows[i].end()
                && cols[j].find(val) == cols[j].end()
                && blocks[k].find(val) == blocks[k].end()) {
                return val;
            }
        }
        return 0;
    }

    void place(Item item) {
        item.start = item.val;
        items[item.i * 9 + item.j] = item;
        rows[item.i].insert(item.val);
        cols[item.j].insert(item.val);
        int k = item.j / 3 + item.i / 3 * 3;
        blocks[k].insert(item.val);
        spaces--;

        if (spaces > 0) {
            find_next_space(item.i, item.j).start = 0;
        }
    }

    void remove(Item item) {
        items[item.i * 9 + item.j].val = 0;
        //items[item.i * 9 + item.j].start = 0;
        rows[item.i].erase(item.val);
        cols[item.j].erase(item.val);
        int k = item.j / 3 + item.i / 3 * 3;
        blocks[k].erase(item.val);
        spaces++;
    }

    void to_board(vector<vector<int>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = items[i * 9 + j].val;
            }
        }
    }

    bool solve() {
        list<Item> tried;
        firstSpace.val = find_available_val(0, 0, 1);
        place(firstSpace);
        tried.push_back(firstSpace);

        print();
        while (spaces > 0) {
            auto& last = tried.back();
            auto& item = find_next_space(last.i, last.j);
            item.val = find_available_val(item.i, item.j, item.start + 1);
            if (item.val == 0) {
                remove(last);
                if (tried.size() == 1) { // 回溯到第一个空位了
                    last.val = find_available_val(last.i, last.j, ++last.start);
                    if (last.val == 0) {
                        return false;
                    }
                    place(last);
                } else {
                    tried.pop_back();
                }
            } else {
                place(item);
                tried.push_back(item);
            }
            print();
        }

        print();
        
        return true;
    }

    bool solveSudoku(vector<vector<int>>& board) {
        if (!readBoard(board)) { return false; }

        if (solve()) {
            to_board(board);
            return true;
        }

        return false;
    }
};

vector<vector<vector<int>>> from_file(std::string path) {
    vector<vector<vector<int>>> res;
    std::ifstream in(path);
    if (in.is_open()) {
        std::stringstream ss;
        ss << in.rdbuf();
        in.close();
        auto content = ss.str();
        size_t prev = 0;
        auto pos = content.find_first_of('\n');
        while (pos != content.npos && pos - prev >= 81) {
            auto str = content.substr(prev, 81);
            vector<vector<int>> board;
            for (int i = 0; i < 9; i++) {
                vector<int> line;
                for (int j = 0; j < 9; j++) {
                    int val = str[i * 9 + j];
                    if ('1' <= val && val <= '9') {
                        line.push_back(val - '0');
                    } else if (val == '.' || val == '0') {
                        line.push_back(0);
                    } else {
                        return res;
                    }
                }
                board.push_back(line);
            }
            res.push_back(board);
            prev = pos + 1;
            pos = content.find_first_of('\n', prev);
        }
    }
    return res;
}


// show_if == 0 dont show board
// show_if = ms, show board if sovle time exceeds ms
void solve_all(std::string path, std::string name = "", int show_if = 0) {
    Solution sln;
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    for (auto& board : from_file(path)) {
        auto start = std::chrono::steady_clock::now();
        bool pass = sln.readBoard(board);
        if (show_if != 0) {
            sln.print(true);
        }
        if (pass) {
            pass = sln.solve();
        }
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != 0 && diff > show_if) {
            sln.print(true);
            printf("#%d of puzzle %s, cost %lldms\n", total, name.c_str(), diff);
        }
        ms += diff;
        if (diff > max_ms) { max_ms = diff; }
        total++;
        if (pass) { ok++; }
    }

    if (total > 0) {
        printf("solved %d of %d %s puzzles, total %lldms, avg %.2fms, max %lldms\n", ok, total, name.c_str(), ms, ms * 1.0 / total, max_ms);
    }
}

void test() {
    solve_all("./easy50.txt", "easy50", 1);
    solve_all("./top95.txt", "top95", 1);
    solve_all("./hardest.txt", "hardest", 1);
}

}

int main()
{
    leetcode::test();
    norvig::test();


}

