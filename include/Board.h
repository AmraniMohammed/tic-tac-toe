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

        const std::vector<std::vector<BoardValue>>& getBoard() const noexcept {return board;};
        GameState getState() const noexcept;
        int getBoardSize() const noexcept;

        void setState(GameState new_state) noexcept;

        void makeMove(std::vector<int> position_2d, Player player);
        
        
        GameState evaluateState(Player current_player, const std::vector<std::vector<BoardValue>>& board) ;

        Winner evaluateWinner(const std::vector<std::vector<BoardValue>>& board);
        
        BoardValue getPlayerSymbol(Player player);
        
        std::string getBoardSymbol(std::vector<int> ids, std::string index) const;

        std::string getBoardSymbol(Player player) const;

        std::vector<int> get2DPos(int pos1D);

        bool isEmptyAt(int row, int col, const std::vector<std::vector<BoardValue>>& board) const;

        std::vector<std::vector<int>> getAvailablePositions() const;

        bool checkIfWin(const std::vector<std::vector<BoardValue>>& board_table);

        bool isFull(const std::vector<std::vector<BoardValue>>& board);
};