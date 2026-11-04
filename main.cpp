#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class SudokuPuzzle
{
        public:

        int puzzle[9][9];

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

void calculate_possibilities(int puzzle[9][9],
                            std::vector<int> possibilities[9][9])
{
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            possibilities[r][c].clear();
            if (puzzle[r][c] == 0){
                for (int num = 1; num <= 9; num++){
                    bool found = is_num_present(puzzle, r, c, num);
                    if (found == false){
                        possibilities[r][c].push_back(num);
                    }
                }
            }
        }
    }
}

int fill_singletons(int puzzle[9][9],
                    std::vector<int> possibilities[9][9])
{
    int inserted = 0;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            if (puzzle[r][c] == 0){
                if (possibilities[r][c].size() == 1){
                    puzzle[r][c] = possibilities[r][c][0];
                    inserted++;
                }
            }
        }
    }
    return inserted;
}

bool solve_simple(int puzzle[9][9])
{
    std::vector<int> possibilities[9][9];

    int inserted = 1;

    while (count_empty(puzzle) > 0 && inserted > 0)
    {
        calculate_possibilities(puzzle, possibilities);

        inserted = fill_singletons(puzzle, possibilities);
    }

    return count_empty(puzzle) == 0;
}

bool load_puzzle(std::string digits, int puzzle[9][9])
{
    if (digits.size() != 81) {
        return false;
    }

    for (int i = 0; i < 81; i++) {
        if (digits[i] < '0' || digits[i] > '9') {
            return false;
        }
    }

    for (int i = 0; i < 81; i++) {
        int row = i / 9;
        int col = i % 9;
        puzzle[row][col] = digits[i] - '0';
    }

    return true;
}

int main()
{
    std::ifstream input("easy.txt");
    if (!input.is_open()) {
        std::cout << "Could not open easy.txt\n";
        return 1;
    }

    int lines_read = 0;
    int attempted = 0;
    int solved = 0;
    int stalled = 0;
    int malformed = 0;

    std::string line;
    while (std::getline(input, line)) {
        lines_read++;
        int puzzle[9][9] = {};

        if (line.size() < 94) {
            malformed++;
        } else {
            std::string digits = line.substr(13, 81);
            bool loaded = load_puzzle(digits, puzzle);

            if (loaded == false) {
                malformed++;
            } else {
                attempted++;
                bool complete = solve_simple(puzzle);

                if (complete == true) {
                    solved++;
                } else {
                    stalled++;
                }
            }
        }
    }

    std::cout << "Lines read: " << lines_read << "\n";
    std::cout << "Attempted: " << attempted << "\n";
    std::cout << "Solved: " << solved << "\n";
    std::cout << "Stalled: " << stalled << "\n";
    std::cout << "Malformed: " << malformed << "\n";

    if (attempted > 0) {
        std::cout << "Percent solved: "
                  << 100.0 * solved / attempted << "%\n";
    }

    return 0;
}