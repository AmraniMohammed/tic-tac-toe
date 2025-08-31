#pragma once

#include <Board.h>
#include <iostream>
#include <limits>
#include <random>

/**
 * @brief Controls the overall Tic Tac Toe game flow.
 * 
 * Handles game setup, player turns, AI moves, board updates,
 * and final result display.
 */
class GameManager {
    private:
        Board& board;
        Player current_player = Player::X;
        Player first_player = Player::X;
        Player second_player = Player::O;
        GameMode game_mode = GameMode::TwoPlayers;
        bool is_easy_mode = false; // If true, AI plays randomly instead of using minimax
    public:
        GameManager(Board& b);

        /**
         * @brief Initializes the game: choose mode, starting player, and update UI.
         */
        void setup();

        /**
         * @brief Prints the board state to the console.
         */
        void updateBoardUI() const noexcept;

        /**
         * @brief Prints a horizontal divider between board rows.
         */
        void drawDivider() const;

        /**
         * @brief Runs the main game loop until the game is over.
         */
        void update();
        
        /**
         * @brief Reads and validates the move from a human player.
         * @param out_2d_position The resulting board coordinates if valid.
         * @return true if the move is valid, false otherwise.
         */
        bool readPlayerMove(std::vector<int>& out_2d_position);

        /**
         * @brief Gets the move for the AI player (random or minimax-based).
         * @return The AI's chosen position in [row, col] format.
         */
        std::vector<int> getAiMove();

        /**
         * @brief Displays the final result of the game.
         */
        void showResult() const noexcept;
        
        /**
         * @brief Switches to the next player's turn.
         */
        void advanceTurn() noexcept;
};