

/* Farran Ahmed
 * 2170-001
 * Filename: board.cpp
* Description: file for impelmtatiom for methods and functions
 * A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h" // Accessing the header file
#include <iomanip>
Board::Board() : mine_count(10), width(8), height(8), revealed_count(0), tiles(height, std::vector<Tile>(width)) {
    // initialize all tiles to covered state (done in constructor)
}

void Board::difficulty() {
    std::cout << "Enter Rows, Cols, and Mines: ";
    std::cin >> width >> height >> mine_count;
    revealed_count = 0;
    tiles.resize(height, std::vector<Tile>(width));  // resize the board based on new dimensions
}

void Board::place_mines() {
    for (int i = 0; i < mine_count; ++i) {
        int row, col;
        do {
            row = rand() % height;
            col = rand() % width;
        } while (tiles[row][col].is_mine()); // check for duplicates
        tiles[row][col].set_value('M'); // mark as mine
    }
}

void Board::update_counts() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles[i][j].is_mine()) continue; // skip mines

            int count = 0;
            // check all 8 surrounding tiles for mines
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) continue; // skip the current tile itself
                    int newRow = i + x;
                    int newCol = j + y;

                    // ensure the indices are within bounds before accessing
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {
                        if (tiles[newRow][newCol].is_mine()) {
                            count++;
                        }
                    }
                }
            }

            // ff no adjacent mines, set value to '0'
            if (count == 0) {
                tiles[i][j].set_value('0');  // asign '0' to tiles with no adjacent mines
            } else if (count > 0) {
                tiles[i][j].set_value('0' + count);  // set the tile to the number of adjacent mines
            }
        }
    }
}

void Board::reveal_tile(int row, int col) {
    // check for out-of-bounds and already revealed tiles
    if (row < 0 || row >= height || col < 0 || col >= width) return; // out of bounds check
    if (tiles[row][col].is_revealed()) return; // tile already revealed

    // reveal the current tile
    tiles[row][col].reveal();
    revealed_count++;

    // ff the tile is a mine  we don't need to check its value, just reveal it
    if (tiles[row][col].is_mine()) return;

    // ff the tile is not a mine and has zero adjacent mines, reveal it with '0'
    if (tiles[row][col].get_value() == '0') {
        //  reveal all 8 neighboring tiles if the current tile has '0' adjacent mines
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                if (x == 0 && y == 0) continue; // skip the tile itself
                reveal_tile(row + x, col + y); // recursively reveal neighboring tiles
            }
        }
    }
}

void Board::print_board() const {

    // print the top row of column indices outside the grid
    std::cout << "   ";  // space for row indices
    for (int j = 0; j < width; ++j) {
        std::cout << "  " << j << " ";  // column indices (0, 1, 2, ...)
    }
    std::cout << std::endl;
    
    // print the top border
    std::cout << "   ";  // space for row indices
    std::cout << "|";
    for (int j = 0; j < width; ++j) {
        std::cout << "---|";
    }
    std::cout << std::endl;

    // print the rows of the board
    for (int i = 0; i < height; ++i) {
        std::cout << " " << i << " |";  // row index (0, 1, 2, ...)
        for (int j = 0; j < width; ++j) {
            if (tiles[i][j].is_revealed()) {
                std::cout << " " << tiles[i][j].get_value() << " |"; // revealed value
            } else {
                std::cout << " # |"; // covered tiles
            }
        }
        std::cout << std::endl;

        // print the border after each row
        std::cout << "   ";  // space for row indices
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            std::cout << "---|";  // print each cell's border
        }
        std::cout << std::endl;
}
}



bool Board::check_win() const {
    // check if the number of revealed tiles is equal to total tiles minus mines
    return (revealed_count == (width * height - mine_count));
}

bool Board::check_loss(int row, int col) const {
    // check if the selected tile is a mine
    return tiles[row][col].is_mine();
}

void Board::revealed_board() const {
    std::cout << "Final Board:\n";

    // print the top row of column indices outside the grid
    std::cout << "   ";  // space for row indices
    for (int j = 0; j < width; ++j) {
        std::cout << "  " << j << " ";  // column indices (0, 1, 2, ...)
    }
    std::cout << std::endl;

    // print the separator row for column indices
    std::cout << "   ";  // space for row indices
    std::cout << "|";
    for (int j = 0; j < width; ++j) {
        std::cout << "---|";  // each cell represented by "----"
    }
    std::cout << std::endl;

    //print the rows of the board with row indices on the left
    for (int i = 0; i < height; ++i) {
        // print the row index before the board values
        std::cout << " " << i << " |";  // row index (0, 1, 2, ...)
        // print the values in the grid
        for (int j = 0; j < width; ++j) {
            std::cout << " " << tiles[i][j].get_value() << " |";  // revealed value
        }
        std::cout << std::endl;

        // print the border after each row
        std::cout << "   ";  // space for row indices
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            std::cout << "---|";  // print each cell's border
        }
        std::cout << std::endl;
    }
}

