#pragma once

#include <Board.h>
#include <iostream>
#include <limits>
#include <random>

class GameManager {
    private:
        Board& board;
        Player current_player = Player::X;
        Player first_player = Player::X;
        Player second_player = Player::O;
        GameMode game_mode = GameMode::TwoPlayers;
        bool is_easy_mode = false;
    public:
        GameManager(Board& b);

        void setup();

        void updateBoardUI() const noexcept;
        
        void drawDivider() const;

        void run();
        
        bool readPlayerMove(std::vector<int>& out_2d_position);

        std::vector<int> getAiMove();

        void showResult() const noexcept;
        
        void advanceTurn() noexcept;
};