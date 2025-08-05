#pragma once
#include <GameTypes.h>
#include <vector>

class Board;

class AIPlayer {
    private:
        Board& board;
    public:
        AIPlayer(Board& b);
        int miniMaxAlgo(const std::vector<std::vector<BoardValue>>& board_table, int depth, Player current_player, Player human_player, Player ai_player);

        bool isTerminal(const std::vector<std::vector<BoardValue>>& board_table);

        int getUtility(const std::vector<std::vector<BoardValue>>& board_table, Player ai_player);
        std::vector<std::vector<int>> getActions(const std::vector<std::vector<BoardValue>>& board_table);
        
        std::vector<std::vector<BoardValue>> getResult(const std::vector<std::vector<BoardValue>>& board_table, std::vector<int>& action, Player player);
};