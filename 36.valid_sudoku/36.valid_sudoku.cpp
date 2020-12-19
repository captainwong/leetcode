
#include "../common/leetcode.h"


class Solution {
public:

    /*
    ִ����ʱ��48 ms, ������ C++ �ύ�л�����18.07%���û�
    �ڴ����ģ�20.7 MB, ������ C++ �ύ�л�����5.02%���û�
    */
    bool isValidSudoku(vector<vector<char>>& board) {
        if (board.size() != 9) { return false; }
        for (const auto& line : board) { if (line.size() != 9) return false; }
        unordered_set<int> rows[9], cols[9], blocks[9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int val = board[i][j] - '0';

                if (rows[i].find(val) != rows[i].end()) { 
                    return false;
                }
                rows[i].insert(val);

                if (cols[j].find(val) != cols[j].end()) { 
                    return false;
                }
                cols[j].insert(val);

                int k = j / 3 + i / 3 * 3;
                if (blocks[k].find(val) != blocks[k].end()) { 
                    return false;
                }
                blocks[k].insert(val);
            }
        }

        return true;
    }

    /*
    ִ����ʱ��32 ms, ������ C++ �ύ�л�����60.97%���û�
    �ڴ����ģ�18.1 MB, ������ C++ �ύ�л�����25.52%���û�
    */
    bool isValidSudoku2(vector<vector<char>>& board) {
        if (board.size() != 9) { return false; }
        for (const auto& line : board) { if (line.size() != 9) return false; }
        bool rows[9][9] = { false };
        bool cols[9][9] = { false };
        bool blocks[9][9] = { false };
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int val = board[i][j] - '0' - 1;

                if (rows[i][val]) { return false; }
                rows[i][val] = true;

                if (cols[j][val]) { return false; }
                cols[j][val] = true;

                int k = j / 3 + i / 3 * 3;
                if (blocks[k][val]) { return false; }
                blocks[k][val] = true;
            }
        }

        return true;
    }
};



int main()
{
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

    assert(Solution().isValidSudoku(input1));
    assert(Solution().isValidSudoku2(input1));
    
    input1[0][0] = '8';
    assert(!Solution().isValidSudoku(input1));
    assert(!Solution().isValidSudoku2(input1));
    
}

