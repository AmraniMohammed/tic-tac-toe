#pragma once
#include <GameTypes.h>
#include <vector>
#include <algorithm>
#include <string>

class Board {

    private:
        GameState state = GameState::Continue;
        int board_size = 3;
        std::vector<std::vector<BoardValue>> board;
    
    public:
        Board();

        // Returns a const reference to the board
        const std::vector<std::vector<BoardValue>>& getBoard() const noexcept;

        // Returns the current game state
        GameState getState() const noexcept;

        // Returns the board dimension
        int getBoardSize() const noexcept;

        // Sets the current game state
        void setState(GameState new_state) noexcept;

        // Sets the current game state
        void setBoardSize(int new_board_size) noexcept;

        // Sets the current game state
        void reset() noexcept;

        /**
         * Places a player's symbol at the given 2D position on the board
         * @param position_2d 2D coordinates {row, column}
         * @param player The player making the move
         */
        std::vector<std::vector<BoardValue>> createBoard(int dim);

        /**
         * Places a player's symbol at the given 2D position on the board
         * @param position_2d 2D coordinates {row, column}
         * @param player The player making the move
         */
        void makeMove(std::vector<int> position_2d, Player player);
        
        /**
         * Evaluates the state of the board for the current player
         * @param current_player Player whose turn it is
         * @param board Board to evaluate
         * @return GameState after evaluation (win, draw, continue)
         */
        GameState evaluateState(Player current_player, const std::vector<std::vector<BoardValue>>& board) ;

         /**
         * Checks for a winner on the given board
         * @param board Board to evaluate
         * @return Winner enum (X, O, Draw, None)
         */
        Winner evaluateWinner(const std::vector<std::vector<BoardValue>>& board);
        
        /**
         * Returns the symbol (X or O) corresponding to a player
         * @param player Player enum
         * @return BoardValue for the player
         */
        BoardValue getPlayerSymbol(Player player);
 
        /**
         * Returns the display string for a board cell, using index if empty
         * @param ids 2D coordinates {row, column}
         * @param index Index string to display if cell is empty
         * @return Symbol string ("X", "O", or index)
         */
        std::string getBoardSymbol(std::vector<int> ids, std::string index) const;

        /**
         * Returns the symbol for a player as string
         * @param player Player enum
         * @return "X" or "O"
         */
        std::string getBoardSymbol(Player player) const;

        /**
         * Converts a 1D board index to 2D coordinates
         * @param pos1D Position in 1D (0-8)
         * @return 2D coordinates {row, column}
         */
        std::vector<int> get2DPos(int pos1D);

        /**
         * Checks if a given cell is empty
         * @param row Row index
         * @param col Column index
         * @param board Board to check
         * @return true if cell is empty
         */
        bool isEmptyAt(int row, int col, const std::vector<std::vector<BoardValue>>& board) const;

        /**
         * Returns all available empty positions on the board
         * @return Vector of 2D coordinates {row, column} of empty cells
         */
        std::vector<std::vector<int>> getAvailablePositions() const;

        /**
         * Checks if the given board has a winning condition
         * @param board_table Board to check
         * @return true if any player has won
         */
        bool checkIfWin(const std::vector<std::vector<BoardValue>>& board_table);

        /**
         * Checks if the board is completely filled
         * @param board Board to check
         * @return true if no empty cells remain
         */
        bool isFull(const std::vector<std::vector<BoardValue>>& board);
};
