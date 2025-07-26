#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <limits>
#include <random>

enum class GameState { PlayerXWin, PlayerOWin, Draw, Continue };
enum class Player {X, O, AI};
enum class GameMode { TwoPlayers, OnePlayer };

class Board {

    private:
        Player current_player = Player::X;
        Player first_player = Player::X;
        Player second_player = Player::O;
        GameState state = GameState::Continue;
        GameMode game_mode = GameMode::TwoPlayers;
        std::array<char, 9> board = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
        inline static const std::vector<std::vector<int>> wins_cases = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                                                                                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                                                                                {0, 4, 8}, {2, 4, 6}
                                                                                };

    public:
        Player getPlayer() const noexcept {return current_player;};
        const auto& getBoard() const {return board;};
        GameState getState() const noexcept {return state;};
        GameMode getGameMode() const noexcept {return game_mode;};

        void setup() {
            std::cout << "Please choose the game mode that you want, for two player game mode type 2, and for one player vs AI game mode type 1. \n";
            int play_mode;
            bool play_mode_seted = false;
            while(true) {
                if(!play_mode_seted) {
                    std::cin >> play_mode;
                    if(std::cin.fail() || (play_mode != 1 && play_mode != 2)) {
                        std::cout << "Please type a valid choice (1 or 2). \n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        if(play_mode == 2) game_mode = GameMode::TwoPlayers;
                        else game_mode = GameMode::OnePlayer;
                        play_mode_seted = true;
                    }
                }
                else {
                    if(game_mode == GameMode::TwoPlayers) {
                        std::cout<< "Please choose a valid starting player symbol by typing X or O\n";
                    }
                    else {
                        std::cout<< "Please choose a playing symbol by typing X or O\n";
                    }
                    std::string starting_player;
                    std::cin >> starting_player;

                    if(game_mode == GameMode::OnePlayer  && (starting_player == "X" || starting_player == "x")) {
                        current_player = Player::X;
                        first_player = current_player;
                        second_player = Player::AI;
                        break;
                    }
                    else if(game_mode == GameMode::OnePlayer  && (starting_player == "O" || starting_player == "o")) {
                        current_player = Player::O;
                        first_player = current_player;
                        second_player = Player::AI;
                        break;
                    }
                    else if(starting_player == "X" || starting_player == "x") {
                        current_player = Player::X;
                        first_player = current_player;
                        second_player = Player::O;
                        break;
                    }
                    else if(starting_player == "O" || starting_player == "o") {
                        current_player = Player::O;
                        first_player = current_player;
                        second_player = Player::X;
                        break;
                    }
                }
            };
            updateBoardUI();
        }

        void fillSquareAtPosition(int pos) {
            board[pos] = getPlayerSymbol(current_player);
        };
         void advanceTurn() noexcept {
            if(game_mode == GameMode::OnePlayer) {
                current_player = (current_player == Player::X || current_player == Player::O ? Player::AI : first_player);
            }
            else {
                current_player = (current_player == Player::X ? Player::O : Player::X);
            }
        }

        bool readPlayerMove(int& out_position) {
            std::cout << "\n" << "Player (" << getPlayerSymbol(current_player) << ") role, please type the position you want to fill: ";
            
            int pos;
            std::cin >> pos;
            if(std::cin.fail() || pos < 0 || pos > 8) {
                std::cout << "Please give a valid number between 0 and 8\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
            else if(board[pos] == 'X' || board[pos] == 'O') {
                std::cout << "Position [" << pos << "] already filled, please choose another one\n";
                return false;
            }
            out_position = pos;
            return true;
        }

        GameState evaluateState() {
            bool is_win = false;

            for(auto win_case: wins_cases) {
                if(board[win_case[0]] == board[win_case[1]] && board[win_case[1]] == board[win_case[2]]) {
                    is_win = true;
                    break;
                }
            };

            if(is_win) {
                state = (current_player == Player::X ? GameState::PlayerXWin : GameState::PlayerOWin);
            }
            else if(std::count_if(board.begin(), board.end(), [](char value){return(value == 'X' || value == 'O');}) == 9) {
                state = GameState::Draw;
            }
            else {
                state = GameState::Continue;
            }
            return state;
        };

        void updateBoardUI() const noexcept {
            std::cout <<"\n";

            std::cout << " " << board[0]  << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << "\n";
            std::cout << "___ ___ ___" << "\n";

            std::cout << " " << board[3]  << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << "\n";
            std::cout << "___ ___ ___" << "\n";
            
            std::cout << " " << board[6]  << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << "\n";
        };

        void showResult() const noexcept{
            if(state == GameState::Draw) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Draw ==========\n";
            } else if(state == GameState::PlayerXWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player X won ==========\n";
            }
            else if(state == GameState::PlayerOWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player O won ==========\n";
            }
        }

        void run() {
            // Get Position to fill from player
            int position;
            
            // Game loop
            while(getState() == GameState::Continue){ 

                if(getGameMode() == GameMode::OnePlayer && getPlayer() == Player::AI) {
                    //std::cout << "One player mode vs AI coming soon ... \n";
                    position = getAiMove();
                    //break;
                }
                else {
                    // Get input
                    if(!readPlayerMove(position)) continue;
                }

                // Game logic
                fillSquareAtPosition(position);
                evaluateState();

                // Draw 
                updateBoardUI();

                if(getState() == GameState::Continue) 
                    advanceTurn();

            };

            showResult();
        }

        char getPlayerSymbol(Player player) {
            switch (player) {
                case Player::X: return 'X';
                case Player::O: return 'O';
                case Player::AI: {
                    if(first_player == Player::X) return 'O';
                    else return 'X';
                };
            }
            return '?';
        }

        int getAiMove() {

            std::vector<int> available_positions;

            for(int i = 0; i < board.size(); i++) {
                if(board[i] != 'X' && board[i] != 'O') {
                    available_positions.push_back(i);
                }
            }

            // Define range
            int min = 0;
            int max = available_positions.size() - 1;

            // Initialize a random number generator
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(min, max);

            // Generate random number in the range [min, max]
            int randomValue = distrib(gen);

            return available_positions[randomValue];
        }
};


int main() {

    
    std::cout << "========== Tic Tac Toe Game ==========\n";
    
    Board board;

    board.setup();

    board.run();
    
    return 0;
}