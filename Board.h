/* Farran Ahmed
 * 2170-001
 * Filename: board.h
* Description: header file using struc and class 
 * A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"  // include the =tile class

class Board {
private:
    int mine_count;
    int width;
    int height;
    int revealed_count;
    std::vector<std::vector<Tile>> tiles; // use tile objects in the 2D array

public:
    Board(); // default constructor
    void place_mines(); // public method to place mines
    void revealed_board() const; // public method to display the board 
    void update_counts(); // update the counts of adjacent mines
    void difficulty(); // set difficulty
    void reveal_tile(int row, int col); // reveal the tile at (row, col)
    void print_board() const; // print the current state of the board
    bool check_win() const; // check if the player has won
    bool check_loss(int row, int col) const; // check if the player has lost
};

#endif // BOARD_H