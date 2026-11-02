#include <iostream>
#include <vector>

class SudokuPuzzle
{
        public:

        int puzzle[9][9];

        //Constructor
        SudokuPuzzle(int p[9][9])

        {
            for (int r = 0; r < 9; r++){
                for (int c = 0; c < 9; c++){
                    puzzle[r][c] = p[r][c];
                }
            }
        }
        
        void print()
        {
            for (int r = 0; r < 9; r++){
                for (int c = 0; c < 9; c++){
                    int count = puzzle [r][c];
                }
            std::cout << std::endl;
            }
        std::cout << std::endl;     
        }
};



bool is_num_present(int puzzle[9][9], int row, int col, int num)
{
    bool found = false;
    for(int c = 0; c < 9; c++)
    {
        if(puzzle[row][c] == num)
        {
            found = true;
        }
    }

    for(int r = 0; r < 9; r++)
    {
        if(puzzle[r][col] == num)
        {
            found = true;
        }
    }

    int col_offset = (col/3)*3;
    int row_offset = (row/3)*3;
    for (int r = 0; r<3; r++){
        for (int c = 0; c<3; c++){
            if(puzzle[row_offset + r][col_offset + c] == num){
                found = true;
            }
        }
    }
    return found;
}

void print_puzzle(int puz[9][9])
{
for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            int clue = puz [i][j];
            if (clue == 0){
                std::cout << " ";
            }else{
                std::cout << clue;
            }
        }
         std::cout << std::endl;
    }
}

int count_empty(int puzzle[9][9])
{
    int count = 0;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            if(puzzle[r][c] == 0){
                count++;
            }
        }
    }
    return count;
}

int main() {

    // Store first sodoku
    int puzzle[9][9] = {
        {2,8,5, 0,0,0, 0,0,3},
        {1,0,3, 0,9,0, 0,6,4},
        {0,0,6, 7,0,0, 5,0,1},
        
        {8,0,0, 0,1,2, 0,0,0},
        {0,9,1, 0,0,0, 6,4,2},
        {5,2,0, 3,0,0, 1,0,9},

        {0,5,0, 0,0,4, 7,3,0},
        {0,1,0, 0,8,3, 0,9,0},
        {0,3,8, 6,0,9, 0,0,0}
    };   

    std::vector <int> possibilities;
    possibilities.clear();

    int row = 7;
    int col = 5;
    int num = 1;


    bool found = is_num_present(puzzle, row, col, num);

    if(found == false)
    {
        possibilities.push_back(num);
        std::cout << "DID NOT FIND " << num << std::endl;
    }
    else{
        std::cout << "found " << num << std::endl;
    }
    int count = count_empty(puzzle);
    std::cout << count << std::endl;

    return 0;
}
