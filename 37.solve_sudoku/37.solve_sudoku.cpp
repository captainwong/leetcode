#include "../common/leetcode.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdint.h>

#define ENABLE_NORVIG_CPP 0

#if ENABLE_NORVIG_CPP
#include <optional>
#endif

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

// 同 leetcode 版，使用 norvig 的测例测试表现，不及格。。。
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

#if (ENABLE_NORVIG_CPP && _HAS_CXX17)
// 移植norvig的python为c++版
namespace norvig_cpp {

/*
## Throughout this program we have:
##   r is a row,    e.g. 'A'
##   c is a column, e.g. '3'
##   s is a square, e.g. 'A3'
##   d is a digit,  e.g. '9'
##   u is a unit,   e.g. ['A1','B1','C1','D1','E1','F1','G1','H1','I1']
##   grid is a grid,e.g. 81 non-blank chars, e.g. starting with '.18...7...
##   values is a dict of possible values, e.g. {'A1':'12349', 'A2':'8', ...}
*/

std::ostream& operator << (std::ostream& os, std::vector<char> s) {
    for (auto c : s) { std::cout << c; }
    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<std::string> s) {
    std::cout << '[';
    for (auto c : s) { std::cout << c << ','; }
    std::cout << ']' << std::endl;
    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<std::vector<std::string>> s) {
    std::cout << '[';
    for (auto c : s) { std::cout << c << ','; }
    std::cout << ']';
    return os;
}

std::ostream& operator << (std::ostream& os, std::unordered_set<std::string> set) {
    std::cout << '['; 
    for (auto c : set) { std::cout << c << ','; }
    std::cout << ']';
    return os;
}

class Sudoku {
public:

    template <typename T>
    T sum(std::initializer_list<T> ts) {
        T t;
        auto i = ts.begin();
        std::copy(i->begin(), i->end(), std::back_inserter(t));
        while (++i != ts.end()) {
            std::copy(i->begin(), i->end(), std::back_inserter(t));
        }
        return t;
    }

    template <typename T>
    std::unordered_set<T> vector_to_set(std::vector<T> v) {
        std::unordered_set<T> s; for (auto i : v) { s.insert(i); }
        return s;
    }

    std::vector<char> string_to_char_vec(std::string s) {
        std::vector<char> ret;
        std::copy(s.begin(), s.end(), std::back_inserter(ret));
        return ret;
    }

    template <typename T>
    std::vector<std::string> cross(T a, T b) {
        std::vector<std::string> c;
        for (auto i : a) {
            for (auto j : b) {
                std::string s;
                s.push_back(i);
                s.push_back(j);
                c.push_back(s);
            }
        }
        return c;
    }

    template <typename T>
    std::vector<std::string> cross(T a, char b) {
        std::vector<std::string> c;
        for (auto i : a) {
            std::string s; s.push_back(i); s.push_back(b);
            c.push_back(s);
        }
        return c;
    }

    template <typename T>
    std::vector<std::string> cross_r(T a, char b) {
        std::vector<std::string> c;
        for (auto i : a) {
            std::string s; s.push_back(b); s.push_back(i);
            c.push_back(s);
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> cross_for(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : b) {
            c.push_back(cross(a, i));
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> cross_for_r(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : b) {
            c.push_back(cross_r(a, i));
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> corss_v(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : a) {
            for (auto j : b) {
                c.push_back(cross(i, j));
            }
        }
        return c;
    }

    template<typename A, typename B>
    bool contains(const A& a, const B& b) {
        for (auto i : a) { if (i == b) { return true; } }
        return false;
    }

    std::unordered_map<std::string, std::vector<std::vector<std::string>>> filter(std::vector<std::vector<std::string>>& v, std::vector<std::string> s) {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> m;
        for (auto i : s) { for (auto j : v) { if (contains(j, i)) { m[i].push_back(j); } } }
        return m;
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> filter(std::unordered_map<std::string, std::vector<std::vector<std::string>>>& map, std::vector<std::string> s) {
        std::unordered_map<std::string, std::unordered_set<std::string>> ret;
        for (auto i : s) { for (auto j : map[i]) { for (auto k : j) { if (k != i) { ret[i].insert(k); } } } }
        return ret;
    }

    template <typename C, typename T>
    C erase_all(const C& c_, T& val) {
        auto c = c_;
        for (auto iter = c.begin(); iter != c.end(); ) {
            if (*iter == val) {
                iter = c.erase(iter);
            } else {
                iter++;
            }
        }
        return c;
    }
    

    template <typename T>
    void print(T t, std::string name = "") {
        std::cout << name << ':' << t << std::endl;
    }

    void print_squares() {
        printf("squres:\n");
        for (size_t i = 0; i < squares.size(); i++) {
            printf("%s,", squares[i].c_str());
            if ((i + 1) % 9 == 0) { printf("\n"); }
        }
    }

    void print_units() {
        printf("units:\n");
        for (auto i : units) {
            std::cout << i.first << ":" << i.second << std::endl;
        }
    }

    void print_peers() {
        printf("peers:\n");
        for (auto i : peers) {
            std::cout << i.first << ":" << i.second << std::endl;
        }
    }

    void print() {
        print(digits, "digits");
        print(rows, "rows");
        print(cols, "cols");
       // print(squares, "squares");
        print_squares();
        print(unitlist, "unitlist");
        print_units();
        print_peers();
    }

    bool equals(std::vector<std::string> a, std::vector<std::string> b) {
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        return a == b;
    }

    template <typename T>
    bool equals(T a, T b) {
        for (auto i : a) {
            bool pass = false;
            for (auto j : b) {
                if (equals(i, j)) { pass = true; break; }
            }
            if (!pass) { return false; }
        }
        return true;
    }

    template <typename Iterable, typename Func>
    bool all(Iterable iterable, Func func) {
        for (auto i : iterable) {
            if (!func(i)) { return false; }
        }
        return true;
    }

    
    std::vector<char> digits = string_to_char_vec("123456789");
    std::vector<char> rows = string_to_char_vec("ABCDEFGHI");
    std::vector<char> cols = digits;
    std::vector<std::string> squares = cross(rows, cols);
    std::vector<std::vector<std::string>> unitlist = sum({ 
        cross_for(rows, cols), 
        cross_for_r(cols, rows), 
        corss_v<std::vector<std::vector<char>>>(
            { string_to_char_vec("ABC"), string_to_char_vec("DEF"), string_to_char_vec("GHI") },
            { string_to_char_vec("123"), string_to_char_vec("456"), string_to_char_vec("789") } ),
    });
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> units = filter(unitlist, squares);
    std::unordered_map<std::string, std::unordered_set<std::string>> peers = filter(units, squares);

    void test() {
        assert(squares.size() == 81);
        assert(unitlist.size() == 27);
        for (auto s : squares) {
            assert(units[s].size() == 3);
            assert(peers[s].size() == 20);
        }
        assert(equals(units["C2"], 
                      std::vector<std::vector<std::string>>{ 
                            { "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2" },
                            { "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9" },
                            { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" } }
        ));
        assert(peers["C2"] == 
               std::unordered_set<std::string>({
                   "A2", "B2", "D2", "E2", "F2", "G2", "H2", "I2",
                   "C1", "C3", "C4", "C5", "C6", "C7", "C8", "C9",
                   "A1", "A3", "B1", "B3"}));

        printf("All tests pass.\n");
    }

    // ################ Parse a Grid ################

    std::optional<std::unordered_map<std::string, std::unordered_set<char>>> parse_grid(std::string grid) {
        std::unordered_map<std::string, std::unordered_set<char>> values;
        for (auto s : squares) { values[s] = vector_to_set(digits); }
        for (auto i : grid_values(grid)) {
            if (contains(digits, i.second)) {
                auto opt = assign(values, i.first, i.second);
                if (!opt) {
                    return std::nullopt;
                }
            }
        }
        return values;
    }

    std::unordered_map<std::string, char> grid_values(string grid) {
        auto chars = string_to_char_vec(grid);
        assert(chars.size() == 81);
        std::unordered_map<std::string, char> m;
        for (size_t i = 0; i < squares.size(); i++) {
            m[squares[i]] = chars[i];
        }
        return m;
    }


    // ################ Constraint Propagation ################

    // Eliminate all the other values (except d) from values[s] and propagate.
    // Return values, except return False if a contradiction is detected.
    std::optional<std::unordered_map<std::string, std::unordered_set<char>>> assign(std::unordered_map<std::string, std::unordered_set<char>>& values, std::string s, char d) {
        auto other_values = erase_all(values[s], d);
        for (auto d2 : other_values) {
            if (!eliminate(values, s, d2)) { return std::nullopt; }            
        }
        return values;
    }

    // Eliminate d from values[s]; propagate when values or places <= 2.
    // Return values, except return False if a contradiction is detected.
    std::optional<std::unordered_map<std::string, std::unordered_set<char>>> eliminate(std::unordered_map<std::string, std::unordered_set<char>>& values, std::string s, char d) {
        if (!contains(values[s], d)) { return values; }
        values[s] = erase_all(values[s], d);

        // (1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
        if (values[s].empty()) {
            return std::nullopt;
        } else if (values[s].size() == 1) {
            auto d2 = *values[s].begin();
            if (!all(peers[s], [this, &values, d2](std::string s2) {return eliminate(values, s2, d2); })) {
                return std::nullopt;
            }/*
            for (auto s2 : peers[s]) {
                if (!eliminate(values, s2, d2)) {
                    return std::nullopt;
                }
            }*/
        }

        // (2) If a unit u is reduced to only one place for a value d, then put it there.
        for (auto u : units[s]) {
            std::vector<std::string> dplaces;
            for (auto ss : u) {
                for (auto i : values[ss]) {
                    if (i == d) {
                        dplaces.push_back(ss);
                        break;
                    }
                }
            }

            if (dplaces.empty()) {
                return std::nullopt;
            } else if (dplaces.size() == 1) {
                if (!assign(values, dplaces[0], d)) {
                    return std::nullopt;
                }
            }
        }
        return values;
    }


    // ################ Display as 2-D grid ################

    template<typename T, typename C>
    C join(T t, C c) {
        C r;
        auto iter = t.cbegin();
        auto end = t.cend();
        if (iter != end) {
            r = *iter++;
        }
        for (; iter != end; iter++) {
            r += c;
            r += *iter;
        }
        return r;
    }

    std::string center(std::string s, size_t length, char c = ' ') {
        if (s.size() >= length) { return s; }
        size_t left = (length - s.size()) / 2;
        if (left == 0) { s.push_back(c); return s; }
        std::string r(left, c); r += s; r += std::string(left, c);
        return r;
    }

    template <typename T>
    std::string vec2str(T v) {
        std::string s; std::copy(v.begin(), v.end(), std::back_inserter(s));
        return s;
    }

    void display(std::unordered_map<std::string, std::unordered_set<char>>& values) {
        size_t width = 0;
        for (auto s : squares) {
            width = std::max(width, values.find(s)->second.size());
        }
        width++;
        std::string line = join(std::vector<std::string>(3, std::string(width * 3, '-')), std::string("+"));
        for (auto r : rows) {
            for (auto c : cols) {
                printf("%s%s", center(vec2str(values[vec2str(std::vector{ r, c })]), width).c_str(), 
                       std::string(contains(std::string("36"), c) ? "|" : "").c_str());
            }
            printf("\n");
            if (contains(std::string("CF"), r)) {
                printf("%s\n", line.c_str());
            }
        }
        printf("\n");
    }


    // ################ Search ################

    std::optional<std::unordered_map<std::string, std::unordered_set<char>>> solve(std::string grid) {
        auto values = parse_grid(grid);
        return search(values);
    }

    template <typename T>
    T deep_copy(const T& t) {
        auto r = t;
        return r;
    }

    // Using depth-first search and propagation, try all possible values.
    std::optional<std::unordered_map<std::string, std::unordered_set<char>>> search(std::optional<std::unordered_map<std::string, std::unordered_set<char>>>& values) {
        if (!values) { return std::nullopt; }
        auto& values_ = *values;
        if (all(squares, [&values_](std::string s) {return values_[s].size() == 1; })) {
            return values;
        }

        // Chose the unfilled square s with the fewest possibilities
        size_t n = 9999999;
        std::string str = squares[0];
        for (auto s : squares) {
            auto sz = values_[s].size();
            if (sz > 1) {
                if (n > sz) {
                    n = sz;
                    str = s;
                }
            }
        }
        std::unordered_map<std::string, std::unordered_set<char>> vd;
        for (auto d : values_[str]) {
            vd = (values_);
            auto va = assign(vd, str, d);
            if (va = search(va)) {
                return va;
            }
        }
        return std::nullopt;
    }
};


vector<std::string> from_file(std::string path) {
    vector<std::string> res;
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
            std::string board;
            for (int i = 0; i < 9; i++) {
                std::string line;
                for (int j = 0; j < 9; j++) {
                    int val = str[i * 9 + j];
                    if ('1' <= val && val <= '9') {
                        line.push_back(val);
                    } else if (val == '.' || val == '0') {
                        line.push_back('.');
                    } else {
                        return res;
                    }
                }
                board += line;
            }
            res.push_back(board);
            prev = pos + 1;
            pos = content.find_first_of('\n', prev);
        }
    }
    return res;
}

//
//// show_if == 0 dont show board
//// show_if = ms, show board if sovle time exceeds ms
//void solve_all(vector<std::string> grids, std::string name = "", int show_if = 0) {
//    int total = 0, ok = 0;
//    long long ms = 0, max_ms = 0;
//    for (auto& grid : grids) {
//        auto start = std::chrono::steady_clock::now();
//        bool pass = sln.readBoard(board);
//        if (show_if != 0) {
//            sln.print(true);
//        }
//        if (pass) {
//            pass = sln.solve();
//        }
//        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
//        if (show_if != 0 && diff > show_if) {
//            sln.print(true);
//            printf("#%d of puzzle %s, cost %lldms\n", total, name.c_str(), diff);
//        }
//        ms += diff;
//        if (diff > max_ms) { max_ms = diff; }
//        total++;
//        if (pass) { ok++; }
//    }
//
//    if (total > 0) {
//        printf("solved %d of %d %s puzzles, total %lldms, avg %.2fms, max %lldms\n", ok, total, name.c_str(), ms, ms * 1.0 / total, max_ms);
//    }
//}

//void test() {
//    solve_all("./easy50.txt", "easy50", 1);
//    solve_all("./top95.txt", "top95", 1);
//    solve_all("./hardest.txt", "hardest", 1);
//}

void test() {
    Sudoku sudoku;
    sudoku.print();
    sudoku.test();

    std::string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    std::string grid2 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    std::string hard1 = ".....6....59.....82....8....45........3........6..3.54...325..6..................";

    auto v = sudoku.solve(grid1);
    if (v) {
        sudoku.display(*v);
    }
    v = sudoku.solve(grid2);
    if (v) {
        sudoku.display(*v);
    }
    v = sudoku.solve(hard1); // can't solve
    if (v) {
        sudoku.display(*v);
    }
}

}
#endif


// 移植norvig的python为c++版，不用 std::optional
namespace norvig_cpp_without_std_optional {

/*
## Throughout this program we have:
##   r is a row,    e.g. 'A'
##   c is a column, e.g. '3'
##   s is a square, e.g. 'A3'
##   d is a digit,  e.g. '9'
##   u is a unit,   e.g. ['A1','B1','C1','D1','E1','F1','G1','H1','I1']
##   grid is a grid,e.g. 81 non-blank chars, e.g. starting with '.18...7...
##   values is a dict of possible values, e.g. {'A1':'12349', 'A2':'8', ...}
*/

std::ostream& operator << (std::ostream& os, std::vector<char> s) {
    for (auto c : s) { std::cout << c; }
    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<std::string> s) {
    std::cout << '[';
    for (auto c : s) { std::cout << c << ','; }
    std::cout << ']' << std::endl;
    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<std::vector<std::string>> s) {
    std::cout << '[';
    for (auto c : s) { std::cout << c << ','; }
    std::cout << ']';
    return os;
}

std::ostream& operator << (std::ostream& os, std::unordered_set<std::string> set) {
    std::cout << '[';
    for (auto c : set) { std::cout << c << ','; }
    std::cout << ']';
    return os;
}

class Sudoku {
public:

    template <typename T>
    T sum(std::initializer_list<T> ts) {
        T t;
        auto i = ts.begin();
        std::copy(i->begin(), i->end(), std::back_inserter(t));
        while (++i != ts.end()) {
            std::copy(i->begin(), i->end(), std::back_inserter(t));
        }
        return t;
    }

    template <typename T>
    std::unordered_set<T> vector_to_set(std::vector<T> v) {
        std::unordered_set<T> s; for (auto i : v) { s.insert(i); }
        return s;
    }

    std::vector<char> string_to_char_vec(std::string s) {
        std::vector<char> ret;
        std::copy(s.begin(), s.end(), std::back_inserter(ret));
        return ret;
    }

    template <typename T>
    std::vector<std::string> cross(T a, T b) {
        std::vector<std::string> c;
        for (auto i : a) {
            for (auto j : b) {
                std::string s;
                s.push_back(i);
                s.push_back(j);
                c.push_back(s);
            }
        }
        return c;
    }

    template <typename T>
    std::vector<std::string> cross(T a, char b) {
        std::vector<std::string> c;
        for (auto i : a) {
            std::string s; s.push_back(i); s.push_back(b);
            c.push_back(s);
        }
        return c;
    }

    template <typename T>
    std::vector<std::string> cross_r(T a, char b) {
        std::vector<std::string> c;
        for (auto i : a) {
            std::string s; s.push_back(b); s.push_back(i);
            c.push_back(s);
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> cross_for(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : b) {
            c.push_back(cross(a, i));
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> cross_for_r(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : b) {
            c.push_back(cross_r(a, i));
        }
        return c;
    }

    template <typename T>
    std::vector<std::vector<std::string>> corss_v(T a, T b) {
        std::vector<std::vector<std::string>> c;
        for (auto i : a) {
            for (auto j : b) {
                c.push_back(cross(i, j));
            }
        }
        return c;
    }

    template<typename A, typename B>
    bool contains(const A& a, const B& b) {
        for (auto i : a) { if (i == b) { return true; } }
        return false;
    }

    std::unordered_map<std::string, std::vector<std::vector<std::string>>> filter(std::vector<std::vector<std::string>>& v, std::vector<std::string> s) {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> m;
        for (auto i : s) { for (auto j : v) { if (contains(j, i)) { m[i].push_back(j); } } }
        return m;
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> filter(std::unordered_map<std::string, std::vector<std::vector<std::string>>>& map, std::vector<std::string> s) {
        std::unordered_map<std::string, std::unordered_set<std::string>> ret;
        for (auto i : s) { for (auto j : map[i]) { for (auto k : j) { if (k != i) { ret[i].insert(k); } } } }
        return ret;
    }

    template <typename C, typename T>
    C erase_all(const C& c_, T& val) {
        auto c = c_;
        for (auto iter = c.begin(); iter != c.end(); ) {
            if (*iter == val) {
                iter = c.erase(iter);
            } else {
                iter++;
            }
        }
        return c;
    }


    template <typename T>
    void print(T t, std::string name = "") {
        std::cout << name << ':' << t << std::endl;
    }

    void print_squares() {
        printf("squres:\n");
        for (size_t i = 0; i < squares.size(); i++) {
            printf("%s,", squares[i].c_str());
            if ((i + 1) % 9 == 0) { printf("\n"); }
        }
    }

    void print_units() {
        printf("units:\n");
        for (auto i : units) {
            std::cout << i.first << ":" << i.second << std::endl;
        }
    }

    void print_peers() {
        printf("peers:\n");
        for (auto i : peers) {
            std::cout << i.first << ":" << i.second << std::endl;
        }
    }

    void print() {
        print(digits, "digits");
        print(rows, "rows");
        print(cols, "cols");
        // print(squares, "squares");
        print_squares();
        print(unitlist, "unitlist");
        print_units();
        print_peers();
    }

    bool equals(std::vector<std::string> a, std::vector<std::string> b) {
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        return a == b;
    }

    template <typename T>
    bool equals(T a, T b) {
        for (auto i : a) {
            bool pass = false;
            for (auto j : b) {
                if (equals(i, j)) { pass = true; break; }
            }
            if (!pass) { return false; }
        }
        return true;
    }

    template <typename Iterable, typename Func>
    bool all(Iterable iterable, Func func) {
        for (auto i : iterable) {
            if (!func(i)) { return false; }
        }
        return true;
    }


    std::vector<char> digits = string_to_char_vec("123456789");
    std::vector<char> rows = string_to_char_vec("ABCDEFGHI");
    std::vector<char> cols = digits;
    std::vector<std::string> squares = cross(rows, cols);
    std::vector<std::vector<std::string>> unitlist = sum({
        cross_for(rows, cols),
        cross_for_r(cols, rows),
        corss_v<std::vector<std::vector<char>>>(
            { string_to_char_vec("ABC"), string_to_char_vec("DEF"), string_to_char_vec("GHI") },
            { string_to_char_vec("123"), string_to_char_vec("456"), string_to_char_vec("789") }),
                                                         });
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> units = filter(unitlist, squares);
    std::unordered_map<std::string, std::unordered_set<std::string>> peers = filter(units, squares);

    void test() {
        assert(squares.size() == 81);
        assert(unitlist.size() == 27);
        for (auto s : squares) {
            assert(units[s].size() == 3);
            assert(peers[s].size() == 20);
        }
        assert(equals(units["C2"],
                      std::vector<std::vector<std::string>>{
                          { "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2" },
                          { "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9" },
                      { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" } }
        ));
        assert(peers["C2"] ==
               std::unordered_set<std::string>({
                   "A2", "B2", "D2", "E2", "F2", "G2", "H2", "I2",
                   "C1", "C3", "C4", "C5", "C6", "C7", "C8", "C9",
                   "A1", "A3", "B1", "B3" }));

        printf("All tests pass.\n");
    }

    // ################ Parse a Grid ################

    bool parse_grid(std::string grid, std::unordered_map<std::string, std::unordered_set<char>>& values) {
        for (auto s : squares) { values[s] = vector_to_set(digits); }
        for (auto i : grid_values(grid)) {
            if (contains(digits, i.second)) {
                if (!assign(values, i.first, i.second)) {
                    return false;
                }
            }
        }
        return true;
    }

    std::unordered_map<std::string, char> grid_values(string grid) {
        auto chars = string_to_char_vec(grid);
        assert(chars.size() == 81);
        std::unordered_map<std::string, char> m;
        for (size_t i = 0; i < squares.size(); i++) {
            m[squares[i]] = chars[i];
        }
        return m;
    }


    // ################ Constraint Propagation ################

    // Eliminate all the other values (except d) from values[s] and propagate.
    // Return values, except return False if a contradiction is detected.
    bool assign(std::unordered_map<std::string, std::unordered_set<char>>& values, std::string s, char d) {
        auto other_values = erase_all(values[s], d);
        for (auto d2 : other_values) {
            if (!eliminate(values, s, d2)) { return false; }
        }
        return true;
    }

    // Eliminate d from values[s]; propagate when values or places <= 2.
    // Return values, except return False if a contradiction is detected.
    bool eliminate(std::unordered_map<std::string, std::unordered_set<char>>& values, std::string s, char d) {
        if (!contains(values[s], d)) { return true; }
        values[s] = erase_all(values[s], d);

        // (1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
        if (values[s].empty()) {
            return false;
        } else if (values[s].size() == 1) {
            auto d2 = *values[s].begin();
            if (!all(peers[s], [this, &values, d2](std::string s2) { return eliminate(values, s2, d2); })) {
                return false;
            }
        }

        // (2) If a unit u is reduced to only one place for a value d, then put it there.
        for (auto u : units[s]) {
            std::vector<std::string> dplaces;
            for (auto ss : u) {
                for (auto i : values[ss]) {
                    if (i == d) {
                        dplaces.push_back(ss);
                        break;
                    }
                }
            }

            if (dplaces.empty()) {
                return false;
            } else if (dplaces.size() == 1) {
                if (!assign(values, dplaces[0], d)) {
                    return false;
                }
            }
        }
        return true;
    }


    // ################ Display as 2-D grid ################

    template<typename T, typename C>
    C join(T t, C c) {
        C r;
        auto iter = t.cbegin();
        auto end = t.cend();
        if (iter != end) {
            r = *iter++;
        }
        for (; iter != end; iter++) {
            r += c;
            r += *iter;
        }
        return r;
    }

    std::string center(std::string s, size_t length, char c = ' ') {
        if (s.size() >= length) { return s; }
        size_t left = (length - s.size()) / 2;
        if (left == 0) { s.push_back(c); return s; }
        std::string r(left, c); r += s; r += std::string(left, c);
        return r;
    }

    template <typename T>
    std::string vec2str(T v) {
        std::string s; std::copy(v.begin(), v.end(), std::back_inserter(s));
        return s;
    }

    void display(const std::unordered_map<std::string, std::unordered_set<char>>& values) {
        size_t width = 0;
        for (auto s : squares) {
            width = std::max(width, values.find(s)->second.size());
        }
        width++;
        std::string line = join(std::vector<std::string>(3, std::string(width * 3, '-')), std::string("+"));
        for (auto r : rows) {
            for (auto c : cols) {
                std::string s; s.push_back(r); s.push_back(c);
                printf("%s%s", center(vec2str(values.find(s)->second), width).c_str(),
                       std::string(contains(std::string("36"), c) ? "|" : "").c_str());
            }
            printf("\n");
            if (contains(std::string("CF"), r)) {
                printf("%s\n", line.c_str());
            }
        }
        printf("\n");
    }

    void display(const std::unordered_map<std::string, char>& values) {
        size_t width = 2;
        std::string line = join(std::vector<std::string>(3, std::string(width * 3, '-')), std::string("+"));
        for (auto r : rows) {
            for (auto c : cols) {
                std::string s; s.push_back(r); s.push_back(c);
                printf("%s%s", center(std::string(1, values.find(s)->second), width).c_str(),
                       std::string(contains(std::string("36"), c) ? "|" : "").c_str());
            }
            printf("\n");
            if (contains(std::string("CF"), r)) {
                printf("%s\n", line.c_str());
            }
        }
        printf("\n");
    }


    // ################ Search ################

    bool solve(std::string grid, std::unordered_map<std::string, std::unordered_set<char>>& values) {
        values.clear();
        if (parse_grid(grid, values) && search(values)) {
            return true;
        }
        return false;
    }

    template <typename T>
    T deep_copy(const T& t) {
        auto r = t;
        return r;
    }

    // Using depth-first search and propagation, try all possible values.
    bool search(std::unordered_map<std::string, std::unordered_set<char>>& values) {
        if (all(squares, [&values](std::string s) {return values[s].size() == 1; })) {
            return true;
        }

        // Chose the unfilled square s with the fewest possibilities
        size_t n = 9999999;
        std::string str = squares[0];
        for (auto s : squares) {
            auto sz = values[s].size();
            if (sz > 1) {
                if (n > sz) {
                    n = sz;
                    str = s;
                }
            }
        }
        for (auto d : values[str]) {
            auto vd = (values);
            if (assign(vd, str, d)) {
                if (search(vd)) {
                    values = vd;
                    return true;
                }
            }
        }
        return false;
    }
};


vector<std::string> from_file(std::string path) {
    vector<std::string> res;
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
            std::string board;
            for (int i = 0; i < 9; i++) {
                std::string line;
                for (int j = 0; j < 9; j++) {
                    int val = str[i * 9 + j];
                    if ('1' <= val && val <= '9') {
                        line.push_back(val);
                    } else if (val == '.' || val == '0') {
                        line.push_back('.');
                    } else {
                        return res;
                    }
                }
                board += line;
            }
            res.push_back(board);
            prev = pos + 1;
            pos = content.find_first_of('\n', prev);
        }
    }
    return res;
}


// show_if == -1 dont show board
// show_if = ms >= 0, show board if sovle time exceeds ms
void solve_all(vector<std::string> grids, std::string name = "", int show_if = 0) {
    Sudoku sudoku;
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    std::unordered_map<std::string, std::unordered_set<char>> values;
    for (const auto& grid : grids) {
        auto start = std::chrono::steady_clock::now();        
        bool pass = sudoku.solve(grid, values);        
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != -1 && diff > show_if) {
            sudoku.display(sudoku.grid_values(grid));
            sudoku.display(values);
            printf("#%d of puzzle %s, cost %lldms\n", total + 1, name.c_str(), diff);
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

//void test() {
//    solve_all("./easy50.txt", "easy50", 1);
//    solve_all("./top95.txt", "top95", 1);
//    solve_all("./hardest.txt", "hardest", 1);
//}

void test(int show_if = 0) {
    Sudoku sudoku;
    //sudoku.print();
    sudoku.test();

    //std::string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    //std::string grid2 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    //std::string hard1 = ".....6....59.....82....8....45........3........6..3.54...325..6.................."; // i7-8700 took 40s to solve

    // /*std::unordered_map<std::string, std::unordered_set<char>> values;
    //if (sudoku.solve(grid1, values)) {
    //    sudoku.display(values);
    //}
    //if (sudoku.solve(grid2, values)) {
    //    sudoku.display(values);
    //}
    //if (sudoku.solve(hard1, values)) {
    //    sudoku.display(values);
    //}*/
    ////solve_all(std::vector<std::string>{grid1, grid2, /*hard1*/ }, "test");
    //
    //

    

    solve_all(from_file("./easy50.txt"), "easy50", show_if);
    solve_all(from_file("./top95.txt"), "top95", show_if);
    solve_all(from_file("./hardest.txt"), "hardest", show_if);
}

}

int main(int argc, char** argv)
{
    //leetcode::test();
    //norvig::test();
    //norvig_cpp::test();

    int show_if = 0;
    if (argc > 1) {
        show_if = atoi(argv[1]);
    }
    norvig_cpp_without_std_optional::test(show_if);
}

