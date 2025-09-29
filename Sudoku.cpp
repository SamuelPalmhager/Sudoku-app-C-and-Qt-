#include "Sudoku.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <cassert>
#include <string>


Sudoku::Sudoku(){std::cout << "Default constructor called" << std::endl;board=std::vector<std::vector<int>>(9, std::vector<int>(9, 0)); hintCounter = 0; difficulty = 0; maxHints = 0;}; //Default const, initalises empty board
   
Sudoku::Sudoku(const std::vector<std::vector<int>>& board): board(board), hintCounter(0), difficulty(0), maxHints(0){std::cout << "Overloaded const called" << std::endl; }; //Explicit const, defines board as input
 
void Sudoku::setBoard(std::vector<std::vector<int>> input){
    this->board = input;
};

std::vector<std::vector<int>> Sudoku::getBoard(){
    return this->board;
};

std::ostream &operator<<(std::ostream &os, const Sudoku &rhs){
    os << "Start of ostream \n";
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            os << rhs.board.at(i).at(j) << " "; 
        }
        os << "\n";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &rhs){
    for (size_t i = 0; i < 9; i++)
    {
        os << rhs.at(i) << " ";
    }
    return os;
    
};

bool Sudoku::populateBoard(std::vector<std::vector<int>> &board){
    std::vector<int> numberlist {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rd;
    std::mt19937 g(rd());
    int row {0};
    int col {0};
    int value {0};
    if(checkGrid(board)) {
        return true;
    }
    for (size_t i = 0; i < 81; i++)
    {
        row = i/9;
        col = i%9;
        //std::cout << "Row: " << row << " Col: " << col << std::endl;

        if(board[row][col] == 0) {std::shuffle(numberlist.begin(), numberlist.end(), g);
        for (size_t j = 0; j < 9; j++)
        {
            value = numberlist.at(j);
            if(checkColumn(col, value, board) && checkRow(row, value, board) && checkSquare(row, col, value, board)){
                board[row][col] = value;
                //std::cout << board << std::endl;
                if(checkGrid(board)){
                    return true;
                }else{
                    if(populateBoard(board)){
                        return true;
                    }
                }
                board[row][col] = 0; //Backtrack if didnt work;
            }
         }
        return false; 
        }
    }
    return true; //No zeros found 
}

bool Sudoku::checkColumn(int col, int value, const std::vector<std::vector<int>> &board){

    for (size_t i = 0; i < 9; i++)
    {
        if(board[i][col] == value) return false;
    }
    return true;
}

bool Sudoku::checkRow(int row, int value, const std::vector<std::vector<int>> &board){
    for (size_t i = 0; i < 9; i++)
    {
        if(board[row][i] == value) return false;
    }
    return true;
};

bool Sudoku::checkSquare(int row, int col, int value, const std::vector<std::vector<int>> &board){
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if(board[boxRow + i][boxCol + j] == value)
                return false;
        }
        
    }
    return true;
}

bool Sudoku::checkGrid(std::vector<std::vector<int>> board){
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if(board.at(i).at(j) == 0){
                return false;
            }
        }
        
    }
    return true;
}

bool Sudoku::sudokuSolver(std::vector<std::vector<int>> board){
    /*
        1. Identify first 0 in board
        2. Find the first number that is legal to place and has not been placed before
        3. Place number and check next for next 0 in row
        4. If there is no legal number to place, return false and return to step 2- 
        5. If there is no 0 found in return true
    */

    std::vector<int> numberlist {1,2,3,4,5,6,7,8,9};
    int row{0};
    int col{0};

    if(checkGrid(board)) return true;

    for (size_t i = 0; i < 81; i++)
    {
        row = i/9;
        col = i%9;
        //std::cout << "Row: " << row << " Col: " << col << std::endl;
        if(board[row][col] == 0){
            for (size_t j = 0; j < 9; j++)
            {
                int value = numberlist.at(j);
                if(checkColumn(col, value, board) && checkRow(row, value, board) && checkSquare(row, col, value, board)){
                    board[row][col] = value;
                   // std::cout << board << std::endl;
                    //std::cout << "Changed [" << row << "]" << "[" << col << "]" << " to " << value << std::endl;
                    if(checkGrid(board)){
                        return true;
                    }else{
                        if(sudokuSolver(board)) return true;
                    }
                    board[row][col] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

bool Sudoku::refsudokuSolver(std::vector<std::vector<int>> &board){
    /*
        1. Identify first 0 in board
        2. Find the first number that is legal to place and has not been placed before
        3. Place number and check next for next 0 in row
        4. If there is no legal number to place, return false and return to step 2- 
        5. If there is no 0 found in return true
    */

    std::vector<int> numberlist {1,2,3,4,5,6,7,8,9};
    int row{0};
    int col{0};

    if(checkGrid(board)) return true;

    for (size_t i = 0; i < 81; i++)
    {
        row = i/9;
        col = i%9;
        //std::cout << "Row: " << row << " Col: " << col << std::endl;
        if(board[row][col] == 0){
            for (size_t j = 0; j < 9; j++)
            {
                int value = numberlist.at(j);
                if(checkColumn(col, value, board) && checkRow(row, value, board) && checkSquare(row, col, value, board)){
                    board[row][col] = value;
                    std::cout << board << std::endl;
                    //std::cout << "Changed [" << row << "]" << "[" << col << "]" << " to " << value << std::endl;
                    if(checkGrid(board)){
                        return true;
                    }else{
                        if(refsudokuSolver(board)) return true;
                        
                    }
                    board[row][col] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int>> Sudoku::generateBoard(std::vector<std::vector<int>> &board, int diff){
    std::cout << std::rand()%(9) << std::endl;
    int counter {0};
    hintCounter = 0;
    while(counter != diff){
        if(!sudokuSolver(board)) break;
        int x = std::rand()%(9);
        int y = std::rand()%(9);
        board[x][y] = 0;
        counter++;
    }   
    //std::cout << board << std::endl;
   return board;
};

std::vector<int> Sudoku::hint(std::vector<std::vector<int>> board){
    std::vector<std::vector<int>> copyboard {};
    std::vector<int> answer {};


    if(this->hintCounter == this->maxHints) return answer;

    copyboard = board;
    refsudokuSolver(copyboard);
    int row {0};
    int col {0};

    do{
    row = std::rand()%(9);
    col = std::rand()%(9);
    }while(copyboard[row][col] == board[row][col]);

    answer.push_back(row+1);
    answer.push_back(col+1);
    answer.push_back(copyboard[row][col]);
    this->hintCounter++;
    std::cout << "Hintcounter: " << hintCounter << std::endl;
    return answer;
}

void Sudoku::saveBoard(const std::vector<std::vector<int>> input){

    /*
        1. Open file output stream and check valid opening or creation of file.
        2. Order of output should be -> currentboard (0s representing empty spaces), difficulty, number of hints used.  
        3. Output stream should start writing to file, if file already populated, delete contents.
        4. Close the file once content written.
    */

    std::cout << "Entered saveboard" << std::endl;

    std::string file_path = "../playerprogress.txt";
    
    std::ofstream out_file{file_path, std::ios::app};

    if(!out_file){
        std::cout << "Error opening or creating file" << std::endl;
        perror("System error");
        return;
    }

    std::cout << "File opened or created successfully" << std::endl;

    for (size_t i = 0; i < 9; i++)
    {
        std::cout << board[i] << std::endl;
    }
    
    assert(board.size() == 9);
    for (const auto& r : board) assert(r.size() == 9);

    std::cout << "Size of rows: " << input.size() << std::endl;
    std::cout << "Size of cols: " << input[0].size() << std::endl;
    
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            out_file << input.at(i).at(j);
        }
        out_file << "\n";
        
    }

    out_file << difficulty << " " <<  hintCounter << std::endl;

    std::cout << "Proggress saved successfully" << std::endl;
    out_file.close();
    std::cout << "out file closed" << std::endl;
    return;
};