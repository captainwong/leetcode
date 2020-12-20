#include "../common/leetcode.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <stdint.h>

//
//#ifdef _WIN32
//#define ENABLE_NORVIG_CPP 1
//#else 
//#define ENABLE_NORVIG_CPP 0 
//#endif

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
// 移植norvig的python为c++版，使用std::optional，测试hard1太慢了
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


// show_if == -1 dont show board
// show_if = ms >= 0, show board if sovle time exceeds ms
void solve_all(vector<std::string> grids, std::string name = "", int show_if = 0) {
    Sudoku sudoku;
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    std::unordered_map<std::string, std::unordered_set<char>> values;
    for (const auto& grid : grids) {
        auto start = std::chrono::steady_clock::now();
        auto values = sudoku.solve(grid);
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != -1 && diff > show_if) {
            sudoku.display(sudoku.grid_values(grid));
            if (values) {
                sudoku.display(*values);
            } else {
                printf("No solution\n");
            }
            printf("#%d of puzzle %s, cost %lldms\n", total + 1, name.c_str(), diff);
        }
        ms += diff;
        if (diff > max_ms) { max_ms = diff; }
        total++;
        if (values) { ok++; }
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

void test(int show_if = 0) {
    Sudoku sudoku;
    sudoku.print();
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

// https://github.com/pauek/norvig-sudoku/blob/master/sudoku.en.cc
//namespace norgiv_cc {
//using namespace std;
//
//class Possible {
//    vector<bool> _b;
//public:
//    Possible() : _b(9, true) {}
//    bool   is_on(int i) const { return _b[i - 1]; }
//    int    count()      const { return std::count(_b.begin(), _b.end(), true); }
//    void   eliminate(int i) { _b[i - 1] = false; }
//    int    val()        const {
//        auto it = find(_b.begin(), _b.end(), true);
//        return (it != _b.end() ? 1 + (it - _b.begin()) : -1);
//    }
//    string str(int wth) const;
//};
//
//string Possible::str(int width) const {
//    string s(width, ' ');
//    int k = 0;
//    for (int i = 1; i <= 9; i++) {
//        if (is_on(i)) s[k++] = '0' + i;
//    }
//    return s;
//}
//
//class Sudoku {
//    vector<Possible> _cells;
//    static vector< vector<int> > _group, _neighbors, _groups_of;
//
//    bool     eliminate(int k, int val);
//public:
//    Sudoku(string s);
//    static void init();
//
//    Possible possible(int k) const { return _cells[k]; }
//    bool     is_solved() const;
//    bool     assign(int k, int val);
//    int      least_count() const;
//    void     write(ostream& o) const;
//
//    static void print(const char* name, const vector< vector<int> >& v) {
//        printf("%s:\n[", name);
//        for (size_t i = 0; i < v.size(); i++) {
//            printf("#%d: [", i);
//            for (size_t j = 0; j < v[i].size(); j++) {
//                printf("%d, ", v[i][j]);
//            }
//            printf("], \n");
//        }
//        printf("]\n");
//    }
//
//    static void print() {
//        print("_group", _group);
//        print("_neighbors", _neighbors);
//        print("_groups_of", _groups_of);
//    }
//};
//
//bool Sudoku::is_solved() const {
//    for (int k = 0; k < _cells.size(); k++) {
//        if (_cells[k].count() != 1) {
//            return false;
//        }
//    }
//    return true;
//}
//
//void Sudoku::write(ostream& o) const {
//    int width = 1;
//    for (int k = 0; k < _cells.size(); k++) {
//        width = max(width, 1 + _cells[k].count());
//    }
//    const string sep(3 * width, '-');
//    for (int i = 0; i < 9; i++) {
//        if (i == 3 || i == 6) {
//            o << sep << "+-" << sep << "+" << sep << endl;
//        }
//        for (int j = 0; j < 9; j++) {
//            if (j == 3 || j == 6) o << "| ";
//            o << _cells[i * 9 + j].str(width);
//        }
//        o << endl;
//    }
//}
//
//vector< vector<int> >
//Sudoku::_group(27), Sudoku::_neighbors(81), Sudoku::_groups_of(81);
//
//void Sudoku::init() {
//    for (int i = 0; i < 9; i++) {
//        for (int j = 0; j < 9; j++) {
//            const int k = i * 9 + j;
//            const int x[3] = { i, 9 + j, 18 + (i / 3) * 3 + j / 3 };
//            for (int g = 0; g < 3; g++) {
//                _group[x[g]].push_back(k);
//                _groups_of[k].push_back(x[g]);
//            }
//        }
//    }
//    for (int k = 0; k < _neighbors.size(); k++) {
//        for (int x = 0; x < _groups_of[k].size(); x++) {
//            for (int j = 0; j < 9; j++) {
//                int k2 = _group[_groups_of[k][x]][j];
//                if (k2 != k) _neighbors[k].push_back(k2);
//            }
//        }
//    }
//}
//
//bool Sudoku::assign(int k, int val) {
//    for (int i = 1; i <= 9; i++) {
//        if (i != val) {
//            if (!eliminate(k, i)) return false;
//        }
//    }
//    return true;
//}
//
//bool Sudoku::eliminate(int k, int val) {
//    if (!_cells[k].is_on(val)) {
//        return true;
//    }
//    _cells[k].eliminate(val);
//    const int N = _cells[k].count();
//    if (N == 0) {
//        return false;
//    } else if (N == 1) {
//        const int v = _cells[k].val();
//        for (int i = 0; i < _neighbors[k].size(); i++) {
//            if (!eliminate(_neighbors[k][i], v)) return false;
//        }
//    }
//    for (int i = 0; i < _groups_of[k].size(); i++) {
//        const int x = _groups_of[k][i];
//        int n = 0, ks;
//        for (int j = 0; j < 9; j++) {
//            const int p = _group[x][j];
//            if (_cells[p].is_on(val)) {
//                n++, ks = p;
//            }
//        }
//        if (n == 0) {
//            return false;
//        } else if (n == 1) {
//            if (!assign(ks, val)) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//int Sudoku::least_count() const {
//    int k = -1, min;
//    for (int i = 0; i < _cells.size(); i++) {
//        const int m = _cells[i].count();
//        if (m > 1 && (k == -1 || m < min)) {
//            min = m, k = i;
//        }
//    }
//    return k;
//}
//
//Sudoku::Sudoku(string s)
//    : _cells(81)
//{
//    int k = 0;
//    for (int i = 0; i < s.size(); i++) {
//        if (s[i] >= '1' && s[i] <= '9') {
//            if (!assign(k, s[i] - '0')) {
//                cerr << "error" << endl;
//                return;
//            }
//            k++;
//        } else if (s[i] == '0' || s[i] == '.') {
//            k++;
//        }
//    }
//}
//
//unique_ptr<Sudoku> solve(unique_ptr<Sudoku> S) {
//    if (S == nullptr || S->is_solved()) {
//        return S;
//    }
//    int k = S->least_count();
//    Possible p = S->possible(k);
//    for (int i = 1; i <= 9; i++) {
//        if (p.is_on(i)) {
//            unique_ptr<Sudoku> S1(new Sudoku(*S));
//            if (S1->assign(k, i)) {
//                if (auto S2 = solve(std::move(S1))) {
//                    return S2;
//                }
//            }
//        }
//    }
//    return {};
//}
//
//int main() {
//    Sudoku::init();
//    string line;
//    while (getline(cin, line)) {
//        if (auto S = solve(unique_ptr<Sudoku>(new Sudoku(line)))) {
//            S->write(cout);
//        } else {
//            cout << "No solution";
//        }
//        cout << endl;
//    }
//}
//}

// 在 norvig_cpp_without_std_optional 的基础上继续优化
// 重度参考了 https://github.com/pauek/norvig-sudoku/blob/master/sudoku.en.cc
// 移植到 LeetCode 上的表现：
// 执行用时：16 ms, 在所有 C++ 提交中击败了40.04%的用户
// 内存消耗：7.9 MB, 在所有 C++ 提交中击败了10.43%的用户
// 已经针不戳了
namespace norvig_cpp_optimize {

class Sudoku {
public:
    struct Possible {
        bool p[9];

        Possible() { memset(p, true, sizeof(p)); }
        Possible& operator=(const Possible& rhs) { memcpy(p, rhs.p, sizeof(p)); }

        bool on(int i) const { return p[i - 1]; }
        int count() const { return static_cast<int>(std::count(p, p + sizeof(p), true)); }
        void eliminate(int i) { p[i - 1] = false; }
        int val() const { for (int i = 0; i < sizeof(p); i++) { if (p[i]) { return i + 1; } } return 0; }

        std::string to_string(int width, char c = ' ') const {
            std::string s(width, c);
            int k = 0;
            for (int i = 1; i <= 9; i++) {
                if (on(i)) { s[k++] = '0' + i; }
            }
            return s;
        }
    };

    struct Helper {
        std::vector<std::vector<int>> groups{}; // 9行+9列+9块=27个组，每组9个cell
        std::vector<std::vector<int>> groups_of{}; // 81个位置，代表每个cell所属的组号
        std::vector<std::unordered_set<int>> neighbors{}; // 81个位置，代表每个cell的邻居cell，每个cell有20个邻居

        Helper() {
            init_maximized(); 
            test_inited();
        }

        void init() {
            groups.clear(); groups.resize(27);
            groups_of.clear(); groups_of.resize(81);
            neighbors.clear(); neighbors.resize(81);


            // (1) 初始化组: 每个cell都有3个组：同行，同列，同块

            // 1~9行
            for (int i = 0; i < 9; i++) {
                // 每行9个cell
                for (int j = 0; j < 9; j++) {
                    int k = i * 9 + j;
                    groups[i].push_back(k); // i 对应 0~8 组
                    groups_of[k].push_back(i); // 记录 cell 所属的组号
                }
            }

            // 1~9列
            for (int i = 0; i < 9; i++) {
                // 每列9个cell
                for (int j = 0; j < 9; j++) {
                    int k = i * 9 + j;
                    groups[9 + j].push_back(k); // 9 + j 对应 9~17 组
                    groups_of[k].push_back(9 + j); // 记录 cell 所属的组号
                }
            }

            // 9个格子
            for (int i = 0; i < 9; i++) {
                // 每格9个cell
                for (int j = 0; j < 9; j++) {
                    int k = i * 9 + j;
                    int block = i / 3 * 3 + j / 3;
                    groups[18 + block].push_back(k); // 18 + block 对应 18~26 组
                    groups_of[k].push_back(18 + block); // 记录 cell 所属的组号
                }
            }


            // (2) 初始化邻居
            for (int k = 0; k < 81; k++) { // k: cells 下标
                for (auto g : groups_of[k]) { // g: 组号
                    for (auto kk : groups[g]) { // kk: 组内 cell 下标
                        if (kk != k) {
                            neighbors[k].insert(kk);
                        }
                    }
                }
            }
        }

        void init_maximized() {
            groups.clear(); groups.resize(27);
            groups_of.clear(); groups_of.resize(81);
            neighbors.clear(); neighbors.resize(81);

            // (1) 初始化组: 每个cell都有3个组：同行，同列，同块
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    int k = i * 9 + j;
                    for (int g : {i, 9 + j, 18 + i / 3 * 3 + j / 3}) { // g: 组号
                        groups[g].push_back(k);
                        groups_of[k].push_back(g);
                    }
                }
            }

            // (2) 初始化邻居
            for (int k = 0; k < 81; k++) { // k: cells 下标
                for (auto g : groups_of[k]) { // g: 组号
                    for (auto kk : groups[g]) { // kk: 组内 cell 下标
                        if (kk != k) {
                            neighbors[k].insert(kk);
                        }
                    }
                }
            }
        }

        template <typename T>
        void print(const char* name, const T& t) {
            printf("%s:[\n", name);
            for (size_t i = 0; i < t.size(); i++) {
                printf("#%02zd:[", i);
                for (int j : t[i]) {
                    printf("%d, ", j);
                }
                printf("],\n");
            }
            printf("]\n");
        }

        void test_inited() {
            assert(groups.size() == 27);
            for (const auto& group : groups) {
                assert(group.size() == 9);
            }

            assert(groups_of.size() == 81);
            for (const auto& go : groups_of) {
                assert(go.size() == 3);
            }

            assert(neighbors.size() == 81);
            for (const auto& neighbor : neighbors) {
                assert(neighbor.size() == 20);
            }
        }

        void print_members() {
            print("groups", groups);
            print("groups_of", groups_of);
            print("neighbors", neighbors);
        }
    };

protected:
    std::vector<Possible> cells;
    std::shared_ptr<Helper> helper{};

public:
    Sudoku() : cells(81)
    {
    }

    std::string to_string() const {
        int width = 1;
        for (const auto& cell : cells) {
            width = std::max(width, 1 + cell.count());
        }
        const std::string sep(3 * width, '-');
        std::string res;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                res += cells[i * 9 + j].to_string(width);
                if (j == 2 || j == 5) {
                    res += "|";
                }
            }
            res += "\n";
            if (i == 2 || i == 5) {
                res += sep + "+" + sep + "+" + sep + "\n";
            }
        }
        res += "\n";
        return res;
    }

    static std::string to_string(std::string grid) {
        const std::string sep(6, '-');
        std::string res;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                res.push_back(grid[i * 9 + j] != '0' ? grid[i * 9 + j] : '.');
                res.push_back(' ');
                if (j == 2 || j == 5) {
                    res += "|";
                }
            } 
            res += "\n";
            if (i == 2 || i == 5) {
                res += sep + "+" + sep + "+" + sep + "\n";
            } 
        }
        res += "\n";
        return res;
    }


    Possible possible(int k) const { return cells[k]; }

    // 每个 cell 都仅剩一个备选时说明问题解决
    bool is_solved() const { for (int i = 0; i < 81; i++) { if (cells[i].count() != 1) { return false; } } return true; }

    // 找到备选元素最少的 cell
    int least_count() const {
        int k = -1, mini;
        for (int i = 0; i < 81; i++) {
            int m = cells[i].count();
            if (m > 1 && (k == -1 || m < mini)) {
                mini = m; k = i;
            }
        }
        return k;
    }

    // 在 k 处的 cell 放置 val，排除 k 的所有非 val 的备选，仅剩 val 备选
    bool assign(int k, int val) {
        for (int i = 1; i <= 9; i++) {
            if (i != val && !eliminate(k, i)) return false;
        }
        return true;
    }

    // 移除 k 处 cell 的备选 val
    bool eliminate(int k, int val) {
        if (!cells[k].on(val)) { return true; } // 已经移除过了
        cells[k].eliminate(val); // 移除备选 val

        // (1) If a square is reduced to one value v, then eliminate v from the peers.
        int n = cells[k].count();
        if (n == 0) { // 若移除 val 后 k 没有其他备选了，说明失败了
            return false;
        } else if (n == 1) { // 若移除 val 后 k 仅剩一个备选 v，那么 k 的邻居们就都不能放置 v 了
            int v = cells[k].val();
            for (auto i : helper->neighbors[k]) { // 尝试移除邻居们的备选元素 v
                if (!eliminate(i, v)) { return false; } // 无法移除必然失败
            }
        }

        // (2) If a unit u is reduced to only one place for a value val, then put it there.
        for (auto g : helper->groups_of[k]) { // 遍历 k 所在的组
            int n = 0, k1;
            for (auto kk : helper->groups[g]) { // 遍历组内元素 kk
                if (cells[kk].on(val)) { // 记录 val 在该组内出现的次数 n
                    n++; k1 = kk; // 顺便记录仅能放置 val 的位置 k1
                }
            }
            if (n == 0) { // k 所在的组内至少要出现一次 val
                return false; // 否则不满足数独的特性：每个组内都要包含 1~9 等9个数字
            } else if (n == 1) { // 若组内仅有一个位置 k1 可以放置 val了，尝试放置
                if (!assign(k1, val)) { // 不能放置必然失败
                    return false;
                }
            }
        }

        return true;
    }

    bool parse_grid(std::string grid) {
        if (grid.size() != 81) { return false; }
        cells.clear();
        cells.resize(81);
        int k = 0;
        for (auto c : grid) {
            if ('1' <= c && c <= '9') {
                if (!assign(k++, c - '0')) {
                    return false;
                }
            } else if ('0' == c || '.' == c) {
                k++;
            } else {
                return false;
            }
        }
        return true;
    }

    static std::unique_ptr<Sudoku> search(std::unique_ptr<Sudoku> s) {
        if (!s || s->is_solved()) { return s; }
        int k = s->least_count();
        auto p = s->possible(k);
        for (int i = 1; i <= 9; i++) {
            if (p.on(i)) {
                std::unique_ptr<Sudoku> s1(new Sudoku(*s));
                if (s1->assign(k, i)) {
                    if (auto s2 = search(std::move(s1))) {
                        return s2;
                    }
                }
            }
        }
        return nullptr;
    }

    static std::unique_ptr<Sudoku> solve(std::string grid, std::unique_ptr<Sudoku> s = nullptr) {
        if (!s) {
            s = std::make_unique<Sudoku>();
        }
        if (!s->helper) {
            s->helper = std::make_shared<Helper>();
        }
        if (!s->parse_grid(grid)) { return nullptr; }
        auto ss = search(std::move(s));
        return ss;
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
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    std::unique_ptr<Sudoku> sudoku;    
    for (const auto& grid : grids) {
        auto start = std::chrono::steady_clock::now();
        sudoku = Sudoku::solve(grid, std::move(sudoku));
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != -1 && diff >= show_if) {
            printf("%s\n", Sudoku::to_string(grid).c_str());
            if (sudoku) {
                printf("%s\n", sudoku->to_string().c_str());
            } else {
                printf("No solution\n");
            }
            printf("#%d of puzzle %s, cost %lldms\n", total + 1, name.c_str(), diff);
        }
        ms += diff;
        if (diff > max_ms) { max_ms = diff; }
        total++;
        if (sudoku) { ok++; }
    }

    if (total > 0) {
        printf("solved %d of %d %s puzzles, total %lldms, avg %.2fms, max %lldms\n", ok, total, name.c_str(), ms, ms * 1.0 / total, max_ms);
    }
}

void test(int show_if = 0) {

    std::string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    std::string grid2 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    std::string hard1 = ".....6....59.....82....8....45........3........6..3.54...325..6..................";

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

    solve_all(std::vector<std::string>{grid1, grid2, hard1 }, "test");
    solve_all(from_file("./easy50.txt"), "easy50", show_if);
    solve_all(from_file("./top95.txt"), "top95", show_if);
    solve_all(from_file("./hardest.txt"), "hardest", show_if);
}

}

// 继续在 norvig_cpp_optimize 的基础上优化为 C 版本
// 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
// 内存消耗：6.7 MB, 在所有 C++ 提交中击败了45.52%的用户
namespace norvig_c {

const int N = 81;
const int NEIGHBORS = 20;
const int GROUPS_OF = 3;
const int GROUPS = 27;

bool Cells[N][9]; // 81 格，每格初始有9种选择，值为 false 表示已经消除过了
int neighbors[N][NEIGHBORS]; // 每格有20个邻居
int groups_of[N][GROUPS_OF]; // 每格属于3个组
int groups[GROUPS][9]; // 27个组 = 9行+9列+9块
int spaces = 81; // 初始情况有81个未填空格

// 第 k 个 cell 是否可以选择 val
bool cell_on(bool cells[N][9], int k, int val) {
    return cells[k][val - 1];
}

// 消除第 k 个 cell 的可选值 val
void cell_eliminate(bool cells[N][9], int k, int val) {
    cells[k][val - 1] = false;
}

// 找到第 k 个 cell 的第一个可选值
int cell_val(bool cells[N][9], int k) {
    for (int i = 0; i < 9; i++) {
        if (cells[k][i]) {
            return i + 1;
        }
    }
    return -1;
}

// 计算第 k 个 cell 的可选数值数量
int cell_count(bool cells[N][9], int k) {
    int n = 0;
    for (int i = 0; i < 9; i++) {
        if (cells[k][i]) { n++; }
    }
    return n;
}

// 获取可选数量最少的 cell
int least_cell_count(bool cells[N][9]) {
    int k = -1, n;
    for (int i = 0; i < N; i++) {
        int nn = cell_count(cells, i);
        if (nn > 1 && (k == -1 || nn < n)) {
            k = i; n = nn;
        }
    }
    return k;
}

bool solved(bool cells[N][9]) {
    for (int k = 0; k < N; k++) {
        if (cell_count(cells, k) != 1) { return false; }
    }
    return true;
}

// 初始化辅助结构体，用户调用 solve 之前手动调用一次即可
void init() {
    memset(neighbors, -1, sizeof(neighbors));
    memset(groups, -1, sizeof(groups));
    memset(groups_of, -1, sizeof(groups_of));

    // (1) 初始化组: 每个cell都有3个组：同行，同列，同块
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int k = i * 9 + j;
            for (int g : {i, 9 + j, 18 + i / 3 * 3 + j / 3}) { // g: 组号
                for (int gg = 0; gg < 9; gg++) {
                    if (groups[g][gg] == k) { break; } // 去重
                    if (groups[g][gg] == -1) {
                        groups[g][gg] = k;
                        break;
                    }
                }
                for (int gg = 0; gg < GROUPS_OF; gg++) {
                    if (groups_of[k][gg] == g) { break; } // 去重
                    if (groups_of[k][gg] == -1) {
                        groups_of[k][gg] = g;
                        break;
                    }
                }
            }
        }
    }

    // (2) 初始化邻居
    for (int k = 0; k < N; k++) { // k: cells 下标
        for (int i = 0; i < 3; i++) { 
            int g = groups_of[k][i]; // g: 组号
            for (int j = 0; j < 9; j++) { 
                int kk = groups[g][j]; // kk: 组内 cell 下标
                if (kk != k) {
                    for (int n = 0; n < NEIGHBORS; n++) {
                        if (neighbors[k][n] == kk) { break; } // 去重
                        if (neighbors[k][n] == -1) {
                            neighbors[k][n] = kk;
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool eliminate(bool cells[N][9], int k, int val);

bool assign(bool cells[N][9], int k, int val) {
    for (int i = 1; i <= 9; i++) {
        if (i != val) {
            if (!eliminate(cells, k, i)) {
                return false;
            }
        }
    }
    spaces--;
    return true;
}

bool eliminate(bool cells[N][9], int k, int val) {
    if (!cell_on(cells, k, val)) { return true; }
    cell_eliminate(cells, k, val);

    // (1) If a square is reduced to one value v, then eliminate v from the peers.
    int n = cell_count(cells, k);
    if (n == 0) { // 若移除 val 后 k 没有其他备选了，说明失败了
        return false;
    } else if (n == 1) { // 若移除 val 后 k 仅剩一个备选 v，那么 k 的邻居们就都不能放置 v 了
        int v = cell_val(cells, k);
        for (int i = 0; i < NEIGHBORS; i++) { // 尝试移除邻居们的备选元素 v
            if (!eliminate(cells, neighbors[k][i], v)) {  // 无法移除必然失败
                return false;
            }
        }
    }

    // (2) If a unit u is reduced to only one place for a value val, then put it there.
    for (int i = 0; i < GROUPS_OF; i++) { // 遍历 k 所在的组
        int g = groups_of[k][i];
        int n = 0, k1;
        for (int j = 0; j < 9; j++) { // 遍历组内元素 kk
            int kk = groups[g][j];
            if (cell_on(cells, kk, val)) { // 记录 val 在该组内出现的次数 n
                n++; k1 = kk; // 顺便记录仅能放置 val 的位置 k1
            }
        }
        if (n == 0) { // k 所在的组内至少要出现一次 val
            return false; // 否则不满足数独的特性：每个组内都要包含 1~9 等9个数字
        } else if (n == 1) { // 若组内仅有一个位置 k1 可以放置 val了，尝试放置
            if (!assign(cells, k1, val)) { // 不能放置必然失败
                return false;
            }
        }
    }

    return true;
}

bool read_grid(const char* grid) {
    if (!grid || strlen(grid) != 81) { return false; }
    memset(Cells, true, sizeof(Cells));
    spaces = 81;
    for (int i = 0; i < 81; i++) {
        if ('1' <= grid[i] && grid[i] <= '9') {
            if (!assign(Cells, i, grid[i] - '0')) {
                return false;
            }
        } else if ('0' == grid[i] || '.' == grid[i]) {

        } else {
            return false;
        }
    }
    return true;
}

bool search(bool cells[N][9]) {
    if (solved(cells)) { return true; }
    int k = least_cell_count(cells);
    for (int val = 1; val <= 9; val++) {
        if (cell_on(cells, k, val)) {
            bool cells1[N][9];
            memcpy(cells1, cells, sizeof(cells1));
            if (assign(cells1, k, val)) {
                if (search(cells1)) {
                    memcpy(cells, cells1, sizeof(cells1));
                    return true;
                }
            }
        }
    }
    return false;
}

bool solve(const char* grid) {
    if (!read_grid(grid)) {
        return false;
    }
    return search(Cells);
}

std::string cells_to_string(bool cells[N][9]) {
    std::string grid(81, '.');
    for (int i = 0; i < N; i++) {
        int val = cell_val(cells, i);
        if (1 <= val && val <= 9) {
            grid[i] = val + '0';
        }
    }
    return grid;
}

typedef void(*OnSolved)(const std::string& grid);


int search(bool cells[N][9], OnSolved on_solved, int solves, int max_solves) {
    if (solved(cells)) { 
        on_solved(cells_to_string(cells));
        return ++solves;
    }
    int k = least_cell_count(cells);
    for (int val = 1; val <= 9; val++) {
        if (cell_on(cells, k, val)) {
            bool cells1[N][9];
            memcpy(cells1, cells, sizeof(cells1));
            if (assign(cells1, k, val)) {
                solves += search(cells1, on_solved, 0, max_solves);
                if (max_solves != 0 && solves >= max_solves) {
                    return solves;
                }
            }
        }
    }
    return solves;
}

// max_solves, 0 for solve all solutions, > 0 for stop if reached
int solve(const char* grid, OnSolved on_solved, int max_solves = 0) {
    if (!read_grid(grid)) {
        return 0;
    }
    return search(Cells, on_solved, 0, max_solves);
}

void print_members() {
    printf("%s:[\n", "groups");
    for (int i = 0; i < 27; i++) {
        printf("#%2d:[", i);
        for (int j = 0; j < 9; j++) {
            printf("%2d, ", groups[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");

    printf("%s:[\n", "groups_of");
    for (int i = 0; i < 81; i++) {
        printf("#%2d:[", i);
        for (int j = 0; j < 3; j++) {
            printf("%2d, ", groups_of[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");

    printf("%s:[\n", "neighbors");
    for (int i = 0; i < 81; i++) {
        printf("#%2d:[", i);
        for (int j = 0; j < 20; j++) {
            printf("%2d, ", neighbors[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");
}
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

void print_cells(bool cells[N][9]) {
    int width = 1;
    for (int i = 0; i < N; i++) {
        width = std::max(width, 1 + cell_count(cells, i));
    }
    const std::string wfm = "%" + std::to_string(width) + "d";
    const std::string sep(3 * width, '-');
    const std::string sepline = sep + "+" + sep + "+" + sep;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf(wfm.c_str(), cell_val(cells, i * 9 + j));
            if (j == 2 || j == 5) {
                printf("|");
            }
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("%s\n", sepline.c_str());
        }
    }
    printf("\n");
}

void print_grid(const char* grid) {
    const std::string sep(6, '-');
    const std::string sepline = sep + "+" + sep + "+" + sep;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", (grid[i * 9 + j] != '0' ? grid[i * 9 + j] : '.'));
            if (j == 2 || j == 5) {
                printf("|");
            }
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("%s\n", sepline.c_str());
        }
    }
    printf("\n");
}

// show_if == -1 dont show board
// show_if = ms >= 0, show board if sovle time exceeds ms
void solve_all(vector<std::string> grids, std::string name = "", int show_if = 0) {
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    for (const auto& grid : grids) {
        std::vector<std::string> solved_gridss;
        auto start = std::chrono::steady_clock::now();
        bool pass = solve(grid.c_str());
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != -1 && diff >= show_if) {
            print_grid(grid.c_str());
            if (pass) {
                print_cells(Cells);
            } else {
                printf("No solution\n");
            }
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

void test(int show_if = 0) {
    init();
    print_members();

    std::string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    std::string grid2 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    std::string hard1 = ".....6....59.....82....8....45........3........6..3.54...325..6.................."; // 924ms on i7-8700, 1400ms on i5-4590

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

    solve_all(std::vector<std::string>{grid1, grid2, hard1 }, "test");
    solve_all(from_file("./easy50.txt"), "easy50", show_if);
    solve_all(from_file("./top95.txt"), "top95", show_if);
    solve_all(from_file("./hardest.txt"), "hardest", show_if);
}



std::vector<std::string> solved_gridss{};
void on_solve(const std::string& grid) {
    solved_gridss.push_back(grid);
}

void solve_all2(vector<std::string> grids, std::string name = "", int show_if = 0) {
    int total = 0, ok = 0;
    long long ms = 0, max_ms = 0;
    for (const auto& grid : grids) {
        solved_gridss.clear();
        auto start = std::chrono::steady_clock::now();
        int solves = solve(grid.c_str(), on_solve, 2); // 最多求2个解
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        if (show_if != -1 && diff >= show_if) {
            print_grid(grid.c_str());
            if (solves == 0) {
                printf("#%d of puzzle %s has No solution\n", total + 1, name.c_str());
            }else {
                printf("#%d of puzzle %s has %s %d solutions:\n", total + 1, name.c_str(), solves > 1 ? "at least" : "", solves);
                for (const auto& solved_grid : solved_gridss) {
                    print_grid(solved_grid.c_str());
                }
            }
            printf("#%d of puzzle %s, cost %lldms\n", total + 1, name.c_str(), diff);
        }
        ms += diff;
        if (diff > max_ms) { max_ms = diff; }
        total++;
        if (solves) { ok++; }
    }

    if (total > 0) {
        printf("solved %d of %d %s puzzles, total %lldms, avg %.2fms, max %lldms\n", ok, total, name.c_str(), ms, ms * 1.0 / total, max_ms);
    }
}

void test2(int show_if = 0) {
    init();
    print_members();

    std::string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    std::string grid2 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    std::string hard1 = ".....6....59.....82....8....45........3........6..3.54...325..6.................."; // 924ms on i7-8700, 1400ms on i5-4590

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

    solve_all2(std::vector<std::string>{grid1, grid2, hard1 }, "test");
    solve_all2(from_file("./easy50.txt"), "easy50", show_if);
    solve_all2(from_file("./top95.txt"), "top95", show_if);
    solve_all2(from_file("./hardest.txt"), "hardest", show_if);
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

#if (ENABLE_NORVIG_CPP && _HAS_CXX17)
    //norvig_cpp::test(show_if);
#endif

    //norvig_cpp_without_std_optional::test(show_if);

    {
        //norgiv_cc::Sudoku::init();
        //norgiv_cc::Sudoku::print();
    }

    //norvig_cpp_optimize::test(show_if);

    norvig_c::test2(show_if);
}

