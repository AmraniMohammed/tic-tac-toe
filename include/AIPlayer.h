#pragma once
#include <GameTypes.h>
#include <vector>

class Board;

/**
 * @class AIPlayer
 * @brief Implements an AI opponent for turn-based board game (Tic-Tac-Toe)
 *        using the Minimax algorithm.
 */
class AIPlayer {
    private:
        Board& board;
    public:
        AIPlayer(Board& b);

        /**
         * @brief Minimax algorithm for computing the optimal score from a given board state.
         * @param board_table Current board state.
         * @param depth Maximum search depth.
         * @param current_player The player whose turn it is.
         * @param human_player The human player identifier.
         * @param ai_player The AI player identifier.
         * @return The best utility score achievable from this state.
         */
        int miniMaxAlgo(const std::vector<std::vector<BoardValue>>& board_table, int depth, Player current_player, Player human_player, Player ai_player);

        /**
         * @brief Checks if the given board state is terminal (win, loss, or draw).
         */
        bool isTerminal(const std::vector<std::vector<BoardValue>>& board_table);

         /**
         * @brief Computes the utility value of a board state for the AI.
         * @return 1 if AI wins, -1 if AI loses, 0 for draw.
         */
        int getUtility(const std::vector<std::vector<BoardValue>>& board_table, Player ai_player);

        /**
         * @brief Generates a list of all possible moves from the given board state.
         * @return Vector of (row, col) coordinates for empty cells.
         */
        std::vector<std::vector<int>> getActions(const std::vector<std::vector<BoardValue>>& board_table);
        
        /**
         * @brief Returns a new board state after applying a given move.
         */
        std::vector<std::vector<BoardValue>> getResult(const std::vector<std::vector<BoardValue>>& board_table, std::vector<int>& action, Player player);

        /**
        * @brief Finds the best move for the AI using Minimax search.
        * @param depth Maximum search depth (default: 10).
        * @return The (row, col) of the optimal move.
        */
        std::vector<int> getBestMove(const std::vector<std::vector<BoardValue>>& board_table, Player current_player, Player human_player, Player ai_player, int depth = 10);

};