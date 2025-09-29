#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <vector>
#include <iostream>

class Sudoku {

    private:
    public:

        std::vector<std::vector<int>> board;
        int hintCounter{0};
        int maxHints{0};
        int difficulty{0}; 

        Sudoku();
        Sudoku(const std::vector<std::vector<int>>& board);

        friend std::ostream &operator<<(std::ostream &os, const Sudoku &rhs);

        std::vector<std::vector<int>> getBoard();
        void setBoard(std::vector<std::vector<int>> board);

        bool populateBoard(std::vector<std::vector<int>> &board);

        bool Solve(std::vector<std::vector<int>>);
        bool checkColumn(int, int, const std::vector<std::vector<int>>&);
        bool checkRow(int, int, const std::vector<std::vector<int>>&);
        bool checkSquare(int, int, int, const std::vector<std::vector<int>>&);

        bool sudokuSolver(std::vector<std::vector<int>>);
        bool refsudokuSolver(std::vector<std::vector<int>>&);

        bool checkGrid(std::vector<std::vector<int>>);

        std::vector<std::vector<int>> generateBoard(std::vector<std::vector<int>>&, int);
        std::vector<int> hint(std::vector<std::vector<int>>);
        std::vector<int> bigHint(std::vector<std::vector<int>>);

        void saveBoard(const std::vector<std::vector<int>>);
        bool readBoard();

};



#endif //SUDOKU_H_