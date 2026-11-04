#include <iostream>
#include <vector>

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
            if (puzzle[r][c] == 0 &&
                possibilities[r][c].size() == 1){
                puzzle[r][c] = possibilities[r][c][0];
                inserted++;
            }
        }
    }

    return inserted;
}

int main() {

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



#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void print_puzzle(int puzzle[9][9]) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col)
            std::cout << puzzle[row][col] << (col == 8 ? '\n' : ' ');
    }
}

int count_empty(int puzzle[9][9]) {
    int blanks = 0;
    for (int row = 0; row < 9; ++row)
        for (int col = 0; col < 9; ++col)
            if (puzzle[row][col] == 0) ++blanks;
    return blanks;
}

bool is_num_present(int puzzle[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (puzzle[row][i] == num || puzzle[i][col] == num) return true;
    }

    int row_offset = (row / 3) * 3;
    int col_offset = (col / 3) * 3;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (puzzle[row_offset + r][col_offset + c] == num) return true;

    return false;
}

void calculate_possibilities(int puzzle[9][9],
                             std::vector<int> possibilities[9][9]) {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            possibilities[r][c].clear();
            if (puzzle[r][c] == 0) {
                for (int num = 1; num <= 9; ++num)
                    if (!is_num_present(puzzle, r, c, num))
                        possibilities[r][c].push_back(num);
            }
        }
    }
}

int fill_singletons(int puzzle[9][9],
                    std::vector<int> possibilities[9][9]) {
    int inserted = 0;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (puzzle[r][c] == 0 && possibilities[r][c].size() == 1) {
                puzzle[r][c] = possibilities[r][c][0];
                ++inserted;
            }
        }
    }
    return inserted;
}

bool solve_simple(int puzzle[9][9], bool trace = false) {
    std::vector<int> possibilities[9][9];
    int pass = 0, inserted = 1;

    // Build all lists from the same grid before placing any digits.
    while (count_empty(puzzle) > 0 && inserted > 0) {
        calculate_possibilities(puzzle, possibilities);
        inserted = fill_singletons(puzzle, possibilities);
        ++pass;

        if (trace)
            std::cout << "Pass " << pass << ": inserted " << inserted
                      << ", remaining " << count_empty(puzzle) << '\n';
    }

    return count_empty(puzzle) == 0;
}

bool load_puzzle(std::string digits, int puzzle[9][9]) {
    if (digits.size() != 81) return false;

    for (char digit : digits)
        if (digit < '0' || digit > '9') return false;

    for (int i = 0; i < 81; ++i)
        puzzle[i / 9][i % 9] = digits[i] - '0';

    return true;
}

int main(int argc, char* argv[]) {
    int puzzle[9][9] = {
        {2, 8, 5, 0, 0, 0, 0, 0, 3},
        {1, 0, 3, 0, 9, 0, 0, 6, 4},
        {0, 0, 6, 7, 0, 0, 5, 0, 1},
        {8, 0, 0, 0, 1, 2, 0, 0, 0},
        {0, 9, 1, 0, 0, 0, 6, 4, 2},
        {5, 2, 0, 3, 0, 0, 1, 0, 9},
        {0, 5, 0, 0, 0, 4, 7, 3, 0},
        {0, 1, 0, 0, 8, 3, 0, 9, 0},
        {0, 3, 8, 6, 0, 9, 0, 0, 0}
    };

    print_puzzle(puzzle);
    std::cout << "Initial blanks: " << count_empty(puzzle)
              << "\nCandidates at [0][3]:";

    for (int num = 1; num <= 9; ++num)
        if (!is_num_present(puzzle, 0, 3, num))
            std::cout << ' ' << num;
    std::cout << '\n';

    solve_simple(puzzle, true);
    print_puzzle(puzzle);

    std::cout << "Already complete: "
              << (solve_simple(puzzle, true) ? "SOLVED" : "STALLED") << '\n';

    int empty_grid[9][9] = {};
    bool complete = solve_simple(empty_grid, true);
    std::cout << "Empty grid: " << (complete ? "SOLVED" : "STALLED") << '\n';

    std::string filename = argc > 1 ? argv[1] : "easy.txt";
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Could not open " << filename << '\n';
        return 1;
    }

    int lines_read = 0, attempted = 0, solved = 0, stalled = 0, malformed = 0;
    std::string line;

    while (std::getline(input, line)) {
        ++lines_read;
        int grid[9][9] = {};

        if (line.size() < 94 || !load_puzzle(line.substr(13, 81), grid)) {
            ++malformed;
            continue;
        }

        ++attempted;
        if (lines_read == 1) {
            std::cout << "First record, initial blanks: "
                      << count_empty(grid) << '\n';
            print_puzzle(grid);
        }

        bool finished = solve_simple(grid);
        if (finished) ++solved;
        else ++stalled;

        if (lines_read <= 10)
            std::cout << lines_read << ' ' << line.substr(0, 12)
                      << (finished ? " SOLVED" : " STALLED")
                      << ", remaining " << count_empty(grid) << '\n';
    }

    std::cout << "Lines read: " << lines_read
              << "\nAttempted: " << attempted
              << "\nSolved: " << solved
              << "\nStalled: " << stalled
              << "\nMalformed: " << malformed
              << "\nPercent solved: " << std::fixed << std::setprecision(2)
              << (attempted > 0 ? 100.0 * solved / attempted : 0.0) << "%\n";
}
