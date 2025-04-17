/* Farran Ahmed
 * 2170-001
 * Filename: playable.cpp
* Description: files takes is main and calls all the funtions
 * A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"


int main() {
    srand((time(0))); // seed for random number generation
    Board board; // creation of board variable
    board.difficulty(); // set difficulty based on user input
    board.place_mines(); // place mines on the board
    board.update_counts(); // update the counts of adjacent mines
    board.print_board(); // print the start state of the board

    int row, col;
    while (true) {
        std::cout << "Enter a row and column to dig: ";
        std::cin >> row >> col;

        if (std::cin.fail()) { // check for invalid input
            std::cin.clear(); // cear the error flag
            std::cout << "Invalid input, please enter numbers for row and column." << std::endl;
            continue; 
        }

        if (board.check_loss(row, col)) { // check if loss
        std::cout << "\n";
            std::cout << "YOU'VE LOST!!!!!!!" << std::endl; // 
            board.revealed_board(); // if yes reveled the whole bored
            break;
        }

        board.reveal_tile(row, col); // reveal the selected tile
        board.print_board(); // print the current state of the board after revealing

        if (board.check_win()) { // checks if you have won
        std::cout << "\n";
            std::cout << "YOU'VE WON!!! "<< std::endl;
            std::cout <<"Final Board: " << std::endl;
            board.print_board();
            break;
        }
    }
    return 0;
}